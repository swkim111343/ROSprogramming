## 과제
1. 메타운영체제, 소프트웨어 플랫폼, 프레임워크, 미들웨어에 대하여 각각 설명하라.
    - 메타운영체제 : 분산 컴퓨팅 자원을 활용하여, 스케쥴링, 로드, 감시, 에러 처리 등을 실행 하는 시스템으로, 기 존의 전통적인 운영체제(리눅스, 윈도우)를 이용한 응용 프로그램이다. 컴파일러, 스레드 모델등을 사용하고, 로봇 응용 소프트웨어 개발을 위한 필수기능들을 라이브러리 형태로 제공한다.

    - 소프트웨어 플랫폼 :  로봇을 제어하고 다양한 기능을 개발할 수 있도록 필요한 도구와 환경을 제공하는 기반(센서, 카메라, 모터 등 하드웨어-소프트웨어간 연결 지원)이고 대표적으로 ROS/ROS2가 있다.(ROS2는 그냥 새로운 버전 이라고 생각하면 됨)

    - 미들웨어 : 운영체제와 응용 프로그램 사이에서 통신하고 데이터를 주고 받게 하는 소프트웨어로, 예를들어 ROS2에서는 DDS(data distriburion service)를 기반으로 노드간 통신을 수행

    - 프레임워크 : 특정 목적의 sw를 개발하기 위해 미리 만들어진 구조, 기능 제공하는 개발 

2. DDS에 대하여 조사하고 ROS에서 DDS의 역할은 무엇인가?
    - DDS : 여러 프로그램이서로데이터를 주고받게 해주는 통신 시스템(카메라 영상이 있으면 객체 인식 프로그램에 직접 연결되는 것이 아니라, dds가 중간에서 데이터 전달을 담당한다.)

    - DDS는 publisher(발행자), Subscriber 구조를 사용(카메라 -> a데이터를 publish, 객체 인식-> a데이터를 subscribe), 네트워크 통신 참여자들을 자동발견, Qos(Quality of Service) 특징이 있다.

    - ROS 에서의 DDS 역할 : 
    

   ROS 2 응용 프로그램                 ROS 2 Middleware 
   Node / Topic / Service     ->            DDS                 ->          Network / OS  
   Action                 

    ROS 2가 로봇 소프트웨어 개발을 위한 프레임워크라면, DDS는 ROS 2의 통신을 담당하는 미들웨어이다

- 각 Node가 서로 직접 통신하는 것이 아니라 ROS 2가 DDS를 이용하여 데이터를 전달하는 방식 -> 개발자는 네트워크 통신을 처음부터 직접 구현하지 않고 ROS 2의 Topic, Service, Action 등을 이용해서 로봇 프로그램을 개발할 수 있다.

3. ROS를 응용한 제품 또는 자율주행 프로젝트 사례를 3가지 이상 조사하라. 산업계에서 실제로 얼마나 많이 사용하는지 확인해볼 것
- BMW는 공장 내부에서 부품과 컨테이너를 운반하기 위한 Smart Transport Robot(STR)을 개발했다.
  <img width="2250" height="1500" alt="c1QVhpJw-UzbfTJJBfwyVVP5-OQc0D0mYvEcxAUDs7NPWE-DYQeVRsJ6tJgH_Y_k_wlbrJMgutlFY887H2UQS2z2KOQX1XitLLjj9AQe1lp9h1H7ceChQo9CNl4mUeGAPSjgSBnED9C72gE09XbHDSNATBNWFqc3rxv7X36mBP6P4qCsFjgmGV2mm1P3I9ee" src="https://github.com/user-attachments/assets/98d2c251-43aa-4ba1-abd2-f94fa2158691" />


- 쿠팡은 물류센터에서 AGV(Automated Guided Vehicle), AI, 자동 포장·분류 시스템 등
  <img width="610" height="458" alt="4c9dLmpWELovDZdm9uPLL9zpEBEXC6mQ-qMW-YF_2XkqVnrMS3vJmyj8ap20FufGsaYEAHfuYrdHeYj-aVj1Nsnj0C0FMwcNzL88p_jDmkyV_o7OKrn9z_3-yVMCW_1_FY4Hr1UemTAtCkFYBEWghCtgl1zelSFRMlpTZclKU9UUQO5O8xx-q9jmlFjIo_X6" src="https://github.com/user-attachments/assets/a805e256-a3aa-41f8-b2e0-54527cf5daad" />
