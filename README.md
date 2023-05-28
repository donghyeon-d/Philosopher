# 프로젝트 개요
1. 42seoul 커리큘럼 중 Multi-Thread C 프로젝트를 C++ 로 구현함
    - 이전에 42서울에서 C로 만든 프로그램은 내용을 잘못이해하고 잘못 구현한 부분이 있음. 이에 C++로 객체지향적으로 다시 구현해봤음
    - [42서울 과제 정리 노션 링크](https://dongchoi.notion.site/Philosopher-947e57952e334043994125430f18b611)
    - [42서울 과제 코드 github](https://github.com/donghyeon-d/42cursus.git) /42cursus/philosopher

2. 주제 
    - 식사하는 철학자들 문제 Mutil-thread 

3. 조건
    - C++로 구현
    - 프로그램 인자 : 철학자 수, 굶어 죽기까지 걸리는 시간, 먹는데 걸리는 시간, 자는 시간, 
                            [특정 횟수만큼 먹으면 시뮬레이션 종료(옵션)]
    - 철학자 1명 == 1개의 thread, 포트는 철학자 개수만큼 있음
    - 철학자는 일정시간 밥을 먹지 못하면 죽게 됨
    - 철학자들끼리는 정보를 주고 받을 수 없음
    - 포크의 상태(used, not_used)는 mutex로 관리될 것
    - 상태가 변할 때마다 현재시간(ms), 철학자id, 상태를 출력(stdout)하는데, 다른 철학자와 출력이 섞이면 안됨
    - 한 철학자가 죽으면 다른 철학자들의 출력이 있으면 안됨

4. DataRace 방지
    - philo class, fork class를 동적할당(new)해서 공유 영역으로 만들어줌
    - 공유영역에 대해서 각각 mutex를 만들어서 lock() 하여 접근함

5. Deadlock 방지
    - 홀수 철학자는 왼쪽 포크부터, 짝수 철학자는 오른쪽 포크부터 잡게 함
    - 짝수 철학자는 처음 시작때 잠깐 쉬었다가 시작함 (각 쓰레드가 실행 시작하는 시점의 차이 때문에 발생하는 대드락 방지)

6. Monitoring
    - main thread에서 철학자들의 상태, 밥먹은 시간, 경과시간을 살피면서 철학자가 죽었는지 다 먹었는지 확인함

7. 실행 방법  
```
$ make all
$ ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
