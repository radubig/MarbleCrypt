#include "Marble.h"
#include <iostream>
#include <cmath>

Marble::Marble(std::string name, int64_t daily_yield, sf::Texture* texture_1, sf::Texture* texture_2) :
    m_name(std::move(name)),
    m_texture(texture_1),
    m_texture_2(texture_2),
    m_timepoint_gen(std::chrono::system_clock::now()),
    m_timepoint_last_yield(m_timepoint_gen),
    m_daily_yield(daily_yield)
{}

template<MarbleRarity T>
Marble::Marble(MarbleLoader::MarbleData<T> data) :
    m_name(data.name),
    m_texture(data.texture),
    m_texture_2(nullptr),
    m_timepoint_gen(std::chrono::system_clock::now()),
    m_timepoint_last_yield(m_timepoint_gen),
    m_daily_yield(static_cast<long long>(T))
{}

template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Normal> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Rare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::SuperRare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::UltraRare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Legendary> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Mythic> data);

Marble::Marble(const Marble& other) :
    m_name(other.m_name),
    m_texture(other.m_texture),
    m_texture_2(other.m_texture_2),
    m_timepoint_gen(other.m_timepoint_gen),
    m_timepoint_last_yield(other.m_timepoint_last_yield),
    m_daily_yield(other.m_daily_yield)
{}

Marble& Marble::operator=(const Marble& other)
{
    // Check for self assignment
    if(this == &other)
        return *this;
    m_name = other.m_name;
    m_texture = other.m_texture;
    m_texture_2 = other.m_texture_2;
    m_timepoint_gen = other.m_timepoint_gen;
    m_timepoint_last_yield = other.m_timepoint_last_yield;
    m_daily_yield = other.m_daily_yield;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Marble& marble)
{
    os << "Marble name: " << marble.m_name << "\n";
    os << "Marble daily yield: " << marble.m_daily_yield << "\n";
    std::time_t gen_time = std::chrono::system_clock::to_time_t(marble.m_timepoint_gen);
    std::time_t last_yield = std::chrono::system_clock::to_time_t(marble.m_timepoint_last_yield);
    os << "Marble generated on: " << std::ctime(&gen_time) << "\n";
    os << "Last time collected yield on: " << std::ctime(&last_yield);
    return os;
}

int64_t Marble::GetYield() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t dur = std::chrono::duration_cast<std::chrono::seconds>(now - m_timepoint_last_yield).count();
    double total_yield = double(dur) * YieldPerSec();
    //std::cout << "The yield of " << m_name << " is now " << total_yield << "\n";
    return int64_t(total_yield);
}

constexpr double Marble::YieldPerSec() const
{
    return double(m_daily_yield) / (24 * 60 * 60);
}

Marble::~Marble()
{
    if(!m_name.empty())
        std::cout << "Marble " << m_name << " got yeeted from memory!\n";
}

sf::Texture* Marble::GetTexturePtr() const
{
    return m_texture;
}

sf::Texture* Marble::GetTexturePtr2() const
{
    return m_texture_2;
}

const std::string& Marble::GetName() const
{
    return m_name;
}

void Marble::CollectYield()
{
    if(GetYield() > 0)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        m_timepoint_last_yield = now;
    }
}

int64_t Marble::GetDailyYield() const
{
    return m_daily_yield;
}
