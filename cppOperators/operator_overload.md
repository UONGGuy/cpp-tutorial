# Operator overloading

Operators in C++ are implemented as functions meaning that they can be overloaded similarly to define your own versions that work with different data types (included user-defined classes).

This can lead to plenty of useful functionalities such as overloading the `<<` operator to print a class to the screen or a file.

## Operators as functions

As an example, consider:

```cpp
int x{ 2 };
int y{ 3 };
std::cout << x + y << '\n';
```

The compiler has its own version of the plus operator for integer operands where it evaluates the expression.
It is best to see this as a function call `operator+(x, y)`.

If we used doubles instead of integers, then the operator function call would be for the double data type.

When we try to add two objects of a user-defined class, the operator does not know how to deal with the operands and so an error occurs.

```cpp
Mystring string1 { "Hello, " };
Mystring string2 { "World!" };
std::cout << string1 + string2 << '\n';
```

We need to write an overloaded function to tell the compiler how the + operator should work for two operands of our user-defined type.

There are three different ways to overload operators:
- Using member functions
- Using friend functions
- Using normal functions

## Resolving overloaded operators

The compiler follows these rules when evaluating an expression with an operator:
- If all operands are fundamental data types, call a built-in routine if one exists. Else produce a compiler error.
- If any operand is a user-defined type (e.g. a class or an enum), look for a matching overloaded operator function to call. If not, try to convert to fundamental data types and use a matching built-in operator (via overloaded typecast). Produce a compile error if unsuccessful.

## Limitations of operator overloading

- Almost any existing C++ operator can be overloaded except conditional (`?:`), `sizeof`, scope (`::`), member selector (`.`), pointer member selector (`.*`), `typeid` and casting operators.
- It is not possible to create new operators or rename existing ones.
- At least one operand in an overloaded operator must be a user-defined type.
- It is not possible to change the number of operands supported by an operator.
- All operators keep their default precedence and associativity regardless of use.

It is best practice to keep the function of operators as close to their original intent as possible when overloading operators

If the meaning of an overloaded operator is not clear nor intuitive, it is better to use a named function instead.

## Choosing how to overload an operator

Generally, you can choose whether you want to use the normal, friend or member function version of the overload.
However, there are situations where one choice is usually better.

If we deal with binary operators that do not modify the left operand (e.g. `operator+`), the normal or friend function is usually preferred as it works for all parameter types (including when the left operand isn't a class object or is a non-modifiable class).
There is also the added benefit of "symmetry" in that each operand becomes an explicit parameter (as opposed to the left operand being a dereferenced variable of `*this` and the right operand being an explicit parameter).

If we deal with binary operators that modify the left operand (e.g. `operator+=`), the member function is typically preferred.
Usually the leftmost operand will be a class type and so it makes sense to have the modified object be the one pointed to by `*this`.
The rightmost operand then becomes an explicit parameter, thus there is no confusion about which is modified and which is evaluated.

Unary operators are usually overloaded as member functions as the member function versions have no parameters.

Some rules of thumb to help decide on implementation:
- Use a member function to overload assignment `=`, subscript `[]`, function call `()` and member selection `->` operators.
- Overload unary operators as member functions.
- Prefer normal functions then friend functions to overload binary operators that do not modify the left operand.
- If overloading a binary operator that modifies its left operand but can't add members to the class definition of the left operand (e.g. `operator<<` with type `std::ostream`), do so as a normal (preferred) or friend function.
- If overloading a binary operator that modifies its left operand (e.g. `operator+=`) and the left operand has a modifiable definition, do so as a member function.

## Minimising redundancy

More complex implementations of operators tend to have greater degrees of redundancy in that their actions can be mimicked by the combining other simpler operators.
For example:
- `operator!=` can be implemented as `!(operator==)`
- `operator>` can be implemented as `operator<` with the order of operands swapped
- `operator>=` can be implemented as `!(operator<)`
- `operator<=` can be implemented as `!(operator>)`

This means we may not need to implement the logic for all operators we want to overload with others being able to reuse definitions.

With the spaceship operator `<=>` being introduced in C++20 (returns -1, 0, 1), it allows us to reduce writing redundant code even more.



