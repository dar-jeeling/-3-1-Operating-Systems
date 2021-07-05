# -3-1-Operating-Systems

3-1에 수강한 "운영체제"과목의 과제를 모아둔 공간입니다.
xv6을 이용하여 프로젝트를 진행하였습니다.

0. Install xv6 
- xv6을 설치하고, xv6의 개념에 대해서 알아보았습니다.
- xv6의 boot message의 본인의 학번과 이름을 출력해봄으로써, xv6이 booting 될 때, 제일 먼저 시작되는 프로그램이 뭔지 알아보았습니다.
2. System Call
- System Call의 개념을 알고, 직접 시스템콜을 구현할 수 있었다.
- System Call이 호출되었을 때, 내부적으로 어떤 일이 일어나는지 이해할 수 있었다.
3. Stack Growth
- pagefault handler를 구현하였다. 
- rc2()를 호출해 page fault가 발생한 virtulal address를 결정하고, virtual address가 valid한 값인지 확인한다.
4. Copy-on-Write
- child process를 fork하게 되면 같은 메모리 공간을 공유하게 되는데, parent process가 데이터를 새로 넣거나 수정하거나 지우게 되면 같은 메모리 공간을 공유할 수 없게 되므로, parent process는 해당 page를 복사한 다음 수정한다. 이것이 바로 Copy-on-write 과정이다.
- 
