#include "../include/Generator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <random>

const long double Generator::s_initial_cost = 1.0;

Generator::Generator()
    :m_cost(Generator::s_initial_cost),
    m_rng_engine(std::random_device()())
{
    this->LoadMarbleData("data/marbles.txt");
}

void Generator::RiseCost()
{
    m_cost *= 1.24L;
}

void Generator::LoadMarbleData(const std::string& filePath)
{
    std::fstream fin(filePath);
    if(!fin.is_open())
    {
        std::cerr << "File \"data/marbles.txt\" could not be open!\n";
        return;
    }
    std::string line;
    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        MarbleData md;
        ss >> md.name >> md.daily_yield;
        m_marble_data_list.push_back(std::move(md));
    }
    m_rng_distr.param(std::uniform_int_distribution<>::param_type{0, int(m_marble_data_list.size()) - 1});
    fin.close();
}

std::ostream& operator<<(std::ostream& os, const Generator& gen)
{
    os << "Current cost: " << gen.m_cost << "\n";
    if(gen.m_marble_data_list.empty())
        os << "No marble data loaded!\n";
    else
    {
        os << "Marble data loaded:\n";
        for(const Generator::MarbleData& md : gen.m_marble_data_list)
        {
            os << md.name << " " << md.daily_yield << "\n";
        }
    }
    return os;
}

void Generator::ResetPrice() noexcept
{
    m_cost = Generator::s_initial_cost;
}

long double Generator::GetPrice() const
{
    return std::trunc(m_cost);
}

Marble Generator::GenerateMarble()
{
    this->RiseCost();
    int index = m_rng_distr(m_rng_engine);
    const MarbleData& md = m_marble_data_list[index];
    return {md.name, md.daily_yield};
}
