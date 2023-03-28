#include "Generator.h"
#include <cmath>
#include <random>

const long double Generator::s_initial_cost = 1.0;

Generator::Generator()
    :m_cost(Generator::s_initial_cost),
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
