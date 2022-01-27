#pragma once
#include <cstdlib>
#include <random>

//Used as home for any random generator used in the Project

std::pair<int, int> basicExpiryGen()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<float> yearGen(0, 0.2);
    int yr = std::floor(std::fabs(yearGen(gen)));

    std::normal_distribution<float> dayGen(25, 10);
    int d = std::floor(std::fabs(dayGen(gen)));

    return std::make_pair(d, yr);
}

int arrivalTimeGen()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<float> dayGen(4, 1);
    int arrives = std::floor(std::fabs(dayGen(gen)));
    return arrives;
}