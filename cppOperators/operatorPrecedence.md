# Operators

Operation = mathematical calculation between input values -> new output value.

## Operator precedence and associativity

i.e. the order of operations in compound (multi-operator) expressions.

Operators have precedence levels from 1 - 17 determining the order in which they are evaluated.

If operators have the same precedence level, their associativity tells the compiler whether to evaluate them from Left-to-Right (L-\>R) or Right-to-Left (R-\>L).

A table of operators, their precedence levels and associativity can be found here:[ ](https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/)

It is important to note the program can evaluate ambiguous expressions in whichever order it believes to be most efficient so variable management is important.

> Best practices
> - Use parentheses to clearly show the order of evaluations.
> - Check operator associativity for identiacl precedence levels.
> - Ensure expressions are not dependent on the order of evaluation.
> - Be wary of prefix vs decrement operators to ensure the correct value is being evaluated.

## Bit manipulation

A bit is the smallest unit of data a computer can process or store.
It is represented by a single, binary value: 0 or 1.
By using `std::bitset`, we can be more efficient with assigning memory to values.

There are a collection of bitwise operators which act on and manipulate individual bit flags.
Bitmasks can be used to protect values from the actions of operators.
