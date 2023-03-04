#ifndef MARBLECRYPT_GENERATOR_H
#define MARBLECRYPT_GENERATOR_H

#include <vector>
#include <string>
#include <ostream>

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
    friend std::ostream& operator<< (std::ostream& os, const Generator& gen);

    void LoadMarbleData(const std::string& filePath);

private:
    long double m_cost; //NOTE: Groth rate set to 1.24x
    std::vector<MarbleData> m_marble_list;

    void RiseCost();

};

#endif //MARBLECRYPT_GENERATOR_H
