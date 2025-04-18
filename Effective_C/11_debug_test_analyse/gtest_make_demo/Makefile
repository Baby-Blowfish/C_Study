# ========================
# 컴파일러 설정
# ========================
CXX = g++
CC  = gcc

# ========================
# 경로 설정
# ========================
INCLUDES = \
  -Iinclude \
  -Ithird_party/googletest/include \
  -Ithird_party/googletest

CFLAGS   = -Wall $(INCLUDES)
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror $(INCLUDES)

# ========================
# 파일 및 디렉토리
# ========================
SRC       = src/motor.c
TEST      = test/test_motor.cpp
GTEST_SRC = third_party/googletest/src/gtest-all.cc

OBJDIR  = obj
BINDIR  = bin

OBJS    = $(OBJDIR)/motor.o
TARGET  = $(BINDIR)/test_motor

# ========================
# 기본 빌드 타겟
# ========================
.PHONY: all clean run test

all: $(TARGET)

# ========================
# 오브젝트 파일 빌드
# ========================
$(OBJDIR)/motor.o: $(SRC) include/motor.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ========================
# 실행 파일 빌드
# ========================
$(TARGET): $(OBJS) $(TEST) $(GTEST_SRC)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -pthread -o $@

# ========================
# 실행 타겟
# ========================
run: all
	./$(TARGET)

# ========================
# 테스트 타겟
# ========================
test: all
	valgrind --leak-check=full ./$(TARGET)

# ========================
# 클린 타겟
# ========================
clean:
	rm -rf $(OBJDIR) $(BINDIR)
