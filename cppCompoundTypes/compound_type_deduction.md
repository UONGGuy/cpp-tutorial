# Type deduction with pointers, references and const

As seen in type\_deduction.md, the `auto` keyword tells the compiler to deduce the type of a variable automatically.
It also drops `const` qualifiers by default (although these can be reapplied).

Type deduction also drops references (i.e. reference types cannot be deduced).
However, if we desire a deduced type to be a reference, then we can use `auto&`.

### High- and low-level const


