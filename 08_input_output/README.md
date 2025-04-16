# 입출력

## 표준 입출력 스트림
stream : 소켓, 키보드, usb포트, 프린터 등과 같이 순차 데이터를 사용하거나 생성하는 파일 및 장치와 통신하기 위한 균일한 추상화

FILE 형식 : 파일 위치 지시자, 버퍼링 정보, 오류 표시기, 파일 끝 지시자 등 내부 상태 정보가 있음

FILE * :  FILE형식 개체에 대한 포인터, 파일 포인터

## 스트림 버퍼링
buffering : 프로세스와 장치 또는 파일 간에 전달되는 데이터를 주 메모리에 임시로 저장하는 프로세스

대기 시간이 많은 입출력 연산의 처리량을 개선

각 파일에 대해 입력버퍼와 출력버퍼를 사용한다.

스트림의 상태
  - 버퍼링되지 않는 : 가능한 빨리 표시하기 위한 것, 오류 보고나 로깅에 사용되는 스트림은 버퍼링 되지 않을 수 있다.
  - 완전히 버퍼링 된 : 블록단위로 전송하기 위해 버퍼가 채워질때 까지 대기후 전송 -> 파일 입출력
  - 줄 버퍼링된 : 줄 바꿈 문자를 만났을 때 블록으로 전송(라인버퍼링) -> 터미널

## 미리 정의된 스트림
`<stdio.h>`에 선언됨
```c
extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;
```
- stdout
  ```bash
  $ echo fred
  fred

  $ echo fred > tempfile
  $ caft tempfile
  fred
  ```
  echo 명령의 출력이 tempfile로 리디렉션됨

- stdin
  ```bash
  $ echo "one two thre four five six seven" > fred
  $ wc < fred
  1 7 34
  ```
  fred의 내용은 ws 명령의 stdin으로 리디렉션돼 fred로 부터 줄 바꿈과 단어, 바이트 수를 출력함

- stderr
  완전히 버퍼링 되지 않음. 

##  **C 언어의 표준 스트림 I/O 시스템에서 "스트림 방향(stream orientation)"** 

스트림은 **표현 범위가 좁은 문자용**(`char`) 또는 **표현 범위가 넓은 문자용**(`wchar_t`)으로 **한 번 결정되면 변경 불가**이다. 이를 **스트림의 방향**이라고 부른다.


### 2. 방향의 결정 시점

- `fopen()` 또는 `freopen()`으로 파일을 열면, 처음엔 **방향이 미지정(indeterminate)** 상태
- 아래 함수 중 하나를 처음 사용한 시점에 방향이 **자동 결정**됨:

| 함수 종류                  | 스트림 방향 설정 |
|----------------------------|------------------|
| 좁은 문자 함수 (`fputs`, `fscanf`, `fprintf`, ...) | 좁은 문자 스트림 |
| 넓은 문자 함수 (`fputws`, `fwscanf`, `fwprintf`, ...) | 넓은 문자 스트림 |

**한 번 정해지면, 스트림을 닫기 전까지는 변경할 수 없다.**



### 3. 스트림 방향 확인 함수

```c
#include <wchar.h>

int fwide(FILE *stream, int mode);
```

### 사용법
- `fwide(fp, 0)` → 방향 확인 (양수면 wide, 음수면 narrow, 0이면 미정)
- `fwide(fp, 1)` → 넓은 문자 스트림 설정 시도
- `fwide(fp, -1)` → 좁은 문자 스트림 설정 시도

```c
FILE *fp = fopen("test.txt", "w");
printf("%d\n", fwide(fp, 0)); // 0: 방향 미지정
fputws(L"안녕\n", fp);        // 넓은 문자 출력 → 방향 결정됨
printf("%d\n", fwide(fp, 0)); // >0: 넓은 문자 스트림
```


### 4. 혼용 금지: 정의되지 않은 동작

  (1) **좁은 문자 스트림에 `wchar_t` 함수 사용**  → **정의되지 않은 동작 (undefined behavior)**

  (2) **넓은 문자 스트림에 `char` 함수 사용**  → **정의되지 않은 동작**

  (3) **같은 파일에 `char`, `wchar_t`, 이진 데이터를 섞어 저장**  → **실행 환경이나 로케일에 따라 파싱 불가능** 또는 **파일 포맷 오류 발생 가능**

  ```c
  fputs("ABC", fp);           // 좁은 문자 함수
  fputws(L"한글", fp);        // 넓은 문자 함수 → 잘못된 혼용
  ```


### 5. 방향 초기화 해제 방법

- 스트림 방향은 **파일을 닫으면 초기화**됨.
- `fclose()` 후 다시 `fopen()` 하면 스트림 방향을 새로 설정할 수 있다.

### 텍스트 및 이진 스트림

  > 텍스트 스트림 (Text Stream)

  **줄(line)**로 구성된 **문자 시퀀스**. 각 줄은 0개 이상의 문자 + **줄바꿈(newline) 문자 시퀀스**로 이루어짐.

  - 예: `"abc\n"` → 3개 문자 + 줄바꿈
  - **플랫폼 의존적 변환 있음**:
    - Windows: 줄바꿈 `\n` → 실제 파일에 `\r\n` 저장
    - Unix/Linux: `\n` → 그대로 `\n` 저장
  - 개행 문자나 텍스트 모드 파일에서 일부 문자 변환은 **자동 처리**


  | 항목                  | 설명                                 |
  |-----------------------|--------------------------------------|
  | 단위                 | 줄 (line)                            |
  | 변환 여부            | 있음 (`\n` ↔ 플랫폼 줄바꿈 시퀀스)   |
  | NULL 바이트 (`\0`)    | 허용되지 않음                        |
  | 이식성               | 높음 (문자 기반 텍스트 처리에 적합)  |
  | 사용 예              | `fopen("file.txt", "r")` 등 텍스트 모드 |


  > 이진 스트림 (Binary Stream)

  **임의의 바이트 시퀀스**, 줄 단위 개념 없음. **데이터 그대로 저장되고 읽힘**.

  - 예: 구조체, 이미지, 바이너리 포맷, 실행파일 등


  | 항목                 | 설명                              |
  |----------------------|-----------------------------------|
  | 단위                | 바이트(byte), 줄 개념 없음        |
  | 변환 여부           | 없음 (있는 그대로 처리)           |
  | NULL 바이트         | 포함 가능                         |
  | 이식성              | 낮음 (엔디안, 구조체 정렬 등 문제) |
  | 사용 예             | `fopen("file.bin", "rb")`          |

  ```c
  #include <stdio.h>

  int main() {
      FILE *fp = fopen("test.txt", "w");     // 텍스트 스트림
      fprintf(fp, "ABC\nDEF\n");             // 줄바꿈 변환됨
      fclose(fp);

      FILE *fb = fopen("test.bin", "wb");    // 이진 스트림
      char bin[5] = {'A', 0, 'B', 0, 'C'};
      fwrite(bin, 1, sizeof(bin), fb);       // 그대로 기록됨
      fclose(fb);
      return 0;
  }
  ```

