#pragma once

#include <cstdlib>
#include <random>
#include "Date.h"
//Used as home for any random generator used in the Project

int basicExpiryGen(int seed)
{
    std::random_device rd;
    std::mt19937 gen(seed == 0 ? rd() : seed);

    std::normal_distribution<float> yearGen(0, 0.2);
    int yr = std::floor(std::fabs(yearGen(gen)));

    std::normal_distribution<float> dayGen(30, 10);
    int d = std::floor(std::fabs(dayGen(gen)));

    for (yr; yr > 0; yr--)
    {
        Date::isLeap(yr) ? d += 366 : d += 365;
    }
    return d;
}

int arrivalTimeGen(int seed)
{
    std::random_device rd;
    std::mt19937 gen(seed == 0 ? rd() : seed);

    std::normal_distribution<float> dayGen(4, 1);
    int arrives = std::floor(std::fabs(dayGen(gen)));
    return arrives;
}