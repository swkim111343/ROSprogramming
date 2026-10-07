## 실습과제 1
1. 빌드 시스템과 빌드 툴의 차이를 설명하라.
    - 빌드 시스템(Build System): 소스 코드를 컴파일하고 링크하여 실행 파일이나 라이브러리 등을 만들어 주는 시스템
    - 빌드 툴(Build Tool): 여러 패키지의 빌드 과정을 관리하고 실행하는 도구
    - ROS 2에서는 colcon을 사용합니다.
2. 패키지 생성 명령어를 실행하는 위치는 어디이고 그곳으로 이동하는 명령어를 쓰시오.
    - ROS 2 패키지는 워크스페이스의 src 디렉터리에서 생성
    - cd ~/ros2_ws/src

3. 패키지 생성 명령어의 사용법을 설명하라.
    - ros2 pkg create 패키지이름
    - ros2 pkg create --build-type ament_cmake my_package(C++)
    - ros2 pkg create --build-type ament_python my_package(python)

4. 패키지 빌드 명령어를 실행하는 위치는 어디이고 그곳으로 이동하는 명령어를 쓰시오.
    - 패키지 빌드 명령어는 ROS 2 워크스페이스의 최상위 디렉터리에서 실행

5. 패키지 빌드 명령어의 사용법을 설명하라.
    - colcon build
    - colcon build --packages-select my_package(특정패키지만 빌드)
    - colcon build --symlink-install(심볼릭 링크를 사용하여 파이썬 파일 등을 수정했을 때)
    - packages-select my_package(특정 패키지를 심볼릭 링크 방식으로 빌드)


## 실습과제 2
1. 사용자 홈디렉터리 아래에 작업폴더 ros2_ws를 생성하고 강의노트의 패키지 생성 및 빌드 명령어를 실습하고 결과를 제출하시오.

2. 자동으로 생성되는 파일과 디렉터리를 출력하고 각각 설명하시오.
    - CMakeLists.txt : CMake 빌드 설정 파일. 패키지를 어떻게 빌드하고 어떤 라이브러리나 실행 파일을 생성할지 정의
    - package.xml : ROS 2 패키지 정보 및 의존성 설정 파일. 패키지 이름, 버전, 설명, 라이선스, 의존 패키지 등을 정의
    - include/ : C/C++ 패키지에서 사용하는 **헤더 파일(.hpp, .h)**을 저장하는 디렉터리
    - include/my_package/ : 해당 패키지 전용 헤더 파일을 저장하는 디렉터리
    - src/ : **C/C++ 소스 코드(.cpp)**를 저장하는 디렉터리
