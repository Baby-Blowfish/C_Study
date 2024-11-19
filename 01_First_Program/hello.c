/**
 * @file hello_world.c
 * @brief A simple program to demonstrate basic C standard I/O functions.
 *
 * This program prints "Hello World" to the standard output (stdout)
 * using `printf` and returns `EXIT_SUCCESS` to indicate successful execution.
 *
 * @return EXIT_SUCCESS Returns 0 if the program executes successfully.
 */

// preprocessor directive
#include <stdio.h>      /**< Standard I/O header file for printf() */
#include <stdlib.h>     /**< Standard library header for EXIT_SUCCESS */

int main(void) // int형 반환, 인수 없음
{
    /**
     * @brief Entry point of the program
     *
     * Prints "Hello World" to stdout using printf.
     */

    printf("%s\n", "Hello World");
    /**<
     * Prints the string "Hello World" followed by a newline character
     * to the standard output. `%s` is the format specifier for strings.
     */

    return EXIT_SUCCESS;
    /**< Indicates successful execution of the program. Typically defined as 0. */
}

/**
 * @example
 * ### Example Execution:
 * ```bash
 * $ ./hello_world
 * Hello World
 * ```
 *
 * @output
 * ```
 * Hello World
 * ```
 *
 * @details
 * - The program successfully writes "Hello World" to the console.
 * - The `EXIT_SUCCESS` macro (commonly 0) is returned to the host environment.
 */

