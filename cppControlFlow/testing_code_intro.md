# Introduction to testing code

It is important to test code to ensure it works as desired.

How you test code is important as what is tested as it can make the process significantly more efficient.

## Unit testing

Best practice is to test programs in small, well-defined units. 
This allows you to check new components work as you write them to make it easier to identify and fix issues before integrating into the overall program.

## Preserving tests

It can be useful to preserve tests (say in a function) in the event modifications that needed to be reverified occur.

That way it is quick and easy to test they work as intended and they are all kept in one place.

## Automating test functions

When writing test functions, it can be useful to write functions that contain both the tests AND expected answers.

By having these, comparisons can be made and problematic areas can be identified and fixed more easily.

## Unit testing frameworks

There exist third party softwares that are deisgned to help simplify the writing, maintenance and execution of unit tests.

## Integration testing

After testing units in isolation, they can be integrated into the program and retested to ensure integration is as intended.

# Code coverage

Describes how mch of the source code of a program is executed while testing.

## Statement coverage

Percentage of statements in code exercised by testing routines.

e.g. using an early `return` may mean statements after may not be tested.

Althought 100% statement coverage is good, it isn't enough to ensure robustness.

## Branch coverage

Percentage of branches exercised by testing routines.

e.g. `if` statements have two branches: `true` and `false`. Only testing one branch gives 50% branch coverage.

Aim for 100% branch coverage when testing code.

## Loop coverage

Checking each iteration of the loop executes correctly.

The '0, 1, 2 test' gives confidence further loops will execute correctly for iterations greater than 2.

## Different input categories

It can be important to check how your functions handle all types of inputs.

Basic guidelines for testing:
- Integers: -ve values, 0, +ve values, overflow (if relevant)
- Floating point: values with precision issues (+- 0.1 for numbers slightly larger than expected; +-0.6 for numbers slightly smaller than expected).
- Strings: empty strings, normal valid strings, strings with whitespace, whitespace only strings
- Pointer: `nullptr`
