#include "../include/CryptoCoin.h"

const long double CryptoCoin::s_initial_ammount = 90;

CryptoCoin::CryptoCoin(long double balance)
    :m_balance(balance)
{}

CryptoCoin::CryptoCoin(const CryptoCoin& other)
    :m_balance(other.m_balance)
{}

CryptoCoin::~CryptoCoin()
{}

CryptoCoin& CryptoCoin::operator=(const CryptoCoin& other)
{
    m_balance = other.m_balance;
    return *this;
}

bool CryptoCoin::Pay(long double ammount)
{
    if(ammount > m_balance)
        return false;
    m_balance -= ammount;
    return true;
}

void CryptoCoin::Add(long double ammount) noexcept
{
    m_balance += ammount;
}

long double CryptoCoin::Balance() const
{
    return m_balance;
}

std::ostream& operator<<(std::ostream& os, const CryptoCoin& wallet)
{
    os << wallet.m_balance;
    return os;
}


