#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
	int count = getreadcount();
	printf(1,"readcount : %d\n", count);
	exit();
}
