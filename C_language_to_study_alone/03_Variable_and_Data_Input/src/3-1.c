/**
 * @file 3-1.c
 * @brief Declaration and use of variables
 *
 * This program demonstrates how to declare and use variables of various data types in C. It also highlights basic arithmetic operations and assignment.
 *
 * @author Kim Hyo Jin
 * @date 2024-12-21
 */

#include <stdio.h>

/**
 * @brief Main function
 *
 * The entry point of the program. It declares variables of different types, assigns values, performs operations, and prints the results.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @return int Returns 0 to indicate successful program termination
 */
int main(int argc, char **argv)
{
    int a, b, c;
    double da;
    char ch;

    a = 10;       /**< Assigning 10 to variable `a` (l-value = r-value). */
    b = a;        /**< Assigning the value of `a` to `b`. */
    c = a + 20;   /**< Performing addition and assigning the result to `c`. */
    da = 3.5;     /**< Assigning a double literal to `da`. */
    ch = 'A';     /**< Assigning a character literal to `ch`. */

    printf("Value of variable a: %d\r\n", a);
    printf("Value of variable b: %d\r\n", b);
    printf("Value of variable c: %d\r\n", c);
    printf("Value of variable da: %.1lf\r\n", da);
    printf("Value of variable ch: %c\r\n", ch);

    return 0; /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./3-1
 * ```
 *
 * @output
 * ```
 * Value of variable a: 10
 * Value of variable b: 10
 * Value of variable c: 30
 * Value of variable da: 3.5
 * Value of variable ch: A
 * ```
 *
 * @details
 * - **L-value**:
 *   - An **l-value** (locator value) represents a memory location that can hold a value.
 *   - It appears on the left-hand side of an assignment statement.
 *   - In the program, variables like `a`, `b`, `c`, `da`, and `ch` are examples of l-values because they refer to identifiable memory locations.
 *
 * - **R-value**:
 *   - An **r-value** (read value) is the actual value assigned to an l-value.
 *   - It appears on the right-hand side of an assignment statement.
 *   - In the program, literals like `10`, `3.5`, `'A'`, and the expression `a + 20` are examples of r-values because they represent values to be stored in memory.
 *
 * - **Examples in the program**:
 *   - `a = 10;` -> `a` is the l-value, and `10` is the r-value.
 *   - `b = a;` -> `b` is the l-value, and the value of `a` (an r-value) is assigned to it.
 *   - `c = a + 20;` -> `c` is the l-value, and `a + 20` is the r-value resulting from an arithmetic operation.
 */

