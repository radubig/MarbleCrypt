#include "Generator.h"
#include <cmath>
#include <random>
#include <iomanip>

const long double Generator::s_initial_cost = 1.0;

Generator::Generator(long double cost)
    :m_cost(cost),
    m_rng_engine(std::random_device()())
{}

void Generator::RiseCost()
{
    m_cost *= 1.24L;
}

void Generator::ResetPrice() noexcept
{
    m_cost = Generator::s_initial_cost;
}

long double Generator::GetPrice() const
{
    return std::trunc(m_cost);
}

uint32_t Generator::operator()()
{
    this->RiseCost();
    return m_rng_distr(m_rng_engine);
}

void Generator::SetRange(uint32_t range_min, uint32_t range_max)
{
    m_rng_distr.param(std::uniform_int_distribution<uint32_t>::param_type{range_min, range_max});
}

std::ostream& operator<<(std::ostream& os, const Generator& gen)
{
    unsigned char buf[sizeof (long double)];
    long double value = gen.m_cost;
    std::copy(reinterpret_cast<const unsigned char *> (&value),
              reinterpret_cast<const unsigned char *> (&value) + sizeof(long double),
              buf);
    for(unsigned int i : buf)
        os << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << i;
    os << std::dec;
    return os;
}

void Generator::ResetPrice(long double cost) noexcept
{
    m_cost = cost;
}
