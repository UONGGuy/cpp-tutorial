# Invalid inputs

## Introduction

Two key components to inputs are `std::cin` and the `>>` extraction operator.

`std::cin` gets user input from an external source and holds the data inside a buffer (temporary memory storage for data) where it remains to be extracted.

`>>` extracts the user input and puts it into a variable.

When `>>` is used:
- If there is data already in the buffer, it is used for extraction.
- If there is no data in the buffer, the user is asked to input data for extraction with a '\n' character placed in the input buffer when the user hits ENTER.
- `>>` extracts as much data from the buffer as it can into the varaible, ignoring leading whitespace characters (spaces, tabs, '\n').
- Unextracted data is left in the input buffer for the next extraction.

Extraction fails if the input data type doesn't match the type of the variable it is extracted to.

## Types of invalid text input

There are 4 general types of input text error:
- Input extraction succeeds but input is meaningless.
- Input extraction succeeds but additional unwanted input remains in the buffer.
- Input extraction fails due to type mismatch.
- Input extraction succeeds but the user overflows a numeric value.

To make robust programs, we should try to consider and handle conceivable cases of program misuse.

For ease of understanding, consider a calculator program where you are asked to input an integer, then an arithmetic operation, then another integer.
The output is the first integer operated on by the second integer.

## Extraction succeeds but input is meaningless

Imagine here that instead of entering one of (+, -, \*, /), a different character is entered instead (e.g. 'k').

The extraction of the operation is valid but does not lead to any action as it is not an expected input.

The solution is to check if the user input was within expectations and either continue if so, or tell the user and have them try again if not.

This can be done with a `while` loop, `switch` and a `default` option to retry.

## Extraction succeeds but with additional unwanted input

Imagine that the user has input `5*7` rather than taking each input step-by-step as intended.

Every time the `>>` operator is called, it sees that there is already data in the buffer and extracts from there immediately without waiting for another user input as expected.

The answer is correct but formatting is messy.

The solution is to ignore following, unwanted characters in the buffer by using `std::cin.ignore(x, '\n')` where `x` is the number of characters to remove after the initial extraction.
To ignore all characters up to the next '\n', `std::numeric_limits<std::streamsize>::max()` can be passed as `x`.
Because of the length of this line of code, it is usually handy to wrap it up in a `void` type function.

## Extraction fails

Imagine that you enter `char` 'a' instead of an integer initially.

The program tries to extract a `char` to an `int` but due to the typing mismatch, `std::cin` goes into "failure mode".
This means all future input extraction requests silently fails (i.e. the program will still output printed prompts but ignores any further extractions).
This prevents and valid cases from being reached and the user remains stuck in an infinite loop.

The solution is to use `std::cin.fail()` (a boolean) to detect whether extraction has failed then revert the buffer to normal mode using `std::cin.clear()` and remove the bad input with `std::cin.ignore()` (see previous section).

Failed extractions cause varaibles to be zero-initialised.

## Extraction succeeds but the user overflows a numeric value

If the input is a numeric value outside the range the variable can contain then `std::cin` goes into "failure mode" and assigns to closest in-range value to the variable.
Additional inputs are skipped and so zero-initialised.

These errors can be handled in the same way as failed extractions.
