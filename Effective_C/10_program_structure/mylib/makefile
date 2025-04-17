CC = gcc
CFLAGS = -Wall -Wextra -fPIC

all: static shared

static:
	$(CC) -c mymath.c -o mymath_static.o
	ar rcs libmymath.a mymath_static.o
	$(CC) main.c -L. -lmymath -o main_static

shared:
	$(CC) -c mymath.c -o mymath_shared.o $(CFLAGS)
	$(CC) -shared -o libmymath.so mymath_shared.o
	$(CC) main.c -L. -lmymath -o main_shared -Wl,-rpath=.  # rpath for ./libmymath.so

clean:
	rm -f *.o *.a *.so main_static main_shared
`