## 파일 열기 및 만들기



  ### `fopen()`
  ```c
  FILE *fopen(const char *filename, const char *mode);
  ```
  - 지정된 **파일 이름**과 **접근 모드**로 스트림을 열고, `FILE*` 포인터를 반환.
  - 실패 시 `NULL` 반환.
  - 성공: `FILE*`  
  - 실패: `NULL`, 그리고 `errno` 설정됨 (`perror()`로 확인 가능)

  접근모드
  | 모드     | 의미                           | 파일이 존재할 때      | 존재하지 않을 때         |
  |----------|--------------------------------|------------------------|---------------------------|
  | `"r"`    | 읽기 전용                      | 시작부터 읽음          | 실패                      |
  | `"w"`    | 쓰기 전용                      | 기존 내용 삭제         | 새로 생성                 |
  | `"a"`    | 추가 전용                      | 파일 끝에 추가         | 새로 생성                 |
  | `"r+"`   | 읽기/쓰기                      | 시작부터 읽고 쓸 수 있음 | 실패                     |
  | `"w+"`   | 읽기/쓰기                      | 내용 삭제 후 새로 씀    | 새로 생성                 |
  | `"a+"`   | 읽기/쓰기 (추가 모드)          | 읽기 가능, 쓰기는 항상 끝에 | 새로 생성            |

  추가 플래그:
  - `"b"`: 바이너리 모드 (`"rb"`, `"wb"`, etc.)  
  - `"x"`: `w`/`w+` 모드에서 파일이 있으면 **열기 실패**
  - `"u"`: `w`/`a`에서 디폴트 파일 권한 적용 (C11 확장)


  ```c
  FILE *fp = fopen("example.txt", "r");
  if (!fp) {
      perror("파일 열기 실패");
      return 1;
  }
  ```

  - `fopen()`은 **널 포인터, 잘못된 모드 등 입력 오류를 검출하지 않음** → 런타임 오류 발생 가능
  - 파일 열기 성공 후 `FILE*`는 반드시 `fclose()`로 닫아야 함



  ### `fopen_s()` (C11 확장, bounds-checked)
  ```c
  errno_t fopen_s(FILE **streamptr, const char *filename, const char *mode);
  ```

  - `fopen()`과 기능은 같지만, **입력 유효성 검사 강화**
  - 실패 시 `*streamptr = NULL`로 보장됨
  - 제약 조건 위반 시 **제약 처리기 함수 호출** (`abort`, `ignore`, etc.)

  제약 조건 (어기면 오류)

  | 조건                        | 동작                         |
  |-----------------------------|------------------------------|
  | `streamptr == NULL`         | 오류 + 제약 처리기 호출      |
  | `filename == NULL`          | 오류 + 제약 처리기 호출      |
  | `mode == NULL`              | 오류 + 제약 처리기 호출      |


  반환값

  | 반환값 | 의미                             |
  |--------|----------------------------------|
  | `0`    | 성공                             |
  | 비 0   | 실패 (`errno.h`에서 정의된 값)   |


  - 아래 매크로 정의가 `<stdio.h>` **포함 전에 있어야** `fopen_s()` 사용 가능
  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <stdio.h>

  int main() {
  #ifdef __STDC_LIB_EXT1__
      FILE *fp = NULL;
      errno_t err = fopen_s(&fp, "log.txt", "w");

      if (err != 0 || fp == NULL) {
          perror("파일 열기 실패");
          return 1;
      }

      fputs("hello\n", fp);
      fclose(fp);
  #else
      puts("fopen_s는 이 구현에서 지원되지 않음");
  #endif
      return 0;
  }
  ```


  ### `open()` 
  > `open()`은 파일을 열어서 **파일 디스크립터(file descriptor)**를 얻는 시스템 호출

  ```c
  #include <fcntl.h>
  int open(const char *pathname, int flags, ... /* mode_t mode */);
  ```

  - `pathname`: 열 파일 경로
  - `flags`: 파일 열기 옵션 (필수)
  - `mode`: 파일 생성 시 접근 권한 (선택, `O_CREAT` 사용 시 필요)
  - 성공 시: **0 이상 정수**인 파일 디스크립터 반환
  - 실패 시: **-1 반환**, `errno`에 에러 코드 설정됨

  `flags`에는 **접근 모드(access mode)** 하나만 반드시 지정

  | 플래그      | 설명                      |
  |-------------|---------------------------|
  | `O_RDONLY`  | 읽기 전용                  |
  | `O_WRONLY`  | 쓰기 전용                  |
  | `O_RDWR`    | 읽기 + 쓰기                |

  `flags`에 OR 연산으로 같이 붙이는 부가 옵션들:

  | 플래그        | 설명 |
  |---------------|------|
  | `O_CREAT`     | 파일 없으면 생성 (`mode` 인자 필수) |
  | `O_EXCL`      | `O_CREAT`와 함께 사용: 이미 있으면 실패 |
  | `O_TRUNC`     | 기존 파일 내용 0으로 자름 |
  | `O_APPEND`    | 항상 파일 끝에 추가 |
  | `O_CLOEXEC`   | `exec()` 이후 자동 close됨 (`FD_CLOEXEC` 플래그 설정) |
  | `O_SYNC`   | write 시 데이터 + 메타데이터 즉시 디스크로 flush |
  | `O_DSYNC`  | write 시 데이터만 flush |
  | `O_RSYNC`  | 읽기 시 동기화도 보장 (희귀 사용) |
  | `O_NOFOLLOW`   | 심볼릭 링크 무시 (링크면 열기 실패) |
  | `O_DIRECTORY`  | 디렉토리가 아니면 열기 실패 |
  | `O_NOCTTY`     | 터미널이 제어 터미널로 설정되지 않음 |
  | `O_NONBLOCK`   | 비차단 I/O 모드로 열기 |


  세 번째 인자 `mode`
  - `O_CREAT` 플래그가 설정되면 **파일 권한 지정**을 위해 `mode_t` 인자를 세 번째 인자로 줘야 함.
  - 이 권한은 **umask**와 연산되어 적용됨.

  ```c
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  // rw-r--r--
  ```


  자주 만나는 errno 예시:

  | errno      | 의미 |
  |------------|------|
  | `EACCES`   | 권한 없음 |
  | `EEXIST`   | `O_CREAT | O_EXCL` 조합 시 이미 파일 존재 |
  | `ENOENT`   | 존재하지 않는 파일 열기 시도 |
  | `ENOTDIR`  | 경로 중 디렉토리가 아님 |
  | `EISDIR`   | 디렉토리를 쓰기 모드로 열려 함 |
  | `EROFS`    | 읽기 전용 파일 시스템에 쓰기 시도 |



  ```c
  int fd = open("mylog.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
      perror("open failed");
      return 1;
  }
  write(fd, "Hello!\n", 7);
  close(fd);
  ```

  ```c
  int fd = open("lockfile", O_WRONLY | O_CREAT | O_EXCL, 0600);
  if (fd == -1) {
      perror("lock failed");
      exit(1);
  }
  ```

  ---

  > openat()

  - `open()`은 **절대 경로** 또는 **현재 디렉토리 기준 상대 경로**로 파일을 염
  - `openat()`은 디렉토리 디스크립터 기준으로 **상대 경로** 파일을 염 → race condition 방지 가능

  ```c
  int dirfd = open("/etc", O_DIRECTORY);
  int fd = openat(dirfd, "passwd", O_RDONLY);
  ```



  > `fclose()` 

  ```c
  #include <stdio.h>
  int fclose(FILE *stream);
  ```

  - **역할**: 열린 파일 스트림을 닫고, 관련된 리소스를 정리함
  - **기본 동작**:
    - **쓰기 버퍼가 남아 있다면 → 자동으로 flush** (OS에 전달)
    - **읽기 버퍼가 남아 있다면 → 자동으로 폐기**
    - 파일과 연결된 버퍼도 메모리에서 해제됨
    - 파일 디스크립터도 닫힘 (`close(fd)` 호출되는 효과)

  | 항목                    | 설명 |
  |-------------------------|------|
  | 매개변수 `FILE *stream` | `fopen()` 등으로 연 파일 포인터 |
  | 성공 시 반환값         | `0` (정상 종료) |
  | 실패 시 반환값         | `EOF` (`-1`) |
  | 실패 예시               | 이미 닫힌 파일, 디스크 오류 등 |
  | `fclose()` 이후         | 해당 스트림 사용은 **정의되지 않은 동작(UB)** |


  내부적으로 하는 일

  1. **쓰기 버퍼**가 존재할 경우:
    - 남은 데이터를 `write()` 시스템 콜을 통해 OS에 전달
  2. **읽기 버퍼**가 남아 있어도 → 폐기됨
  3. 스트림 구조체 내부 해제 (파일 디스크립터 포함)
  4. `setbuf`, `setvbuf`로 설정된 버퍼도 해제됨



  ```c
  #include <stdio.h>

  int main(void) {
      FILE *fp = fopen("hello.txt", "w");
      if (!fp) {
          perror("fopen");
          return 1;
      }

      fprintf(fp, "안녕하세요!\n");
      if (fclose(fp) == EOF) {
          perror("fclose");
          return 1;
      }

      return 0;
  }
  ```

  🔸 이때 `fclose()`를 호출하지 않으면 버퍼가 비워지지 않아 실제로 **파일에 내용이 쓰이지 않을 수 있음**.

  
  - 파일을 닫지 않으면:
    - 버퍼가 비워지지 않아 데이터 손실 발생 가능
    - 열린 파일 디스크립터 누적으로 **리소스 고갈**
    - 디버깅 시 의도치 않은 **파일 손상, 충돌**

  | 실수 | 설명 |
  |------|------|
  | `fclose()` 없이 `return` | 버퍼가 flush 안 될 수 있음 |
  | 두 번 `fclose()` 호출 | 정의되지 않은 동작 (UB) 발생 가능 |
  | 닫은 파일 포인터 재사용 | 세그멘테이션 오류 위험 |

  > `close()`
  ```c
  #include <unistd.h>
  int close(int fildes);
  ```
  - 열린 **파일 디스크립터(file descriptor)**를 닫고, **커널 리소스를 해제**하는 시스템 콜
  - `fildes`는 `open()`, `socket()`, `dup()` 등으로 얻은 정수형 파일 디스크립터
  - 성공 시 `0`, 실패 시 `-1` 반환 (에러는 `errno`로 구체화)


  일반 파일 닫기 동작 순서

  1. `fildes`가 가리키는 open file description 참조 수 1 감소
  2. 0이 되면 실제로 리소스 해제 (inode, buffer, file offset 등)
  3. `unlink()` 후 참조 수가 0이면 디스크에서도 제거

  | 케이스 | 설명 |
  |--------|------|
  | `EINTR` | 시그널에 의해 인터럽트되면 실패 (`errno = EINTR`) — 결과는 **미정** |
  | `EIO`   | 닫는 도중 I/O 오류 발생 (예: NFS) — 상태는 **미정** |
  | 파일이 아직 mmap 되어 있으면 | `close()` 이후에도 삭제되지 않음 (참조 유지됨) |
  | socket + linger 옵션 | linger 시간이 남아있으면 `close()`가 **block**됨 |
  | FIFO | 한쪽이 닫히면 다른 쪽 읽기/쓰기 오류 발생 |
  | pseudo-terminal | master 닫히면 slave에 `SIGHUP` 보냄 |


  닫기 후 재사용 주의

  - `close(fd)` 이후 해당 `fd`는 **더 이상 유효하지 않음**
  - 이후 **`open()` 등이 해당 번호를 재사용할 수 있음**
  - 특히 `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO` (0, 1, 2번)는 **절대 닫고 방치하지 말 것**
    - 오류 메시지나 로그가 다른 FD에 출력되거나, 아예 출력되지 않을 수 있음

  ```c
  int fd = open("example.txt", O_RDONLY);
  if (fd == -1) {
      perror("open");
      return 1;
  }

  if (close(fd) == -1) {
      perror("close");
      return 1;
  }
  ```



  ```c
  int fd = open("log.txt", O_WRONLY | O_CREAT, 0644);
  if (fd == -1) return 1;

  dup2(fd, STDOUT_FILENO); // 표준출력을 파일로
  close(fd);               // 더 이상 필요 없는 원본 FD 해제
  ```

## 문자와 줄을 읽고 쓰기

  ### `fputc()` / `putc()` 
  ```c
  #include <stdio.h>

  int fputc(int ch, FILE *stream);
  int putc(int ch, FILE *stream);
  ```

  | 항목            | 설명 |
  |-----------------|------|
  | **기능**        | `ch` 문자를 `stream`에 출력 (문자 하나 출력) |
  | **매개변수**    | `ch` → 출력할 문자 (단, `int`로 받고 내부적으로 `unsigned char`로 변환)<br>`stream` → 출력 대상 스트림 (`stdout`, 파일 등) |
  | **반환값**      | 성공 시 출력된 문자<br>실패 시 `EOF` 반환 및 `ferror()`로 오류 확인 가능 |
  | **헤더**        | `<stdio.h>` |


  `putc()` vs `fputc()` 차이점

  | 항목            | `putc()`                     | `fputc()` |
  |-----------------|------------------------------|-----------|
  | **정의**        | 매크로일 수도 있음           | 함수로 정의됨 |
  | **성능**        | 일부 시스템에서 약간 빠름     | 일반적인 호출 |
  | **안정성**      | **인자에 부작용 있으면 주의** (`putc(c++, stream)` ❌) | 안전함 |
  | **멀티스레드**  | 일부 구현에서 **비권장**      | 안전 |


  - `int ch`를 `unsigned char`로 변환한 뒤 스트림에 기록함.
  - 실패 시 `EOF` 반환하고, 해당 스트림에 오류 플래그가 설정됨.
  - 이 플래그는 `ferror(FILE *stream)`로 확인 가능

  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main(void) {
      int ret_code = 0;

      for (char c = 'a'; (ret_code != EOF) && (c != 'z'); c++) {
          ret_code = putc(c, stdout); // 또는 fputc(c, stdout);
      }

      if (ret_code == EOF && ferror(stdout)) {
          perror("putc() 오류 발생");
          fprintf(stderr, "putc() 실패: 파일 %s, 라인 %d\n", __FILE__, __LINE__ - 7);
          exit(EXIT_FAILURE);
      }

      putc('\n', stdout);
      return EXIT_SUCCESS;
  }
  ```

  ```
  abcdefghijklmnopqrstuvwxy
  ```


  1. **`putc(stream++)` 또는 `putc(f(), stream)` 형태로 쓰면 안 됨**
    - `putc()`는 매크로로 구현되면 인자를 **여러 번 평가**할 수 있음.
    - 안전하게 사용하려면 변수로 넘겨야 함.

  2. **`EOF`와 문자의 -1 혼동 주의**
    - 반환값이 `int`인 이유는 `EOF(-1)`와 정상 문자 `'\xFF'` (== 255)와 구분하기 위해서임.


  ### `fputs()` 

  ```c
  #include <stdio.h>
  int fputs(const char *str, FILE *stream);
  ```

  | 항목        | 내용 |
  |-------------|------|
  | **기능**    | null-종단 문자열 `str`을 스트림 `stream`에 **줄바꿈 없이** 출력 |
  | **매개변수**| `str` → 출력할 문자열 (null로 끝나야 함)<br>`stream` → 출력 대상 스트림 (예: `stdout`, 파일 포인터 등) |
  | **반환값**  | 성공 시 **0 이상 정수**, 실패 시 **`EOF` 반환** 및 `ferror()`로 확인 |
  | **종료 문자** | `'\0'` (null 문자)는 **출력하지 않음** |
  | **헤더**    | `<stdio.h>` |

  - 문자열의 각 문자를 `fputc()`로 반복 호출하여 출력하는 것과 같은 효과.
  - 문자열 끝에 자동으로 `'\n'`을 붙이지 않음.

  ```c
  fputs("abc", stream);     // 출력: abc
  puts("abc");              // 출력: abc\n
  ```

  `fputs()` vs `puts()` 비교

  | 항목       | `fputs()`                            | `puts()`                            |
  |------------|---------------------------------------|-------------------------------------|
  | **줄바꿈** | 자동 줄바꿈 없음                      | 출력 후 자동으로 `'\n'` 추가        |
  | **출력 대상** | 지정된 스트림 (`FILE *stream`)         | 무조건 `stdout`                     |
  | **유연성** | 파일 등 다양한 스트림 지원             | 콘솔 출력에만 사용 가능            |
  | **표준화** | ANSI C, POSIX, C99에서도 표준 함수     | 동일하게 표준 함수지만 단순 용도에 적합 |



  ```c
  #include <stdio.h>

  int main(void) {
      int rc = fputs("Hello World", stdout);

      if (rc == EOF)
          perror("fputs()");
  }
  ```

  ```
  Hello World
  ```

  ※ `puts()`를 사용하면 자동으로 개행됨:
  ```c
  puts("Hello World"); // Hello World\n
  ```

  주의사항

  1. `str`은 반드시 **null-종단 문자열**이어야 함.  
    → null(`'\0'`) 문자는 **출력되지 않음**.

  2. `fputs()`는 줄바꿈을 하지 않기 때문에, 다음 출력이 같은 줄에 이어질 수 있음.  
    → 필요시 명시적으로 `\n` 포함해서 출력할 것.

  3. 실패 시 `EOF`를 반환하고 `ferror(stream)`로 오류 플래그를 확인 가능.



  ### `fgetc()` / `getc()` 

  ```c
  #include <stdio.h>

  int fgetc(FILE *stream);
  int getc(FILE *stream);
  ```

  | 항목          | 설명 |
  |---------------|------|
  | **기능**      | 지정한 **스트림으로부터 문자 하나를 읽음** |
  | **매개변수**  | `FILE *stream` → 입력 받을 대상 스트림 (ex. `stdin`, 파일 등) |
  | **반환값**    | 읽은 문자 (0~255) → `unsigned char`를 `int`로 변환한 값<br>실패 시 `EOF` 반환 |
  | **헤더**      | `<stdio.h>` |
  | **종료 조건** | `EOF` 반환되면 파일 끝이거나 오류 |



  - 내부적으로 `getc()`는 `fgetc()`와 **기능이 동일**하지만,
  - `getc()`는 **매크로로 구현될 수 있으므로**, 인자로 전달된 `stream`이 **부작용(side effect)**이 있는 표현식이면 **예상치 못한 동작이 생길 수 있음**.

  - 반환형은 `**int**`인 이유는, `unsigned char`의 범위를 넘는 **특수 값 `EOF` (-1)** 를 표현하기 위함.
  - 따라서 `char` 타입 변수로 받으면 `EOF`를 정확히 구분할 수 없음!

  ```c
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
      putchar(ch);
  }
  ```


  | 항목         | `fgetc()`                         | `getc()`                         |
  |--------------|-----------------------------------|----------------------------------|
  | 구현 방식    | 보통 함수                         | 매크로일 수도 있음               |
  | 평가 횟수    | `stream` 한 번만 평가             | 여러 번 평가될 수 있음          |
  | 안전성       | 항상 안전                         | 표현식 부작용 주의 필요         |
  | 성능         | 보통 `getc()`가 더 빠름 (매크로) | 내부적으로 매크로로 최적화 가능 |


  ```c
  #include <stdio.h>
  #include <stdlib.h>

  int main(void) {
      FILE *fp = fopen("test.txt", "r");
      if (!fp) {
          perror("파일 열기 실패");
          return EXIT_FAILURE;
      }

      int ch;
      while ((ch = fgetc(fp)) != EOF)
          putchar(ch); // 하나씩 출력

      if (ferror(fp))
          puts("입력 중 에러 발생");
      else if (feof(fp))
          puts("\n파일 끝 도달");

      fclose(fp);
      return EXIT_SUCCESS;
  }
  ```

 (파일 내용이 `abc\n`일 경우):

  ```
  abc
  파일 끝 도달
  ```

  1. 반환값은 `int`로 받고, 항상 `EOF`와 비교해야 한다.
  2. `getc()`는 매크로로 구현될 수 있으니 `stream++` 같이 부작용 있는 표현은 피하자.
  3. 파일 끝인지 오류인지는 `feof()`, `ferror()`로 구분하자.



  ### `fgets()` 

  ```c
  #include <stdio.h>

  char *fgets(char *str, int count, FILE *stream);
  ```

  | 항목           | 설명 |
  |----------------|------|
  | **기능**       | `stream`에서 **최대 `count-1`개의 문자**를 읽어 `str`에 저장하고 마지막에 **null 문자('\0')**를 추가 |
  | **정지 조건**  | 1) 줄바꿈 문자 `\n`을 만나면<br>2) `count - 1`개를 읽으면<br>3) `EOF` 만나면 |
  | **줄바꿈 처리**| `\n`도 문자열에 **포함**됨 (따라서 문자열 안에 줄바꿈 있음!) |
  | **반환값**     | 성공: `str` 포인터<br>실패: `NULL` (예: 에러, 아무것도 못 읽고 `EOF`) |
  | **헤더**       | `<stdio.h>` |


  ```c
  char buffer[16];
  fgets(buffer, sizeof(buffer), stdin);
  ```

  - 최대 `15`개의 문자 읽고 `buffer[15]`에 `'\0'` 저장
  - 개행 문자가 있으면 **그 문자까지 포함**해서 종료
  - 줄 끝에 도달하지 않아도 **버퍼 크기 초과 시 다음 호출에서 이어 읽음**


  ```c
  #include <stdio.h>

  int main(void) {
      char buf[10];
      FILE *fp = fopen("sample.txt", "r");

      if (!fp) return 1;

      while (fgets(buf, sizeof(buf), fp)) {
          printf("읽은 문자열: \"%s\"\n", buf);
      }

      fclose(fp);
      return 0;
  }
  ```

  `sample.txt` 내용:
  ```
  hello world
  abc def
  ```

   출력 예시:
  ```
  읽은 문자열: "hello wor"
  읽은 문자열: "ld\n"
  읽은 문자열: "abc def\n"
  ```


  | 항목 | 주의사항 |
  |------|----------|
  | 📌1  | `fgets()`는 **줄 전체를 못 읽을 수도 있음** → 반복적으로 호출해서 줄 전체를 처리해야 함 |
  | 📌2  | 문자열 끝에 `\n`이 있으면 포함됨 → 필요 시 수동으로 제거해야 함 |
  | 📌3  | `count <= 1`이면 대부분 **아무 것도 읽지 않고 종료** |
  | 📌4  | 반환값 `NULL`은 **에러 or EOF** → `feof()`와 `ferror()`로 구분 |


  `\n` 제거하는 코드

  ```c
  char *p = strchr(buf, '\n');
  if (p) *p = '\0';  // 줄바꿈 제거
  ```


  ```c
  int len = strlen(buf);
  if (buf[len - 1] == '\n') buf[len - 1] = '\0';
  ```

