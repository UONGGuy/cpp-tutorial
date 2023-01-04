# Value categories

These include `lvalue`s and `rvalue`s.

To help determine how expressions should be evaluated and where they can be used, C++ expressions have a type and a value category.
An expression's type is equivalent to the type of the value, object or function that results from the evalutated expression.

The compiler determines expression type at compile-time via type inference of its components.

The value category of an expression indicates whether it resolves to a value, a function or an object of some kind.

Prior to C++11, the only value categories were `lvalue` and `rvalue`.
Post C++11, `glvalue`, `prvalue` and `xvalue` were added support the `move semantics` feature.

## lvalue and rvalue expressions

An lvalue expression is one that evaluates to an identifiable object, function or bit-field.
If an entity is  identifiable/has an identity in C++, it means it can be differentiated from other similar entities, typically by comparing addresses.
Entities with identities have longer lifetimes than single expressions or statements and can be accessed via an identifier, reference, or pointer.
Lvalue expressions can either be modifiable or non-modifiable.

An rvalue expression is an expression that is not an lvalue.
This includes literals (except C-style string literals as they are lvalues) and the return values of functions and operators.
Rvalues are not identifiable (i.e. must be used immediately) and only exist within the scope of the expression they are used in.

For this reason, only rvalues can be assigned (`=`) to lvalues and not the other way round.

```cpp
int x {};
x = 5; // valid
5 = x; // invalid
```

## lvalue to rvalue conversion

lvalues can also be converted to lvalues because they are implicitly converted to rvalues where required.

```cpp
int x { 1 };
int y { 2 };
x = y; // valid as y implicitly converted to rvalue
x = x + 1; // valid as x + 1 is an rvalue expression
```


