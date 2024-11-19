# 1장 프로그램 만들기

# 1-1 프로그램과 C언어

## C 언어의 탄생

프로그래밍 언어 : 컴퓨터가 이해할 수 있는, 정확한 표현의 규칙을 정의해 놓은 것

C언어는 1972년 벨 연구소의 **데니스 리치(Dennis Ritchie)**에 의해 개발 C언어는 유닉스 운영체제를 구현하기 위해 만들어졌으며, 기존의 B언어를 개선하여 더 효율적이고 강력한 기능을 제공

초기의 유닉스는 대부분 어셈블리어로 작성되어 하드웨가 바뀌면 유닉스를 다시 개발해야 하는 문제 →  **하드웨어와 상관없이 사용할 수 있는 고수준 언어로서 하드웨어에 가까운 저수준 프로그래밍도 가능**하게됨

## C언어의 장점

1. **시스템 프로그래밍 가능**
    
    C언어는 운영체제, 컴파일러, 그리고 임베디드 시스템과 같은 시스템 소프트웨어를 프로그래밍하는 데 적합
    
    예를 들어, 메모리 관리나 입출력 장치 제어와 같은 작업을 효율적으로 수행 가능
    
2. **이식성을 갖춘 프로그램을 만들 수 있음**
    
    표준을 지켜 프로그램을 만들면 한 플랫폼에서 개발된 소프트웨어를 다른 플랫폼으로 쉽게 이식할 수 있어, 코드의 재사용성과 유지보수성을 높일 수 있음
    
3. **함수를 사용해 개별 프로그래밍이 가능**
    
    C언어는 함수 단위로 코드를 분할하여 작성할 수 있는 구조적 프로그래밍(복잡한 프로그램을 작은 단위로 나누어 개발)을 지원
    

## 생산성

### 구조적 프로그래밍 기법

구조적 프로그래밍은 코드의 흐름을 제어하기 위해 순차적, 선택적, 반복적 구조를 사용하는 기법

- 데이터와 알고리즘을 분리하여 작성
- 함수 단위로 코드를 작성하여 모듈화
- 사용 예: C 언어

### 객체지향 프로그래밍 기법

객체지향 프로그래밍은 데이터와 그 데이터를 조작하는 알고리즘을 하나의 객체로 묶어 사용하는 기법

- 데이터와 알고리즘을 클래스(객체)로 묶어서 작성
- 상속, 다형성, 캡슐화 등의 원칙을 사용
- 사용 예: C++ 언어

### 프로그램

프로그램은 데이터를 처리하는 알고리즘(로직)으로 구성됩니다. 데이터를 입력받아 처리하고, 결과를 출력하는 일련의 과정

- 데이터: 프로그램이 처리해야 할 정보
- 알고리즘: 데이터를 처리하는 절차나 방법

### 다양한 언어

- Python: 인공지능(AI) 및 데이터 과학에 주로 사용
- Java: 웹 및 엔터프라이즈 애플리케이션 개발에 많이 사용
- C#: 마이크로소프트(MS) 플랫폼을 위한 개발에 사용
- Go: 구글에서 개발한 언어로, 높은 성능과 간결함을 목표로 함
- C: 구조적 프로그래밍에 주로 사용
- C++: 객체지향 프로그래밍에 주로 사용

# 1-2 컴파일과 컴파일러 사용법

## 컴파일 과정

프로그래밍 언어로 작성된 소스 코드 → 기계어 

### 1. 전처리 (Preprocessing)