좋습니다. 이번엔 `fflush()` 함수에 대해 자세히 정리해드릴게요.

---

## 스트림 플러싱 `fflush()` 

```c
#include <stdio.h>

int fflush(FILE *stream);
```

- **출력 버퍼에 저장된 데이터를 강제로 비워(=flush)** 파일이나 화면 등 **출력 장치에 즉시 반영**하는 함수입니다.
- 주로 **`stdout`이 지연 출력되는 경우** 사용합니다. (예: 줄바꿈 없는 `printf()` 출력이 바로 보이지 않을 때)

| 상황                             | 예시 설명 |
|----------------------------------|-----------|
| `stdout`이 **버퍼링되어 출력 지연** | `printf("Enter name: "); fflush(stdout);` 없이 입력 대기하면, 프롬프트가 안 보일 수 있음 |
| 파일에 **지연된 쓰기 내용 반영** | `fputs()`나 `fprintf()` 후 `fflush(fp);` |
| `stream == NULL`일 때             | 열려 있는 **모든 출력 스트림을 flush** |

반환값
| 결과 | 의미 |
|------|------|
| `0` | 성공 |
| `EOF` | 실패 → `ferror(stream)`로 확인 가능 |


```c
#include <stdio.h>

int main(void) {
    printf("Enter your name: ");
    fflush(stdout); // 줄바꿈 없음 → 프롬프트가 안 나올 수 있음 → flush 필요

    char name[100];
    fgets(name, sizeof(name), stdin);

    printf("Hello, %s", name);
    return 0;
}
```

