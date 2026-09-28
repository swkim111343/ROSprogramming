## 과제
1. 메시지, 토픽, 서비스, 액션, 인터페이스 용어를 명확히 구분하여 설 명하라.
    - 메시지 (Message) : 노드끼리 주고받는 데이터의 형식과 내용
    - 토픽 (Topic) : 노드들이 메시지를 계속해서 송수신하는 통신 채널(비동기, Publish/Subscribe)
    - 서비스 (Service) : 요청(Request)을 보내고 응답(Response)을 받는 통신(동기적 요청/응답)
    - 액션 (Action) : 시간이 걸리는 작업을 요청하고 진행상태와 결과를 받는 통신(비동기, Goal/Feedback/Result)
    - 인터페이스 (Interface) : ROS 2에서 통신에 사용하는 데이터 구조의 정의를 통칭

2. ros2 명령어를 이용하여 turtlesim과 teleop_turtle노드를 각각 실행 하고 현재 실행중인 토픽메시지와 메시지 인터페이스를 출력하시오. 
<img width="1062" height="425" alt="스크린샷 2026-09-28 221954" src="https://github.com/user-attachments/assets/ea7d399d-61c4-42fc-94e6-4309bf68a4ed" />

3. 앞에서 출력한 메시지 인터페이스의 정의를 ros2 명령어를 이용하 여 각각 출력하시오.
