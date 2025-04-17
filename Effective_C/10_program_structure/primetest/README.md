# Prime Number Testing Program (소수 판별 프로그램)

이 프로젝트는 정적 라이브러리를 활용한 소수 판별 프로그램입니다. 소수 판별 기능을 정적 라이브러리로 구현하여 재사용성과 모듈화를 향상시켰습니다.

This project demonstrates a prime number testing program using a static library. The primality test functionality is implemented as a static library to improve reusability and modularity.

## 프로젝트 구조 (Project Structure)

```
primetest/
├── isprime.h      # 라이브러리 헤더 파일
├── isprime.c      # 라이브러리 구현 파일
├── diver.c        # 메인 프로그램
├── bin/
    ├── libPrimalityUtilities.a  # 생성된 정적 라이브러리
    ├── isprime.o                # 라이브러리 오브젝트 파일
    ├── diver.o                  # 메인 프로그램 오브젝트 파일
    └── primetest               # 최종 실행 파일
```

## 라이브러리 구성 (Library Components)

### 정적 라이브러리 (Static Library)
- 이름: `libPrimalityUtilities.a`
- 기능: Miller-Rabin 소수 판별 알고리즘 구현
- 인터페이스: `isprime.h`에 정의
- 구현: `isprime.c`에서 제공

### 메인 프로그램 (Main Program)
- 파일: `diver.c`
- 기능: 명령줄 인터페이스 제공
- 라이브러리 활용: `libPrimalityUtilities.a` 링크

## 빌드 프로세스 (Build Process)

```bash
# 1. 라이브러리 소스 컴파일
gcc -c -std=c17 -Wall -Wextra -pedantic -Werror isprime.c -o bin/isprime.o

# 2. 정적 라이브러리 생성
ar rcs bin/libPrimalityUtilities.a bin/isprime.o

# 3. 메인 프로그램 컴파일
gcc -c -std=c17 -Wall -Wextra -pedantic -Werror diver.c -o bin/diver.o

# 4. 최종 링킹
gcc bin/diver.o -Lbin -lPrimalityUtilities -o bin/primetest
```

## 사용 방법 (Usage)

```bash
./primetest <number1> <number2> ...
```

### 예시 (Example)
```bash
./primetest 17 123 997
17 is prime
123 is not prime
997 is prime
```

## 기술적 특징 (Technical Features)

- 정적 라이브러리를 통한 코드 모듈화
- Miller-Rabin 알고리즘을 이용한 효율적인 소수 판별
- 2부터 ULLONG_MAX(2^64 - 1)까지의 숫자 지원
- 메모리 안전성을 고려한 구현
- 엄격한 입력값 검증 및 에러 처리

## 라이브러리 활용 (Library Usage)

다른 프로젝트에서 이 라이브러리를 사용하려면:
1. `isprime.h` 헤더 파일 포함
2. `libPrimalityUtilities.a` 파일과 함께 링크
3. `-Lpath_to_lib -lPrimalityUtilities` 컴파일 옵션 사용

## 제한사항 (Limitations)

- 입력값은 2 이상의 정수여야 함
- 최대 ULLONG_MAX(2^64 - 1)까지의 숫자만 지원
- Miller-Rabin 테스트의 특성상 매우 큰 수에 대해 확률적 결과 제공
  