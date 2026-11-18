## 과제
## 실습과제 1
1. 일반 함수와 람다식의 차이를 자세히 설명하시오. 일반 함수로 정의하는 대신에 람다식을 사용할 때 장점은 무엇인가?
    - 차이점: 일반 함수는 전역이나 클래스 내부에 이름을 가지고 정의되지만, 람다식은 C++11에서 도입된 '이름이 없는 익명 함수'를 만드는 기능이다. 람다식은 일반 함수와 달리 '캡쳐 리스트'를 가지고 있어 함수 외부에서 선언된 변수를 람다 함수 내부에서 쉽게 사용할 수 있음
    - 람다식 사용의 장점: 람다 대수에서 유래한 람다식은 수학 함수를 단순하게 표현하는 기법으로, 복잡한 함수 선언 없이 필요한 곳에서 즉석으로 함수를 정의하고 사용할 수 있고, 특히 캡쳐 리스트를 통해 외부 지역 변수의 값이나 참조를 직접 캡쳐하여 사용할 수 있으므로, 코드의 가독성을 높이고 불필요한 전역 변수나 멤버 변수의 사용을 줄일 수 있음

## 실습과제 2
1. 23페이지 예제처럼 함수에 인자로 람다식을 사용하는 예제를 인터넷에서 찾아서 실행해보고 소스코드를 자세히 설명하시오.
```
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 람다식을 인자로 사용하여 짝수의 개수를 구함
    int even_count = std::count_if(vec.begin(), vec.end(), [](int n) {
        return n % 2 == 0;
    });
    
    std::cout << "짝수의 개수: " << even_count << "개" << std::endl;
    return 0;
}
```

<algorithm> 헤더의 std::count_if 함수는 조건에 맞는 요소의 개수를 세는 함수로, 세 번째 매개변수로 조건을 판별할 '함수(또는 람다식)'를 받음

[](int n) { return n % 2 == 0; } 라는 람다식을 std::count_if의 인자로 직접 전달

이 람다식은 벡터의 각 요소를 인자 n으로 받아 짝수인지 판별하여 true 또는 false를 반환하며, 이를 통해 짝수의 개수를 세고, 외부 함수를 따로 정의할 필요 없이 간결하게 로직을 전달할 수 있음

## 실습과제 3
1. 문제: 함수 포인터와 std::function 객체의 차이를 자세히 설명하시오.
    - 함수 포인터: C언어 시절부터 사용되던 방식으로, 메모리 상에 존재하는 함수의 시작 주소를 가리키는 단순한 포인터이고, 함수 포인터는 시그니처가 일치하는 일반 함수만을 가리킬 수 있으며 객체의 멤버 함수나 상태를 가지는 캡쳐 람다 등을 유연하게 다루기 어려움

    - std::function 객체: <functional> 헤더 파일에 정의된 템플릿 클래스이고, 포인터가 아닌 '객체'이지만 함수 포인터의 역할을 대신하며, 포인터 사용으로 인한 오류를 방지해 줌. 가장 큰 차이점은 일반 함수 주소뿐만 아니라 함수 객체, 람다식, 심지어 멤버 함수까지 '호출이 가능한 모든 것'을 담을 수 있는 범용성을 가진다는 점

## 실습과제 4
1. 3페이지 예제처럼 인터넷에서 std::function 클래스를 함수에 매개변수에 사용한 예제를 찾아서 실행해보고 소스코드를 자세히 설명하시오

```
#include <iostream>
#include <vector>
#include <functional>

// std::function을 매개변수로 사용하여 커스텀 필터링 로직을 전달받는 함수
void filterAndPrint(const std::vector<int>& vec, std::function<bool(int)> filterFunc) {
    for (int num : vec) {
        if (filterFunc(num)) { // 전달받은 함수(또는 람다) 객체 호출
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {10, 15, 20, 25, 30};

    std::cout << "20 이상인 수: ";
    // 람다식을 std::function 매개변수로 전달
    filterAndPrint(numbers, [](int n) { return n >= 20; });

    std::cout << "5의 배수: ";
    // 또 다른 람다식을 전달
    filterAndPrint(numbers, [](int n) { return n % 5 == 0; });

    return 0;
}
```
filterAndPrint 함수는 정수 벡터와 std::function<bool(int)> 타입의 객체 filterFunc를 매개변수로 받음 즉, 정수를 하나 받아 bool을 반환하는 어떠한 형태의 함수나 람다식도 인자로 받을 수 있음

main 함수에서는 filterAndPrint를 호출할 때 각각 "20 이상인지 확인하는 람다식"과 "5의 배수인지 확인하는 람다식"을 전달

이처럼 std::function을 매개변수로 사용하면, 함수의 핵심 동작(순회 및 출력)은 유지한 채 세부 로직(필터링 조건)만 외부에서 람다식으로 유연하게 주입할 수 있어 코드의 재사용성이 크게 향상됨