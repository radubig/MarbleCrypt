#include "../include/Inventory.h"

std::ostream& operator<<(std::ostream& os, const Inventory& inv)
{
    os << "Cryptomonede detinute: " << inv.m_wallet << "\n";
    os << "Enumerare bile detinute:\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(const Marble& marble : inv.m_marbles)
        os << marble << "\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    return os;
}

void Inventory::Clear()
{
    m_wallet = CryptoCoin();
    m_marbles.clear();
}

void Inventory::ResetDefault()
{
    m_wallet = CryptoCoin(CryptoCoin::s_initial_ammount);
    m_marbles.clear();
}
