#include "getRandomNumber.h"

// Get random number
int LE::getRandomInt(const int Min, const int Max)
{
    // create mersenne twister engine with random device seed
    std::random_device rd;
    std::mt19937 mersenne(rd());

    // create uniform distribution from min to max
    std::uniform_int_distribution<> dist(Min, Max);

    // generate a random integer using the distribution and return it
    return dist(mersenne);
}
float LE::getRandomFloat(const float Min, const float Max)
{
    static std::random_device rd;
    static std::mt19937 mersenne(rd());
    std::uniform_real_distribution<float> distribution(Min, Max);
    return distribution(mersenne);
}