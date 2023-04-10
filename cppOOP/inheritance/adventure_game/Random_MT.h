#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

namespace RandomMT
{
    inline std::mt19937 init()
    {
        std::random_device rd;

        std::seed_seq ss{
            static_cast<unsigned int>
                (std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
        
        return std::mt19937{ ss };
    }

    inline std::mt19937 mt{ init() };

    inline int getRandomInt(int min, int max)
    {
        std::uniform_int_distribution<int> die{ min, max };
        return die(mt);
    }
};

#endif
