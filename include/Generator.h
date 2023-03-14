#ifndef MARBLECRYPT_GENERATOR_H
#define MARBLECRYPT_GENERATOR_H

#include <vector>
#include <string>
#include <ostream>
#include <random>
#include <Marble.h>

class Generator
{
    struct MarbleData
    {
        std::string name;
        long long daily_yield;
        //std::string texture_path;
        //int rarity;
    };

public:
    static const long double s_initial_cost;

    explicit Generator();
    ~Generator() = default;
    friend std::ostream& operator<< (std::ostream& os, const Generator& gen);

    void LoadMarbleData(const std::string& filePath);
    void ResetPrice() noexcept;
    long double GetPrice() const;
    Marble GenerateMarble();

private:
    long double m_cost; //NOTE: Groth rate set to 1.24x
    std::vector<MarbleData> m_marble_data_list;
    // Tools for modern RNG
    std::mt19937 m_rng_engine;
    std::uniform_int_distribution<> m_rng_distr;

    void RiseCost();
};

#endif //MARBLECRYPT_GENERATOR_H