전처리기는 소스 코드에서 전처리 지시문(#으로 시작하는 지시문)을 처리합니다. 이 과정에서 파일을 포함(#include), 매크로를 정의(#define), 조건부 컴파일(#ifdef, #ifndef) 등의 작업이 수행됩니다. 전처리 결과는 확장된 소스 코드입니다.

### 2. 컴파일 (Compilation)

컴파일러는 전처리된 소스 코드를 분석하여 중간 코드(intermediate code)나 어셈블리 코드(assembly code)를 생성합니다. 개체파일이 됨. cpu가 해석가능한 명령어로 이루어진 기계어 파일이지만, OS에 의해 실행되므로 개체 파일을 설치된 OS가 인식할 수 있는 실행 파일로 바꿔야함.

- **어휘 분석 (Lexical Analysis):** 소스 코드를 토큰(token)으로 분할합니다.
- **구문 분석 (Syntax Analysis):** 토큰의 구조를 검사하여 구문 트리(parse tree)를 생성합니다.
- **의미 분석 (Semantic Analysis):** 구문 트리를 기반으로 의미를 검사하고, 중간 코드를 생성합니다.

### 3. 최적화 (Optimization)

생성된 중간 코드나 어셈블리 코드는 최적화 과정을 거쳐 성능이 향상됩니다. 이 과정에서는 불필요한 코드가 제거되거나, 더 효율적인 코드로 대체됩니다. 최적화는 컴파일러의 선택적인 단계로, 다양한 최적화 기법이 적용될 수 있습니다.

### 4. 어셈블리 (Assembly)

어셈블러는 어셈블리 코드를 기계어로 변환합니다. 이 단계에서는 어셈블리 코드를 바이너리 코드로 변환하여 객체 파일(object file)을 생성합니다.

### 5. 링크 (Linking)

링커는 개체 파일에 startup code를 결합함. 여러 객체 파일과 라이브러리 파일을 결합하여 실행 파일(executable)을 생성합니다. 이 과정에서 각 객체 파일의 심볼(symbol)을 해석하고, 필요한 라이브러리를 포함시킵니다. 링크 과정은 다음과 같은 하위 단계를 포함합니다.

- **심볼 해결 (Symbol Resolution):** 각 객체 파일의 심볼을 해석하고, 참조된 모든 심볼이 정의되어 있는지 확인합니다.
- **재배치 (Relocation):** 각 객체 파일의 주소를 조정하여 실행 파일의 메모리 레이아웃을 결정합니다.

### 구현체에 정의된 동작:

이 동작은 C나 C++ 표준에 의해 강제되지 않지만, 특정 컴파일러나 시스템의 구현체에서 정의된 동작입니다. 즉, 같은 코드를 다른 컴파일러나 플랫폼에서 실행하면 결과가 달라질 수 있습니다. 이는 코드의 이식성을 떨어뜨리는 주요 요인이 될 수 있습니다.

### 미지정 동작 (Unspecified Behavior):

여러 가지 동작이 가능한 상황에서 표준이 특정한 결과를 지정하지 않고, 구현체에 따라 다르게 동작하도록 한 것을 말합니다. 예를 들어 함수 인자의 평가 순서가 미지정되어 있으면, 구현체마다 다르게 평가될 수 있습니다.

### 미정의 동작 (Undefined Behavior):

프로그램이 표준에 의해 규정되지 않은 방식으로 동작할 때 발생합니다. 예를 들어, 배열의 경계를 벗어난 접근이나 0으로 나누는 등의 행동은 미정의 동작을 유발할 수 있습니다. 이 경우, 프로그램이 충돌하거나 예상치 못한 결과를 생성할 수 있어 이식성이 크게 저하됩니다.

### 로케일별 동작:

프로그램이 실행되는 환경의 로케일(지역 설정)에 따라 다른 결과를 생성하는 동작입니다. 예를 들어, 문자열의 정렬 순서나 날짜 형식 등이 로케일에 따라 다를 수 있으며, 이는 프로그램의 이식성을 제한할 수 있는 요소가 됩니다.

### 공통 확장:

많은 컴파일러나 시스템에서 제공하는 비표준 확장 기능을 의미합니다. 이러한 확장은 편리하게 사용할 수 있지만, 표준을 따르지 않기 때문에 다른 시스템에서 해당 기능이 동작하지 않을 수 있습니다. 이는 코드의 호환성과 이식성을 저해할 수 있습니다.