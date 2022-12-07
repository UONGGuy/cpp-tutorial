# Random number generation

Extremely useful - especially in statistical modelling and cryptology.

Computers can only simulate randomness using algorithms.

## Context

Algorithm = finitie sequence of instructions that produce some useful result.

Stateful = algorithm that retains information across calls (e.g. static integer incrememnter)

Stateless = algorithm that doesn't store information and must be given all information it needs to work with when calle.

Deterministic = algorithm that always produces the same output for a given input.

## Pseudo-random number generators (PRNGs)

These are algorithms that generate a sequence of numbers with properties simulating a sequence of random numbers.

There are various ways this can be done - for example, using large constants and overflow.

However, these sequences are not truly random and are deterministic based on their initialised random seed.
The seed determines the sequence of numbers that will be output.

Good PRNGs should:
- Generate each number with approximately the same probability (distribution uniformity)
- Have a good dimensional distribution of numbers (i.e. good spread of high and low value results) 
- Have a long period for all seeds (i.e. long sequence length before repeating)
- Be efficient

There are many different PRNG algorithms with their own strengths and weaknesses that can be picked depending on application.

## Randomisation in C++

Randomisation capabilities are accessible through the `<random>` header of the standard library.

For a list of the PRNG families see https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/

Can convert PRNG values to those from a random number distribution.

e.g. Uniform distribution

```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt; // instantiate 32-bit Mersenne Twister algorithm

    // Create reusable RNG generating uniform numbers from 1 - 6
    std::uniform_int_distribution die6{ 1, 6 }; // for C++14 use std::uniform_int_distribution<> die6{ 1, 6 };

    // Print result of 20 dice rolls
    for (int roll{ 1 }; roll <= 20, ++roll)
    {
        std::cout << die6(mt) << '\t';

        if (roll % 10 == 0)
        {
            std::cout << '\n';
        }
    }

    return 0;
}
```

Due to seeding, note that program always produces same sequence of results when it is run.

To always generate different sequences of pseudo-random numbers, can seed using the system clock or system random device.

However, PRNGs should **only be seeded once** due to inefficiency and the loss of random element from continual re-initialisation.

## Seeding with the system clock

Can use current time or time passed since earliest measured time as a way of seeding PRNG algorithms.
Can do this using macros from the `<chrono>` header.

Useful macros include:
- `std::time()` for current time
- `std::chrono::high_resolution_clock` for a clock with the most granular unit of time
- `std::chrono::steady_clock::now().time_since_epoch().count()` for time elsapsed since program run from a clock users cannot adjust

## Seeding using random devices

`std::random_device{}()` is an implementation-defined PRNG in the `<random>` library.
It typically asks the OS for a random number.

Best practice is to use this to seed PRNGs unless it's not implemented properly for the target compiler/architecture.

An issue to bear in mind is that `std::random_device` can be deterministic on some systems, producing the same sequence every time.

## Random numbers across multiple functions

If RNG is needed in multiple functions, it can be better to create a global RNG (inside a namespace) instead of creating a PRNG in main and passing it around or creating an individual PRNG for each function.

This tends to be one of the exceptions to creating non-const global variables.

```cpp
#include <random>

namespace Random // capital R to avoid collisions
{
    std::mt19937 mt{ std::random_device{}() };

    int uniform(int min, int max)
    {
        std::uniform_int_distribution die{ min, max };
        
        return die(mt);
    }
}
```

## Underseeding

Underseeding refers to initialising a PRNG algorithm that is x-bytes with a y-byte value where y < x.
The random library tries to fill in the remaining bytes with "random" data but is not perfect. 
Underseeded PRNGs can generate suboptimal results - especially for applications requiring high quality results.

`std::seed_seq` is one way to try and handle underseeding.
It can hold multiple seed values as well as generate additional unbiased seed values to initialise a PRNG's state.
By providing `std::seed_seq` with more random data, it can work better.

An example of setting this up is as follows:

```cpp
#include <random>

int main()
{
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()}; // get 8 random integers from random device for seed sequence
    std::mt19937 mt{ ss };

    return 0;
}
```

Alternatively, a PRNG with smaller state can be used instead.

## Warming up PRNGs

Underseeding tends to lead to poor initial PRNG results.

"Warming up" PRNGs refers to running the PRNG, discarding the first N results, then using results after the internal state is sufficiently mixed up.
Typically a few hundred to a few thousand initial results are discarded.
The longer the period of the PRNG, the more initial results should be discarded.

`seed_seq` initialisation used by `std::mt19937` performs a warm up so `std::mt19937` objects do not need to be explicitly warmed up.

## Debugging programs with random numbers

Due to changes in behaviour, it can be difficult to debug such programs.

For this reason, it is useful to choose a specific seed value when debugging so that results can be compared as you work on the program.
Normal seeding can be used once the program has been debugged.
