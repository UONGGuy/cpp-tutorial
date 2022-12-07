# Error handling

It is important to check how your program behaves when it is not used as intended.

e.g. Function to look up grade for a student

Implict assumptions:
- Student looked up exists
- All student names unique
- Uses letter grading (as opposed to numeric or pass/fail)

Errors that may arise:
- May return function unsuccessfully (although assumed otherwise)
- Input may be incorrect in format and/or semantics

Defensive programming is a good way to anticipate and prepare for such events.

## Handling errors in functions

There are 4 general strategies for handling errors in functions:
- Handle the error within the function
- Pass the error back to the caller to deal with
- Halt the program
- Throw an exception

Errors have their own designated output stream which can be used to show messages when they occur.
These can be created using `std::cerr` which is the error stream equivalent of `std::cout`.

### Handling errors within functions

Usually the best strategy as the error is dealt with within the same function it arises in.
This keeps it contained and prevents it impacting other code outside the function.

The two main options are to:
- Retry until successful
- Cancel the operation

### Passing errors back to caller

For errors where they can't reasonably be handled within the function, returning the result to caller to deal with may be more appropriate.

e.g. A function that returns double { x / y } but y = 0.

In this case it may be better to change the function type to bool when looking to detect the error (and handle accordingly).
You could include an `if` statement for this particular case but the it may be difficult to detect if an error is occuring since the returned result is as expected and this may influence further code.

### Fatal errors

These are non-recoverable errors that prevent the program operating properly.

In these cases, it is best to terminate the program.
If the code is in `main()` or a function called directly from it it is best to let `main()` return a non-zero status code.
If the code is in some deeply nested subfunction, it may be better to use a halt statement where not possible to propagate the error back to `main()`.

### Exceptions

Because returning an error back to caller can be complicated and inconsistent, C++ offers `exceptions` as a way of passing errors back to caller.

When an error occurs, an exception is "thrown" and the current function has a chance to "catch" the error.
If it does not, then its caller has a chance to catch the error and this continues up the call stack with the caller of the previous caller having a chance to catch the error until it is either handled or `main()` fails to handle it.




