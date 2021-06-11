// Physical memory allocator, intended to allocate
// memory for user processes, kernel stacks, pgae table pages,
// and pipe buffers. Allocates 4096-byte pages.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"

// 각 physical page의 reference count를기록할 배열 생성
uint pgrefcount[PHYSTOP >> PGSHIFT];
uint get_refcounter(uint pa);
void dec_refcounter(uint pa);
void inc_refcounter(uint pa);
void freerange(void *vstart, void *vend);
extern char end[]; // first address after kernel loaded from ELF file
                   // defined by the kernel linker script in kernel.ld
int numfreepages = 0;

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  int use_lock;
  struct run *freelist;
} kmem;

// Initialization happens in two phases.
// 1. main() calls kinit1() while still using entrypgdir to place just
// the pages mapped by entrypgdir on free list.
// 2. main() calls kinit2() with the rest of the physical pages
// after installing a full page table that maps them on all cores.
void
kinit1(void *vstart, void *vend)
{
  initlock(&kmem.lock, "kmem");
  kmem.use_lock = 0;
  freerange(vstart, vend);
}

void
kinit2(void *vstart, void *vend)
{
  freerange(vstart, vend);
  kmem.use_lock = 1;
}

void
freerange(void *vstart, void *vend)
{
  char *p;
  p = (char*)PGROUNDUP((uint)vstart);
  for(; p + PGSIZE <= (char*)vend; p += PGSIZE){
    kfree(p);
    pgrefcount[V2P(p)>>PGSHIFT] = 0;
  }
}
//PAGEBREAK: 21
// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v)
{
  struct run *r;

  if((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
    panic("kfree");

  if(get_refcounter(V2P(v)) > 0)
    dec_refcounter(V2P(v));

  if(get_refcounter(V2P(v)) == 0){
  // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE);

    if(kmem.use_lock)
      acquire(&kmem.lock);
    // 해당 page를 free pagelist에 추가하기
    numfreepages++;
    r = (struct run*)v;
    r->next = kmem.freelist;
    kmem.freelist = r;
    if(kmem.use_lock)
      release(&kmem.lock);
    }
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char*
kalloc(void)
{
  struct run *r;

  if(kmem.use_lock)
    acquire(&kmem.lock);
  numfreepages--;
  r = kmem.freelist;
  if(r){
    kmem.freelist = r->next;
    // reference counter를 1로 초기화
    pgrefcount[V2P((char*)r) >> PGSHIFT] = 1;
  }
    kmem.freelist = r->next;
  if(kmem.use_lock)
    release(&kmem.lock);
  return (char*)r;
}

int freemem(){
  return numfreepages;
}

// 인자로 받은 pa가 속한 physical page의 reference counter 반환
uint
get_refcounter(uint pa)
{
  return pgrefcount[pa >> PGSHIFT];
}

// pa의 reference counter를1 감소
void
dec_refcounter(uint pa)
{
  pgrefcount[pa >> PGSHIFT]--;
}

// pa의 reference counter를 1 증가
void
inc_refcounter(uint pa)
{
  pgrefcount[pa >> PGSHIFT]++;
}
