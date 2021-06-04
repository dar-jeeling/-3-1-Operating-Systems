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
5. Copy-on-Write (진행 중)
