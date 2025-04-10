/**
 * @file 2-2.c
 * @brief A program to demonstrate basic output using `printf`.
 *
 * This program prints two strings, "Be happy" and "My friend", to the
 * standard output using the `printf` function.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It outputs two strings to the console.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("Be happy\n");    /**< Prints "Be happy" followed by a newline. */
    printf("My friend\n");   /**< Prints "My friend" followed by a newline. */
    return 0;                /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./2-2
 * Be happy
 * My friend
 * ```
 *
 * @output
 * ```
 * Be happy
 * My friend
 * ```
 *
 * @details
 * - The program demonstrates the use of the `printf` function to print
 *   multiple lines of text.
 * - Each `printf` call outputs a string followed by a newline character (`\n`).
 */

