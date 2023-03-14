#include <Inventory.h>
#include <iostream>

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
    m_generator.ResetPrice();
}

void Inventory::ResetDefault()
{
    m_wallet = CryptoCoin(CryptoCoin::s_initial_ammount);
    m_marbles.clear();
    m_generator.ResetPrice();
}

long double Inventory::GetBalance() const
{
    return m_wallet.Balance();
}

long double Inventory::GetNewMarblePrice() const
{
    return this->m_generator.GetPrice();
}

bool Inventory::BuyMarble()
{
    if(!m_wallet.Pay(m_generator.GetPrice()))
        return false;
    m_marbles.emplace_back(m_generator.GenerateMarble());
    return true;
}

void Inventory::ShowGeneratorData() const
{
    std::cout << m_generator << "\n";
}

void Inventory::CollectAll()
{
    for(Marble& marble : m_marbles)
    {
        long double ammount = marble.GetYield();
        m_wallet.Add(ammount);
    }
}
