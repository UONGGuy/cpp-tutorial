/*  Header file containing Mersenne Twister PRNG 
 *  
 *  Contains self-seeding Mersenne Twister in the Random namespace
 *
 */

#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

namespace Random
{
    inline std::mt19937 init()
    {
        std::random_device rd;

        // create seed_seq with high-res clock, 7 random numbers from std::random_device
        std::seed_seq ss{ static_cast<unsigned int>
            (std::chrono::steady_clock::now().time_since_epoch().count()),
                rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        return std::mt19937{ ss };
    }

    inline std::mt19937 mt{ init() }; // PRNG object

    inline int get(int min, int max) // Generate uniform distrib RN
    {
        std::uniform_int_distribution die{ min, max };
        return die(mt);
    }
};

#endif
