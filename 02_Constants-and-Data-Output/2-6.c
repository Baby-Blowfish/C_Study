/**
 * @file 2-6.c
 * @brief A program to demonstrate the use of floating-point numbers in both
 * decimal and exponential (scientific) notation in C.
 *
 * This program shows how to format and print floating-point numbers using
 * both fixed-point and exponential notation with varying precision.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It demonstrates the use of floating-point
 * formatting with both decimal (`%lf`) and exponential (`%le`) notations.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("%.1lf\n", 1e6);         /**< Prints 1e6 (1,000,000) in fixed-point notation with 1 decimal place. */
    printf("%.7lf\n", 3.14e-5);     /**< Prints 3.14e-5 (0.0000314) in fixed-point notation with 7 decimal places. */
    printf("%le\n", 0.0000314);     /**< Prints 0.0000314 in exponential notation with default precision. */
    printf("%.2le\n", 0.0000314);   /**< Prints 0.0000314 in exponential notation with 2 decimal places. */
    return 0;                       /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./2-6
 * 1000000.0
 * 0.0000314
 * 3.140000e-05
 * 3.14e-05
 * ```
 *
 * @output
 * ```
 * 1000000.0
 * 0.0000314
 * 3.140000e-05
 * 3.14e-05
 * ```
 *
 * @details
 * - `1e6`: Exponential notation representing 1,000,000. Printed in fixed-point notation as `1000000.0`.
 * - `3.14e-5`: Exponential notation for 0.0000314. Printed in fixed-point notation with 7 decimal places.
 * - `%le`: Formats a floating-point number in exponential notation. Default precision is 6 decimal places.
 * - `%.2le`: Formats a floating-point number in exponential notation with 2 decimal places.
 */

