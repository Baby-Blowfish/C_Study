#ifndef LOG_MACRO_H
#define LOG_MACRO_H

#include <stdio.h>
#include <time.h>

/* 현재 시간 문자열 반환 */
static inline const char* log_get_time_str() {
    static char buffer[20];
    time_t t = time(NULL);
    struct tm* lt = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", lt);
    return buffer;
}

/* 기본 로그 출력 매크로 */
#define LOG_BASE(level, msg, ...) \
    fprintf(stderr, "[%s] [%s] %s:%d in %s() - " msg "\n", \
        log_get_time_str(), level, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

/* 로그 레벨 별 매크로 정의 */
#define LOG_INFO(msg, ...)  LOG_BASE("INFO", msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...)  LOG_BASE("WARN", msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) LOG_BASE("ERROR", msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) LOG_BASE("DEBUG", msg, ##__VA_ARGS__)

#endif // LOG_MACRO_H