| 항목 | 설명 |
|------|------|
| ❌ 입력 스트림에 사용 시 | **정의되지 않은 동작** (C 표준에서) |
| POSIX 확장 | 입력 스트림도 **seekable한 경우** `fflush()`가 **버퍼 무효화 및 위치 동기화** 수행 |
| Visual Studio | 오래된 버전(`<=2013`)에서는 **입력 버퍼 삭제**<br>신버전(`>=2015`)에서는 **무시됨** |


입력 버퍼를 지우고 싶다면?

- `fflush(stdin)`은 **표준 C에서는 undefined behavior**
- 대신 다음과 같이 처리:

```c
int c;
while ((c = getchar()) != '\n' && c != EOF); // 표준 방식으로 버퍼 비우기
```

| 함수      | 대상     | 설명 |
|-----------|----------|------|
| `fflush()`| 파일/스트림 | 출력 버퍼를 비움 |
| `fsync()` | 파일 디스크립터 | 커널 버퍼까지 플러시 (데이터 안정성 보장) |
| `sync()`  | 전체 디스크 | 시스템 전체의 데이터를 디스크에 기록 요청 |

## 파일 위치 `ftell() fseek()`


  ### `ftell()` 
  ```c
  #include <stdio.h>
  long ftell(FILE *stream);
  ```
  - 현재 **파일 포인터의 위치**를 바이트 단위로 반환합니다.
  - 주로 **`fseek()` 전후 위치 추적**이나 **오프셋 확인**에 사용됩니다.
  | 반환값 | 의미 |
  |--------|------|
  | `>= 0` | 파일의 현재 위치 (바이트 단위 오프셋) |
  | `-1L`  | 실패 (`errno` 설정됨) |

  ```c
  FILE *fp = fopen("data.bin", "rb");
  fseek(fp, 0, SEEK_END);         // 파일 끝으로 이동
  long size = ftell(fp);          // 파일 크기 얻기
  fseek(fp, 0, SEEK_SET);         // 다시 파일 처음으로
  ```


  ### `fseek()` 
  ```c
  #include <stdio.h>
  int fseek(FILE *stream, long offset, int origin);
  ```
  - 파일 포인터를 **지정한 위치로 이동**시킵니다.

   `origin` 값

  | 상수 | 설명 |
  |------|------|
  | `SEEK_SET` | 파일 시작 위치로부터 offset 바이트 이동 |
  | `SEEK_CUR` | 현재 위치로부터 offset 바이트 이동 |
  | `SEEK_END` | 파일 끝으로부터 offset 바이트 이동 (POSIX는 허용, C 표준은 일부 제한) |

  | 반환값 | 의미 |
  |--------|------|
  | `0`    | 성공 |
  | 비0    | 실패 (`ferror()`로 확인) |

  ```c
  fseek(fp, sizeof(double) * 2, SEEK_SET);  // 세 번째 double 위치로 이동
  fread(&value, sizeof(double), 1, fp);
  ```


  ```c
  FILE* fp = fopen("log.txt", "rb");
  long start = ftell(fp);               // 위치 0
  fseek(fp, 100, SEEK_CUR);             // 100바이트 이동
  long current = ftell(fp);             // 위치 100
  fseek(fp, 0, SEEK_END);               // EOF 위치
  long size = ftell(fp);                // 파일 전체 크기
  ```


  🔸 텍스트 모드 vs 바이너리 모드
  - `ftell()`과 `fseek()`의 **정확한 바이트 오프셋**은 **바이너리 모드**에서만 보장됨.
  - **텍스트 모드**에선 내부적으로 줄바꿈 `\r\n` 변환 등이 적용되므로 **동작이 불명확**할 수 있음.

  🔸 `ftell()`의 결과는 `fseek(..., SEEK_SET)`에서만 유효
  - `ftell()`의 결과를 `SEEK_CUR` 또는 `SEEK_END`에 사용하는 건 잘못된 방법입니다.


  ### `remove()` `rename`
  ```c
  #include <stdio.h>
  int remove(const char *filename);
  ```
  - 지정한 파일을 **삭제**합니다.
  - 파일 이름은 문자열로 전달되며, 해당 파일이 삭제됩니다.

  | 반환값 | 의미 |
  |--------|------|
  | `0`    | 성공 |
  | `!= 0` | 실패 (`perror()`로 상세 원인 확인 가능) |

  - POSIX 시스템에서는 파일 이름과 디렉토리 엔트리만 제거되며, **해당 파일을 참조하는 모든 프로세스가 닫힌 뒤** 실제로 공간이 회수됩니다.
  - Windows는 **파일이 열려 있으면 삭제 불가**.

  ```c
  FILE *fp = fopen("temp.txt", "w");
  fclose(fp);
  remove("temp.txt");
  ```

  - 이미 삭제된 파일을 다시 삭제하려고 하면 **에러**가 납니다.
  - 존재하지 않는 파일을 삭제하면 `remove()`는 실패하고 `errno`가 `ENOENT`로 설정됩니다.


  ```c
  #include <stdio.h>
  int rename(const char *old_filename, const char *new_filename);
  ```
  - 파일 또는 디렉토리의 **이름을 변경**합니다.
  - 새 이름이 기존 파일 이름을 덮어쓸 수 있으며, OS에 따라 동작이 다를 수 있습니다.

  | 반환값 | 의미 |
  |--------|------|
  | `0`    | 성공 |
  | `!= 0` | 실패 (`perror()`로 원인 확인 가능) |

  ```c
  FILE *fp = fopen("old.txt", "w");
  fputc('A', fp);
  fclose(fp);

  rename("old.txt", "new.txt");
  ```

  - **POSIX 시스템**: `new_filename`이 존재하면 해당 파일을 **덮어씀**.
  - **Windows**: `new_filename`이 존재하면 실패함 (단, Windows 10 이상에서는 일부 예외 있음).

  ---

  📌 `remove()` vs `unlink()` (POSIX)
  - `remove()`는 **표준 C 함수**로 파일/디렉토리 둘 다 삭제 대상 (디렉토리 삭제는 POSIX 전용).
  - `unlink()`는 POSIX 전용 함수로 **파일만 삭제** 가능.
  - C 프로그램에서는 가급적 **`remove()`** 사용 권장.


  ### `unlink()` 

  ```c
  #include <unistd.h>
  int unlink(const char *pathname);
  ```

  - 지정된 **파일 이름을 파일 시스템에서 제거**합니다.
  - 즉, **파일의 디렉터리 엔트리(이름)** 를 삭제하는 것입니다.
  - **파일의 내용 자체는 아직 열려 있는 프로세스가 있다면 유지됨** → 나중에 모두 닫히면 삭제됨.

  **링크 수(link count)**
  - 유닉스/리눅스는 **하드 링크**를 통해 여러 이름이 하나의 파일을 가리킬 수 있습니다.
  - `unlink()`는 링크 수를 **1 감소**시키며, 링크 수가 0이 되면 파일 데이터가 제거됩니다.
  - 단, **해당 파일을 열고 있는 프로세스가 모두 닫혀야 실제 삭제**가 이루어집니다.


  | 반환값 | 의미 |
  |--------|------|
  | `0`    | 성공적으로 삭제 요청 |
  | `-1`   | 실패 (`errno`로 원인 확인) |

  | `errno` 값 | 의미 |
  |------------|------|
  | `ENOENT`   | 파일이 없음 |
  | `EACCES`   | 접근 권한 없음 |
  | `EPERM`    | 디렉토리의 경우, 삭제 권한 없음 |
  | `EISDIR`   | 디렉토리를 지우려 함 (→ `rmdir()` 써야 함) |


  ```c
  #include <stdio.h>
  #include <unistd.h>

  int main() {
      const char *filename = "example.txt";

      FILE *fp = fopen(filename, "w");
      if (fp == NULL) {
          perror("fopen");
          return 1;
      }
      fputs("Hello, world!\n", fp);
      fclose(fp);

      if (unlink(filename) == -1) {
          perror("unlink");
          return 1;
      }

      printf("파일 '%s' 삭제 성공\n", filename);
      return 0;
  }
  ```


