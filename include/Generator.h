#ifndef MARBLECRYPT_GENERATOR_H
#define MARBLECRYPT_GENERATOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ostream>
#include <random>
#include "Marble.h"

class Generator
{
public:
    static const long double s_initial_cost;

    explicit Generator();
    ~Generator() = default;
    friend std::ostream& operator<< (std::ostream& os, const Generator& gen);

    void SetRange(uint32_t range_min, uint32_t range_max);
    void ResetPrice() noexcept;
    long double GetPrice() const;
    uint32_t operator()();

private:
    long double m_cost; //NOTE: Groth rate set to 1.24x
    // Tools for modern RNG
    std::mt19937 m_rng_engine;
    std::uniform_int_distribution<uint32_t> m_rng_distr;

    void RiseCost();
};

#endif //MARBLECRYPT_GENERATOR_H
