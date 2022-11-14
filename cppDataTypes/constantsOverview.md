# CONSTANT = name that can be replaced by an unchanging value

Can have constant variables and expressions.

**Compile-time** => value known when code is compiled but NOT run (yet)

**Runtime** => initialisation value only known when executable is running

Can use the `constexpr` keyword to ensure a compile-time constant.
If variable is a runtime constant, compiler will return an error.

**Literal** => values cannot be reassigned.

Can change type of a literal by adding specific suffixes.
(Necessary when initialising variables e.g. `float a { 4.1f }` [4.1 is a double literal])