`unlink()`의 실제 활용 예시

  - **임시 파일**을 열자마자 `unlink()` → 자동 삭제 보장 (열려 있는 동안만 존재)
  - **보안 강화**: 프로그램이 종료되면 흔적 없이 파일 자동 제거

  ```c
  int fd = open("temp", O_RDWR | O_CREAT, 0600);
  unlink("temp");  // 이름 제거 → 다른 프로세스 접근 차단
  // 이후 fd로만 접근 가능
  ```

  ### 형식이 있는 텍스트 스트림 읽기

  | 함수 | 설명 |
  |------|------|
  | `scanf`     | **표준 입력(stdin)**에서 데이터를 읽음 |
  | `fscanf`    | **파일 스트림(FILE*)**에서 데이터를 읽음 |
  | `sscanf`    | **문자열 버퍼**에서 데이터를 읽음 |
  | `scanf_s`   | `scanf`의 **보안 강화 버전 (C11)** |
  | `fscanf_s`  | `fscanf`의 **보안 강화 버전 (C11)** |
  | `sscanf_s`  | `sscanf`의 **보안 강화 버전 (C11)** |

  ```c
  int scanf(const char *format, ...);           // 표준 입력에서 읽음
  int fscanf(FILE *stream, const char *format, ...);  // 파일에서 읽음
  int sscanf(const char *buffer, const char *format, ...); // 문자열에서 읽음
  ```
  - `format` 문자열에 따라 데이터를 추출
  - `%d`, `%f`, `%s`, `%c`, `%x`, `%u`, `%p`, `%[...]` 등 다양한 **포맷 지정자** 사용 가능
  - 반환값: **성공적으로 저장된 항목의 개수** 또는 EOF

  ```c
  #define __STDC_WANT_LIB_EXT1__ 1
  #include <stdio.h>
  int scanf_s(const char *format, ...);
  ```
  - `%s`, `%c`, `%[` 사용 시에는 반드시 **버퍼 크기**도 같이 전달해야 함
  - **버퍼 오버플로우 방지** 목적으로 추가된 보안 함수
  - 사용 시 `__STDC_WANT_LIB_EXT1__`를 정의해야 사용 가능

  ```c
  char buf[20];
  scanf_s("%19s", buf, sizeof(buf));  // %s는 크기 전달 필수
  ```


  | 포맷 | 설명 | 저장되는 변수형 |
  |------|------|-----------------|
  | `%d` | 부호 있는 10진수 정수 | `int *` |
  | `%u` | 부호 없는 10진수 | `unsigned int *` |
  | `%x`, `%X` | 16진수 | `unsigned int *` |
  | `%`, `%lf` | 실수 | `float *`, `double *` |
  | `%c` | 문자 | `char *` (또는 배열) |
  | `%s` | 문자열 (공백 전까지) | `char *` |
  | `%[...]` | 지정한 문자 집합만 허용 | `char *` |
  | `%n` | 지금까지 읽은 문자 수 저장 | `int *` |
  | `*` | 값은 읽지만 저장하지 않음 | 없음 |

  1. `%s`, `%c`, `%[`는 **공백을 구분자로 하지 않음** → 버퍼 오버플로우 주의
  2. `%c`는 입력 버퍼에 남은 **`\n`도 읽어버림** → 앞에 `" %c"`로 공백 넣어주기
  3. `scanf_s` 시에는 반드시 **배열 크기** 전달할 것
  4. `scanf()`는 에러에 취약함 → 입력 검증 필수


  ```c
  #include <stdio.h>

  int main() {
      int a;
      float b;
      char name[20];

      printf("정수, 실수, 이름 입력: ");
      scanf("%d %f %19s", &a, &b, name);

      printf("입력된 값: a=%d, b=%.2f, name=%s\n", a, b, name);
      return 0;
  }
  ```

