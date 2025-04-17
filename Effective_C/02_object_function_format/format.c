/*
===========================================
Boolean type
===========================================

#include <stdbool.h>

_Bool flag1 = 0;
bool flag2 = false;   // 이걸 사용

bool 타입 : 참/거짓 값을 표현하는 타입, 0 또는 1 값을 가짐


===========================================
character type
===========================================

char
signed char
unsigned char

char 타입 : 문자 데이터 표현, 대문자, 소문자, 10개 십진수 숫자, 공백문자, 구두점과 제어문자 등, 1바이트 크기, 기본 실행 문자 집합
정수 데이터에 적합하지 않다.
wchar_t 타입 : 멀티바이트 문자 표현, 유니코드 문자 표현, 1바이트 크기, 기본 실행 문자 집합

signed char 타입 : 부호 있는 작은 정수

unsigned char 타입 : 부호 없는 작은 정수







===========================================
numeriacal type
===========================================

#include <limits.h> // 정수 형식의 최소값과 최대값을 정의하는 헤더 파일

1. 정수 형식(signed integer type)
  1.1 부호 있는 정수 형식
  signed char
  signed short int
  signed int
  signed long int
  signed long long int

  1.2 부호 없는 정수 형식
  unsigned char
  unsigned short int
  unsigned int
  unsigned long int
  unsigned long long int


2. 열거형(enumerated type)
  의미 있는 이름들에 숫자 값을 부여해주는 사용자 정의 자료형
  signed int, gcc의 경우 unsigned int를 사용
  기본적으로 0부터 1씩 증가, 명시적으로 값 지정 가능

  2.1 열거형 타입
  enum color {RED, GREEN, BLUE};
  enum color {RED = 1, GREEN = 2, BLUE = 3};
  enum color {RED, GREEN, BLUE = 3}; // RED = 0, GREEN = 1, BLUE = 3
  enum color {RED = 100, GREEN = 200, BLUE = 300};

  2.2 열거형 변수
  enum color myColor;
  myColor = RED;

  printf("%d\n", myColor); // 0
  printf("%d\n", GREEN); // 1

  
  ex)
  enum Mode { IDLE, RUNNING, ERROR };

  void check(enum Mode m) {
      switch (m) {
          case IDLE:
              printf("대기 중\n");
              break;
          case RUNNING:
              printf("실행 중\n");
              break;
          case ERROR:
              printf("오류 발생\n");
              break;
      }
  }

  ex)
  const char* mode_to_str(enum Mode m) {
    switch (m) {
        case IDLE: return "IDLE";
        case RUNNING: return "RUNNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
  }






===========================================
floating point type
===========================================

float
double
long double

float 타입 : 32비트 부동 소수점 형식, 소수점 이하 7자리 정도의 정확도
double 타입 : 64비트 부동 소수점 형식, 소수점 이하 15자리 정도의 정확도
long double 타입 : 80비트 부동 소수점 형식, 소수점 이하 19자리 정도의 정확도





===========================================
void type
===========================================

void 타입 : 함수의 반환 값이나 인수가 없는 경우 사용
void 타입의 변수는 선언할 수 없음

void * : 포인터 타입, 모든 타입의 포인터를 저장할 수 있음







===========================================
function type
===========================================
반환 형식
매개변수의 개수
매개변수의 형식

int f(void);
int *fip();

void g(int i, int j); // 이걸 사용
void h(int, int);





===========================================
derived type
===========================================
포인터, 배열, 형식 정의 , 구조체, 공용체



===========================================
pointer type
===========================================

int *ip;
char *cp;
void *vp;

int i = 17;
int *ip = &i;

ip = &*ip;


===========================================
array type
===========================================

1. 배열(array)
  1.1 배열 선언
  int a[10];
  





===========================================
type define
===========================================

형식정의 : 기존 형식에 대한 별칭(alias) 선언

typedef unsigned int uint_type;
typedef unsigned char uchar_type, *uchar_ptr, (*fp)(void);






===========================================
structure type
===========================================

구조체 : 여러 데이터 형식을 하나의 단위로 묶어서 정의한 사용자 정의 자료형

struct sigrecord {
  int signum;
  char signame[20];
  char sigdesc[100];
} sigline, *sigline_ptr;

sigline.signum = 5;
strcpy(sigline.signame, "SIGINT");
strcpy(sigline.sigdesc, "Interrupt");

sigline_ptr = &sigline;

sigline_ptr->signum = 5;
strcpy(sigline_ptr->signame, "SIGINT");
strcpy(sigline_ptr->sigdesc, "Interrupt");






===========================================
union type
===========================================

공용체 : 여러 데이터 형식을 하나의 단위로 묶어서 정의한 사용자 정의 자료형

union {
  strcut{
    int type;
  } n;

  struct{
    int type;
    int intnode;
  } ni;

  struct{
    int type;
    double doublenode;
  } nf;

}u;

u.n.type = 1;
u.ni.intnode = 10;
u.nf.doublenode = 10.1;






===========================================
tag 
===========================================

tag : 구조체, 공용체, 열거형 등의 사용자 정의 자료형에 붙이는 이름

struct s{

}
s : tag

태그 : 형식의 이름 아니고 변수를 선언하는데 사용할 수 없다.
struct s v;
sturct s *p;
day today;    // 오류
enum day tomorrow;

태그는 네임스페이스에 정의됨, 같은 범위안에서 같은 철자를 가진 태그와 다른 식별자를 가진 변수를 선언할 수 있다.
enum status { ok, fail};
enum status status(void);

struct s s;


typedef struct tag { //~~; } identifier;
typedef struct s { int x;} t;

t.x = 10;

// 자기 참조 구조체가 아닌 경우 태그 생략 가능
typedef struct { int x;} t;


// 자기 참조 구조체 : 태그 생략 경고
struct tnode{
  int count;
  struct tnode *left;
  struct tnode *right;
};

// 가능
typedef struct tnode{
  int count;
  struct tnode *left;
  struct tnode *right;
} tnode;

typedef struct tnode;
struct tnode
{
  int count;
  struct tnode *left;
  struct tnode *right;
}tnode;

tpyedef void fv(int), (*pfv)(int);
void (*signal(int, void (*)(int)))(int);
fv *signal(int, fv *);
pfv signal(int, pfv);



===========================================
type qualifier
===========================================

const
volatile
restrict



1. const
  할당도리 수는 없지만, 상수 이니셜라이저로 초기화 가능
  읽기 저뇽 메모리에 위치, 쓰기 시도하면 런타임 오류 발생

  const int i = 1;
  i = 2; // 런타임 오류

  const int *p = (int*)&i;
  *p = 2; // 정의되지 않은 동작, 오류 발생 확률 있음

  int * const p = &i;
  *p = 2; // 가능
  
  int i = 12;                // 일반 변수: i는 수정 가능한 메모리에 할당됨
  const int j = 12;          // 상수 변수: j는 수정할 수 없도록 정의됨
  const int *ip = &i;        // ip는 const int*지만, 실제로는 i(수정 가능)를 가리킴
  const int *jp = &j;        // jp는 const int*로, j(상수)를 가리킴

  *(int *)ip = 10;           // (1) ip를 int*로 캐스트 후 값을 변경 → OK
  *(int *)jp = 10;           // (2) jp를 int*로 캐스트 후 값을 변경 → 런타임 오류 발생, 정의되지 않은 동작

  
2. volatile
  컴파일러가 최적화를 위해 변수를 변경하지 않도록 방지
  컴파일러가 최적화를 위해서 레지스터에 캐시해서 읽어옴, 레지스터에서 읽지말고 매번 메모리에서 읽어라는 용도 
  하드웨어 레지스터 : memory-mapped I/O
  무한 루프 상태 감시 : 외부 인터럽트나 스레드가 값을 바꿀 수 있는 변수
  멀티스레드 공유 변수 : 메인 스레드가 검사하고, 다른 스레드가 변경하는 플래그
    volatile은 값이 변경됨은 감지하지만 원자성을 보장 하지 않는다.
    즉 여러개의 쓰래드가 volatile 변수에 접근하고 수정할때 race condition 이 발생할 수 있다 -> 원자성 x
    따라서 atomic_* 을 사용하거나 mutex로 동기화를 해야한다.

  ex)
  int flag = 0;
  while(flag == 0){
    // 무한 루프
  }
  컴파일러가 flag는 바뀌지 않는다고 판단하고 while(1) 로 최적할 수도 있음

  // 컴파일러가 최적화를 위해 변수를 변경하지 않도록 방지
  volatile int flag = 0;
  while(flag == 0){
    // 무한 루프
  }
  컴파일러는 매번 flag의 실제 메모리 주소를 읽음
  다른 스레드나 인터럽트가 flag를 바꿔도 변경을 감지 할수 있음  


3. restrict
  포인터를 통해 간접적으로 접근되는 개체는 같은 개채를 참조할떄 발생하는 문제 방지하기 위해 최적화 될 수 없다.
  이러한 앨리어싱은 최적화를 방해한다.
  이 포인터가 가리키는 메모리는 이 포인터를 통해서만 접근된다라고 컴파일러에게 약속함
  void foo(int * restrict p, int * restrict q);
  a와 b는 겹치지 않는 메모리 영역을 가리킨다를 컴파일러에 보장함.
  컴파일러는 자유롭게 최적화 가능하다. a의 변경이 b에 영향을 주지 않으므로

  벡터 연산, 이미지 처리, 배열 복사

  ex)
  void copy(int *restrict dst, const int *restrict src, int size) {
    for (int i = 0; i < size; i++) {
        dst[i] = src[i];
    }
  }
  컴파일러는 루프안에서 dst와 src가 영상을 안미친다고 확신하여 unrolling, SIMD최적화 가능
  만약 restrict가 없다면 매번 src를 메모리에서 다시 읽어야 한다고 추정 -> 최적화 불가능
  만약 중첩된다면 정의되지 않는 동작 발생

  ex) 벡터 더하기
  void add(float *restrict a, float *restrict b, float *restrict out, int size) {
      for (int i = 0; i < size; i++) {
          out[i] = a[i] + b[i];
      }
  }
  

*/