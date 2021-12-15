#ifndef STARS_H
#define STARS_H

#include <random>
#include <vector>
#include <tuple>

// Mersenne Twister random number generator
std::mt19937 rng;

float getRandFloat(int min, int max)
{
    // Random number distribution
    std::uniform_real_distribution<float> dist(min, max);

    return dist(rng);
}

std::vector<std::tuple<float, float>> generateStarLocations()
{
    // Initialize with non-deterministic seed
    rng.seed(std::random_device{}());

    std::vector<std::tuple<float, float>> starLocs;
    for (int r = -8; r < 14; r++) {
        for (int c = -28; c < 28; c++) {
            starLocs.push_back(std::make_tuple(getRandFloat(c, c+1), getRandFloat(r, r+1)));
        }
    }

    return starLocs;
}

#endif // STARS_H
