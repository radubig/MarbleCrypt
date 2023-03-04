#include "../include/Generator.h"
#include <fstream>
#include <iostream>
#include <sstream>

const long double Generator::s_initial_cost = 1.0;

Generator::Generator()
    :m_cost(Generator::s_initial_cost)
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
        m_marble_list.push_back(std::move(md));
    }
    fin.close();
}

std::ostream& operator<<(std::ostream& os, const Generator& gen)
{
    os << "Current cost: " << gen.m_cost << "\n";
    if(gen.m_marble_list.empty())
        os << "No marble data loaded!\n";
    else
    {
        os << "Marble data loaded:\n";
        for(const Generator::MarbleData& md : gen.m_marble_list)
        {
            os << md.name << " " << md.daily_yield << "\n";
        }
    }
    return os;
}
