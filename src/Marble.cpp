#include <Marble.h>
#include <iostream>

Marble::Marble(std::string name, int64_t daily_yield, uint32_t textureID) :
    m_name(std::move(name)),
    m_textureID(textureID),
    m_timepoint_gen(std::chrono::system_clock::now()),
    m_timepoint_last_yield(m_timepoint_gen),
    m_daily_yield(daily_yield)
{}

Marble::Marble(const Marble& other) :
    m_name(other.m_name),
    m_textureID(other.m_textureID),
    m_timepoint_gen(other.m_timepoint_gen),
    m_timepoint_last_yield(other.m_timepoint_last_yield),
    m_daily_yield(other.m_daily_yield)
{}

Marble& Marble::operator=(const Marble& other)
{
    m_name = other.m_name;
    m_textureID = other.m_textureID;
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

int64_t Marble::GetYield()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int64_t dur = std::chrono::duration_cast<std::chrono::seconds>(now - m_timepoint_last_yield).count();
    int64_t total_yield = (dur / 30) * YieldPer30s();
    std::cout << "The yield of " << m_name << " is now " << total_yield << "\n";
    m_timepoint_last_yield = now;
    return total_yield;
}

constexpr int64_t Marble::YieldPer30s() const
{
    return m_daily_yield / 2880;
}

Marble::~Marble()
{
    std::cout << "Marble " << m_name << " got yeeted from memory!\n";
}

uint32_t Marble::GetTextureID() const
{
    return m_textureID;
}
