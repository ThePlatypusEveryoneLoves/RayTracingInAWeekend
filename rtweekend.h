#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

#include "ray.h"
#include "vec3.h"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random number
    std::default_random_engine gen(r());
    std::uniform_real_distribution<int> distrib(0.0, 1.0);
    return distrib(gen);
}


// Common Headers



#endif