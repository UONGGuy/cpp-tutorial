# Assertions

Conditional statements used to detect invalid parameters or validate other assumptions.
Can also print error messages and terminate programs.
Always true unless bug occurs.
Very useful in debugging.

Used to document cases that should be logically impossible/never happen in the program.

Unlike error handling, does not allow program to recover from errors.

## Asserts

`assert()` lives in the \<cassert\> header.
In the argument, insert a statement that should be true for the program to function (e.g. `x > 0`).
Can use `&&` and a string in argument to better describe the statement tested as string will appear in assertion error message (and strings are always Boolean true).

`assert` comes with a small performance cost every time the condition is checked.
`assert`s should also ideally never be encountered in production code so.
If the macro `NDEBUG` is defined, the `assert` macro is disabled.

There are also limitations to asserts.
Asserts themselves can also have bugs which will cause errors to be reported when they don't exist or failure to report occuring bugs.
Asserts should have no side effects (i.e. program should run the same with and without the assert) otherwise the release configuration may not be the same as the debug configuration (assuming you ship with `NDEBUG`.
Since `abort()` terminates the program without cleanup, asserts should only be used where corruption is unlikely to occur if the program terminates unexpectedly.

## Static asserts

`static_assert()` is a keyword (i.e. no header needed) which is an assertion checked at compile-time rather than runtime.
It takes the form `static_assert(condition, diagnostic_message)`.
Static asserts can be placed anywhere in the code file, unlike normal assertions.

