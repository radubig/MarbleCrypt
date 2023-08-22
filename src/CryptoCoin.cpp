#include "CryptoCoin.h"
#include <iomanip>

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
    unsigned char buf[sizeof (long double)];
    long double value = wallet.m_balance;
    std::copy(reinterpret_cast<const unsigned char *> (&value),
              reinterpret_cast<const unsigned char *> (&value) + sizeof(long double),
              buf);
    for(unsigned int i : buf)
        os << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << i;
    os << std::dec;
    return os;
}


