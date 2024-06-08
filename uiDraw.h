#pragma once
#include <cstdlib>
#include <ctime>

// Initialize random seed
inline void initRandom() { std::srand(std::time(nullptr)); }

// Random number generation
inline double random(double min, double max) {
    return min + static_cast<double>(std::rand()) / (RAND_MAX / (max - min));
}

// Placeholder for drawing functions
inline void drawLine(double, double, double, double, double, double, double) {}
inline void drawRectangle(double, double, double, double, double, double) {}
inline void drawTarget(double, double) {}
