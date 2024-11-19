/**
 * @file 2-5.c
 * @brief A program to demonstrate different integer constant formats in C.
 *
 * This program shows how to represent and print decimal, octal, and hexadecimal
 * integer constants using `printf`.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It demonstrates the use of decimal, octal,
 * and hexadecimal integer constants and prints their values in decimal format.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("%d\n", 12);   /**< Prints the decimal constant 12. */
    printf("%d\n", 014);  /**< Prints the octal constant 014 (equivalent to 12 in decimal). */
    printf("%d\n", 0xc);  /**< Prints the hexadecimal constant 0xc (equivalent to 12 in decimal). */
    return 0;             /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./2-5
 * 12
 * 12
 * 12
 * ```
 *
 * @output
 * ```
 * 12
 * 12
 * 12
 * ```
 *
 * @details
 * - `12`: A decimal integer constant, directly interpreted as 12.
 * - `014`: An octal integer constant, where the leading `0` indicates octal representation. `014` in octal equals `12` in decimal.
 * - `0xc`: A hexadecimal integer constant, where the prefix `0x` indicates hexadecimal representation. `0xc` in hexadecimal equals `12` in decimal.
 */

