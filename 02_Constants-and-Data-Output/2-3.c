/**
 * @file 03.c
 * @brief A program demonstrating escape sequences in C.
 *
 * This program showcases the use of various escape sequences such as
 * `\n`, `\t`, `\b`, `\r`, and `\a` to manipulate output formatting and behavior.
 *
 * @author 김효진
 * @date 2024-11-19
 */

#include <stdio.h> /**< Standard I/O library for printf function. */

/**
 * @brief Main function
 *
 * The entry point of the program. It demonstrates the use of escape sequences
 * for formatted output.
 *
 * @return int Returns 0 to indicate successful program termination.
 */
int main(void)
{
    printf("Be happy\n");               /**< Prints "Be happy" and moves to a new line. */
    printf("12345678901234567890\n");   /**< Prints column numbers and moves to a new line. */
    printf("My\tfriend\n");             /**< Prints "My", moves to a tab position, and prints "friend". */
    printf("Goot\bd\tchance\n");        /**< Backspaces the last character of "Goot" and replaces it with 'd', moves to a tab position, and prints "chance". */
    printf("Cow\rW\a\n");               /**< Replaces 'C' with 'W' using `\r`, produces a bell sound with `\a`, and moves to a new line. */
    return 0;                           /**< Indicates successful program termination. */
}

/**
 * @example
 * ### Execution Example:
 * ```bash
 * $ ./03
 * Be happy
 * 12345678901234567890
 * My    friend
 * Good  chance
 * Wow
 * ```
 *
 * @output
 * ```
 * Be happy
 * 12345678901234567890
 * My    friend
 * Good  chance
 * Wow
 * ```
 *
 * @details
 * - `\n`: Moves to the next line.
 * - `\t`: Moves to the next tab stop.
 * - `\b`: Moves the cursor back one space and overwrites the previous character.
 * - `\r`: Moves the cursor to the beginning of the current line.
 * - `\a`: Produces a bell sound (audible if the terminal supports it).
 */

