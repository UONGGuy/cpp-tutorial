# Type conversion

Type conversion = converting a value from one data type to another.

Can be invoked implicity by compiler or explicitly by programmer.

Implicit = coercion
Explicit = casting

## Implicit conversion (coercion)

Performed when one data type required by a different one is supplied (e.g. when initialising, returning, for non-Booleans, argument passing, etc.).

Compiler determines whether type conversion is possible and does if so.
If not possible, compilation fails with compile error.

4 types of standard conversions:
- Numeric promotions
- Numeric conversions
- Arithmetic conversions
- Other conversions (inc. pointers and references)

Mainly need to know it "just works".
If need finer detail, look up at https://en.cppreference.com/w/cpp/language/implicit_conversion.

### Numeric promotions

Type conversion of narrower numeric types (e.g. `char`) to wider numeric types (e.g. `int` or `double`).

Numeric promotions are value-preserving: all values in original type representable without loss of data or precision in new type.

Mainly favoured by compiler and reduces redundancy (e.g. a function returning a `double` can be called with `int` parameters).

Two main sub-categories: integral promotions and floating point promotions.

Floating point promition: 
-`float` -> `double`.

Integral promotion:
- signed char or signed short -> `int`
- unsigned char, char8\_t and unsigned short -> `int` (if can hold entire range of the type, unsigned int else)
- If signed by default, follows signed rules. If unsigned by default, follows unsigned rules.
- `bool` -> `int` (`false` = `0`, `true` = `1`)

Are other less common rules that can be found here: https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion

Although integral promotion is value-preserving, it is not necessarily sign preserving (of the type).

### Numeric conversions

Type conversions not covered by rules mentioned under numeric promotions are numeric conversions.

Five basic types of numeric converions:
- Integral type -> any other integral type
- Floating point type -> any other floating point type
- Floating point type -> any integral type
- Integral type -> any floating point type
- Integral/floating point type -> bool

A quick reminder that brace initialisation disallows some conversions so this mainly applies when copy initialisation is used.

Numeric conversions can result in the loss of data or precision depending on the value and range of types being converted.
Such conversions are called narrowing conversions.
If the converted value is constexpr and in range of the destination type, then the conversion might not be narrowing.

Compilers generally warn of implicit narrowing conversions (but not always and especially when converting between signed and unsigned types).

As a general rule of thumb, try to avoid narrowing conversions and if necessary, make them explicit by using `static_cast`.

In all cases converting values which are outside the range of the desired type will lead to unexpected results.

### Arithmetic conversions

Certain operators require their operands to be of the same type.
If this is not the case, one or both of the operands will be implicity converted to the matching types following the rules for usual arithmetic conversions.

Such operators include:
- Binary arithmetic operators: +, -, \*, /, %
- Binary relational operators: <, >, <=, >=, ==, !=
- Binary bitwise arithmetic operators: &, ^, |
- The conditional operator: ?:

The compiler has a prioritised list of types by which operands of lower priority are converted to match higher priority operands.
Otherwise both operands are numerically promoted.

Prioritisation hierachy can cause issues when mixing signed and unsigned values as results are unexpected and without warnings being issued.

## Explicit conversion (casting)

Although values can be implicitly converted, this is not the case for variables.
If we want to ensure that operations with variables are processed into the correct type, it is necessary to cast variables to the appropriate type first.

### Type casting

C++ supports 5 types of casts:
- C-style casts
- static casts
- const casts
- dynamic casts
- reinterpret casts

The last 4 are sometimes referred to as named casts.

In general, avoid const casts and reinterpret casts as they are only useful in rare cases and can be harmful if incorrectly used.

### C-style casts

Performed using the `()` operator. The variable is cast to the type in the parentheses.

```cpp
int x { 10 };
int y { 4 };
double d { (double)x / y }; // converts x -> double, implicitly converts y -> double
```

The C-style casts can perform a variety of conversions depending on context.
These include a static cast, const cast or reinterpret cast.

Due to this, there is a chance of misuse leading to unexpected behaviour.
Best practice is to avoid using C-style casts.

### Static cast

The `static_cast<>()` operator converts the variable in the parentheses to the type in the angled brackets.
Its main advantage is that it provides compile-time checking.

It is best used to convert a fundamental type into another but is also used for explicit narrowing conversions to avoid compiler errors.



