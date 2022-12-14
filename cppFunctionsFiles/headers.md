# HOW HEADERS WORK

Headers are files acting as links between your main program file and 
other files which contain the functions you intend to use in your main.
They forward declare functions from one file to be used in another and
are denoted by the ".h" extension.

Requires:
- add.cpp [File containing functions, classes]
- add.h [Header file]
- main.cpp [Main program file]

## STRUCTURE OF add.cpp:

```cpp
#include "add.h" // Insert header file forward declarations
// Include other necessary libraries for functions
// Write functions
```

## STRUCTURE OF add.h:

```cpp
#ifndef ADD_H // Use header guards!
#define ADD_H

// Paired header file
// Other header files from project
// 3rd party library headers
// Standard library headers

// Function declaration(s)

#endif
```

## STRUCTURE OF main.cpp:

```cpp
// Add in this order and alphabetically
#include "add.h" //Paired header file
// Other headers from project
// 3rd party library headers
// Standard library headers
```
