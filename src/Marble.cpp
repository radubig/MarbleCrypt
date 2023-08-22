#include "Marble.h"
#include <iostream>
#include <cmath>

Marble::Marble(std::string name, int64_t daily_yield, sf::Texture* texture_1, sf::Texture* texture_2, MarbleRarity rarity) :
    m_name(std::move(name)),
    m_texture(texture_1),
    m_texture_2(texture_2),
    m_rarity(rarity),
    m_timepoint_last_yield(std::chrono::system_clock::now()),
    m_daily_yield(daily_yield)
{}

template<MarbleRarity T>
Marble::Marble(MarbleLoader::MarbleData<T> data) :
    m_name(data.name),
    m_texture(data.texture),
    m_texture_2(nullptr),
    m_rarity(T),
    m_timepoint_last_yield(std::chrono::system_clock::now()),
    m_daily_yield(static_cast<long long>(T))
{}

template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Normal> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Rare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::SuperRare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::UltraRare> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Legendary> data);
template Marble::Marble(MarbleLoader::MarbleData<MarbleRarity::Mythic> data);

std::ostream& operator<<(std::ostream& os, const Marble& marble)
{
    os << marble.m_name << "\n";        // Marble name
    os << marble.m_daily_yield << "\n"; // Marble daily yield
    os << marble.m_timepoint_last_yield.time_since_epoch().count(); // Last yield

    //std::time_t last_yield = std::chrono::system_clock::to_time_t(marble.m_timepoint_last_yield);
    //os << "Last time collected yield on: " << std::ctime(&last_yield);
    return os;
}

int64_t Marble::GetYield() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t dur = std::chrono::duration_cast<std::chrono::seconds>(now - m_timepoint_last_yield).count();
    double total_yield = double(dur) * YieldPerSec();
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

MarbleRarity Marble::GetRarity() const
{
    return m_rarity;
}
