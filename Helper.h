// helper.h
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>
#include <random>  
#include <limits>   

std::uniform_int_distribution<int> UNIFORM_DIST(0, 25); // random letters

//standard ETAOIN SHRDLU order
static const std::vector<double> ENGLISH_FREQ_RATE = {
    8.167,  // A
    1.492,  // B
    2.782,  // C
    4.253,  // D
    12.702, // E
    2.228,  // F
    2.015,  // G
    6.094,  // H
    6.966,  // I
    0.153,  // J
    0.772,  // K
    4.025,  // L
    2.406,  // M
    6.749,  // N
    7.507,  // O
    1.929,  // P
    0.095,  // Q
    5.987,  // R
    6.327,  // S
    9.056,  // T
    2.758,  // U
    0.978,  // V
    2.360,  // W
    0.150,  // X
    1.974,  // Y
    0.074   // Z
};

static const double BESTSCORE_PLACEHOLDER = -1e300;
static const double MIN_PENALTY = -10.0;

// generate rand strings
// L: length
// rng: random number generator
inline std::string RAND_STRING_GENERATOR(int L, std::mt19937& rng) {
    std::string s;
    s.resize(L);
    for (int i = 0; i < L; ++i)
    {
        s[i] = char('A' + UNIFORM_DIST(rng));
    }

    return s;
}

#endif
