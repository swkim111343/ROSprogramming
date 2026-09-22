## 과제
## 실습과제1
1. linear.x : x축 방향 직선 속도
2. linear.y : y축 방향 직선 속도
3. linear.z : z축 방향 직선 속도
4. angular.x : x축을 중심으로 회전
5. angular.y : y축을 중심으로 회전
6. angular.z : z축을 중심으로 회전
## 실습과제2
1. 42B/s : 측정된 평균 데이터 전송량. 1초에 평균 42바이트가 전송됨
2. mean : 여러 측정값의 평균값(Mean)
3. min : 측정 기간 동안 관측된 최소 전송량
4. max : 측정 기간 동안 관측된 최대 전송량
## 실습과제3
1. average rate	: 메시지가 발행되는 평균 주파수(Hz)
2. min : 메시지 사이의 최소 시간 간격(초)
3. max : 메시지 사이의 최대 시간 간격(초)
4. std dev	: 메시지 발행 간격의 표준편차. 발행주기가 얼마나 일정한지 나타냄
5. window : 평균 및 통계 계산에 사용한 최근 메시지 간격의 개수
## 실습과제4
1. turtlesim_node 를 실행하고 새로운 창에서 아래 명령을 실행하고 강의 노트의 rosbag을 제외한 모든 명령어를 실습하고 결과를 캡쳐하여 제출하라

2. 명령과 출력 결과가 일치하는지 설명하라.
$ ros2 topic pub --rate 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"