## 실습과제1 
1. CMake와 GNU Make의 차이점을 설명하라.
    - CMake : 어떻게 빌드할지 결정하고 빌드 시스템을 만들어 주는 도구
    - GNU Make : 만들어진 빌드 규칙을 실제로 실행하는 도구

2. CMakeLists.txt의 역할을 설명하라.
    - CMake 프로젝트의 빌드 설정을 정의하는 파일

3. CMakeCache.txt의 역할을 설명하라.
    - CMake가 Configure 과정에서 결정한 변수와 설정값을 저장하는 캐시 파일

4. Cmake의 각 단계별(configure->generate->build) 결과물을 자세히 설명하라.
    - Configure 단계에서는 CMake가 CMakeLists.txt를 읽고 현재 컴퓨터의 빌드 환경과 프로젝트 설정을 분석
    - Generate 단계에서는 Configure 과정에서 결정된 정보를 바탕으로 실제로 사용할 빌드 시스템 파일을 생성
    - Build 단계에서는 Generate 단계에서 만들어진 빌드 시스템을 실제로 실행하여 소스 코드를 컴파일하고 링크
    
5. 예제1에서 cmake --build build 명령어 대신에 make명령어를 이용하여 빌드 해보시오. Generate단계 후에 hello/build/Makefile이 생성된다. hello/build 디렉토리로 이동 후 make를 실행하면 됨
<img width="898" height="526" alt="스크린샷 2026-10-01 163944" src="https://github.com/user-attachments/assets/8bd1953e-ef05-4b72-b964-977709bc23ba" />

## 실습과제2
1. CMake를 이용하여 2개의 정수를 입력 받아 합을 출력하는 C++프로그램을 작성하시오. 프로젝트의 구조는 다음과 같이 작성하라.
<img width="863" height="377" alt="스크린샷 2026-10-01 164321" src="https://github.com/user-attachments/assets/1e276589-7c32-42b9-857a-88b42fa6e95a" />

CMakeLists.txt
'''
cmake_minimum_required(VERSION 3.16.3)

project(Hello)

add_executable(Hello main.cpp)
'''

main.cpp
'''
#include <iostream>
using namespace std;

int main()
{
    int a, b;

    cout << "첫 번째 정수를 입력하세요: ";
    cin >> a;

    cout << "두 번째 정수를 입력하세요: ";
    cin >> b;

    cout << "합: " << a + b << endl;

    return 0;
}
'''