## 이진 스트림에서 읽기 및 쓰기

  ### `fread()`
  이진 스트림에서의 **읽기 및 쓰기**는 텍스트 스트림과 달리 **데이터를 가공 없이 그대로 저장하거나 읽어들일 때** 사용합니다. 

  ```c
  size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
  ```
  | 인자 | 설명 |
  |------|------|
  | `buffer` | 읽은 데이터를 저장할 버퍼 주소 |
  | `size` | 읽을 "요소의 크기 (바이트 단위)" |
  | `count` | 읽을 요소의 "개수" |
  | `stream` | 읽을 대상 파일 스트림 포인터 (`fopen()`으로 연 파일) |

  즉, 총 `size * count` 바이트를 읽으려고 시도합니다.

  반환값
  - 성공적으로 읽은 요소 수 (요소 = size만큼의 블록)
  - `0`이면 읽지 못함 → `feof()`(EOF 여부), `ferror()`(오류 여부)로 원인 판단


  - **텍스트 모드("w", "r")가 아닌 이진 모드("wb", "rb")**로 열어야 데이터가 손상되지 않습니다.
  - `fread()`와 `fwrite()`는 구조체나 배열 같은 **바이너리 데이터를 저장할 때 유용**합니다.
  - 포맷 없이 쓰기 때문에 **다른 시스템(리틀/빅 엔디안)에서 호환성 문제가 생길 수 있음**.



  ### `fwrite()`
  `fwrite()` 함수는 **이진 파일(Binary File)**에 데이터를 **버퍼에서 파일로 저장**할 때 사용되는 표준 C 함수입니다. 
  ```c
  #include <stdio.h>
  size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
  ```
  | 인자     | 설명 |
  |----------|------|
  | `buffer` | 파일로 쓸 데이터가 있는 메모리 주소 |
  | `size`   | 한 개 요소의 크기 (바이트 단위) |
  | `count`  | 쓰려는 요소의 개수 |
  | `stream` | 대상 파일 스트림 포인터 (`fopen()`으로 연 파일) |

  즉, 총 `size * count` 바이트를 씁니다.
  
  반환값
  - 실제로 **성공적으로 기록한 요소의 개수** 반환
  - 반환값 < `count` 면 **쓰기 오류 또는 디스크 문제 발생 가능성** 있음 → `ferror()`로 원인 확인


  ```c
  #include <stdio.h>
  #include <stdlib.h>

  #define SIZE 5

  int main(void) {
      double a[SIZE] = {1.1, 2.2, 3.3, 4.4, 5.5};

      // 쓰기 모드로 파일 열기
      FILE *fp = fopen("data.bin", "wb");
      if (!fp) {
          perror("fopen");
          return 1;
      }

      size_t written = fwrite(a, sizeof(double), SIZE, fp);
      printf("wrote %zu elements\n", written);
      fclose(fp);

      // 읽기 모드로 다시 열기
      double b[SIZE] = {0};
      fp = fopen("data.bin", "rb");
      if (!fp) {
          perror("fopen");
          return 1;
      }

      size_t read = fread(b, sizeof(double), SIZE, fp);
      printf("read %zu elements:\n", read);
      for (size_t i = 0; i < read; ++i)
          printf("b[%zu] = %.1f\n", i, b[i]);
      
      fclose(fp);
      return 0;
  }
  ```


  `fwrite()`와 `fread()`는 언제 쓰나?

  - 구조체, 배열 등 **복잡한 데이터를 그대로 파일에 저장할 때**
  - 텍스트가 아닌 **이진 데이터로 파일을 다룰 때**
  - **CSV, JSON, XML** 등 텍스트 형식보다 빠른 저장/복원을 원할 때


  주의사항
  - 반드시 `wb`, `rb` 모드로 열어야 합니다. (`w`, `r`는 텍스트 모드)
  - 파일 간 이식성을 위해 데이터 정렬, 엔디안(endian) 문제 주의 필요
  - `fwrite()` 후에는 **반드시 `fclose()` 또는 `fflush()` 호출**해 디스크에 반영

  