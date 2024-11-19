/**
 * @file 2-4.c
 * @brief A program to demonstrate formatted output in C using printf.
 *
 * This program shows how to use format specifiers such as `%d`, `%lf`,
 * and precision specifiers for floating-point numbers. It includes examples
 * of integer and floating-point arithmetic formatted outputs.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It demonstrates formatted output for integers
 * and floating-point numbers, as well as arithmetic calculations within `printf`.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("%d\n", 10);           /**< Prints the integer 10 followed by a newline. */
    printf("%lf\n", 3.4);         /**< Prints the double 3.4 to 6 decimal places followed by a newline. */
    printf("%.1lf\n", 3.45);      /**< Prints 3.45 rounded to one decimal place (3.5) followed by a newline. */
    printf("%.10lf\n", 3.4);      /**< Prints 3.4 to 10 decimal places followed by a newline. */

    printf("%d과 %d의 합은 %d입니다.\n", 10, 20, 10 + 20); /**< Prints the sum of 10 and 20 in a formatted sentence. */
    printf("%.1lf - %.1lf = %.1lf\n", 3.4, 1.2, 3.4 - 1.2); /**< Prints the result of 3.4 - 1.2 rounded to one decimal place. */

    return 0; /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./2-4
 * 10
 * 3.400000
 * 3.5
 * 3.4000000000
 * 10과 20의 합은 30입니다.
 * 3.4 - 1.2 = 2.2
 * ```
 *
 * @output
 * ```
 * 10
 * 3.400000
 * 3.5
 * 3.4000000000
 * 10과 20의 합은 30입니다.
 * 3.4 - 1.2 = 2.2
 * ```
 *
 * @details
 * - `%d`: Prints an integer.
 * - `%lf`: Prints a double to 6 decimal places by default.
 * - `%.1lf`: Prints a double rounded to one decimal place.
 * - `%.10lf`: Prints a double to 10 decimal places.
 * - Multiple arguments in `printf`: Used to format arithmetic calculations in a sentence.
 */

