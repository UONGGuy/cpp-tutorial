# Numeral Systems

There are 4 main numeral systems in C++: decimal, binary, hexadecimal and octal (order of popularity).

## Decimal (base 10)
Digits from 0 - 9.
Standard counting system adopted by human beings.
Output value as decimal using `std::dec`

## Binary (base 2)
Only 2 digits: 0 and 1
Each place value is a power of 2.
Prefix literal with 0b to convert to binary literal.
Can use digit separators for readability (')
Use ==bitset== library and `std::bitset<n_bits> bin_obj_name {bin_literal}` to store binary values that can be output in binary format.

e.g. 0b1101 binary literal -> 13 decimal

## Octal (base 8)
Only 8 digits: 0 - 7.
Prefix literal with 0 to convert to octal literal.
Output value as decimal using `std::oct`

e.g. 0200 octal literal -> 128 decimal


## Hexadecimal (base 16)
Count digits as: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
Prefix literal with 0x to convert to hexadecimal literal.

e.g. 0x3A hexadecimal literal -> 58 decimal
