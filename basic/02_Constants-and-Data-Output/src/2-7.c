/**
 * @file 2-7.c
 * @brief A program to demonstrate the use of character and string constants in C.
 *
 * This program shows how to print character constants (`%c`) and string constants
 * (`%s`) using the `printf` function, and how to combine them in a formatted string.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It demonstrates the use of character and
 * string constants in formatted output using `printf`.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("%c\n", 'A');                        /**< Prints the character constant 'A'. */
    printf("%s\n", "A");                        /**< Prints the string constant "A". */
    printf("%c은 %s입니다.\n", '1', "first");   /**< Prints '1' as a character and "first" as a string in a sentence. */
    return 0;                                   /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./2-7
 * A
 * A
 * 1은 first입니다.
 * ```
 *
 * @output
 * ```
 * A
 * A
 * 1은 first입니다.
 * ```
 *
 * @details
 * - `%c`: Formats a single character constant for output.
 * - `%s`: Formats a string constant for output.
 * - Combination: `%c` and `%s` can be used together to create formatted sentences.
 */

