#include "Inventory.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Inventory& inv)
{
    os << "Cryptomonede detinute: " << inv.m_wallet << "\n";
    os << "\n";
    os << "Enumerare bile detinute:\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(const Marble& marble : inv.m_marbles)
        os << marble << "\n";
    os << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    return os;
}

void Inventory::LoadTextures(const std::string& filePath)
{
    // TODO: Assign Texture ID properly in case of error at loading file
    std::fstream fin(filePath);
    if(!fin.is_open())
        throw ResourceLoadException(filePath);

    std::string line;
    while(std::getline(fin, line))
    {
        sf::Texture texture;
        if(!texture.loadFromFile(line))
        {
            std::cerr << "Image " << line << " could not be loaded!\n";
            continue;
        }
        m_textures.push_back(std::move(texture));
    }
    fin.close();
}

void Inventory::LoadMarbleData(const std::string& filePath)
{
    m_marble_loader.LoadMarbleData(filePath, m_textures);
    m_generator.SetRange(1, 100);
}

void Inventory::SetDefault()
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
    auto chance = m_generator();
    if(chance <= 54) m_marbles.emplace_back(m_marble_loader.GetNormalMarble());
    else if(chance <= 84) m_marbles.emplace_back(m_marble_loader.GetRareMarble());
    else if(chance <= 96) m_marbles.emplace_back(m_marble_loader.GetSuperRareMarble());
    else if(chance <= 99) m_marbles.emplace_back(m_marble_loader.GetUltraRareMarble());
    else m_marbles.emplace_back(m_marble_loader.GetLegendaryMarble());

    return true;
}

void Inventory::CollectAll()
{
    for(Marble& marble : m_marbles)
    {
        long double ammount = marble.GetYield();
        m_wallet.Add(ammount);
        marble.CollectYield();
    }
}

Marble& Inventory::operator[](uint32_t index)
{
    return m_marbles[index];
}

std::vector<Marble>& Inventory::GetMarbles()
{
    return m_marbles;
}

void Inventory::AddCoins(long double ammount) noexcept
{
    m_wallet.Add(ammount);
}

void Inventory::FusionMarbles(uint32_t index_first, uint32_t index_second)
{
    // check if the elements do exist in the vector
    if(index_first >= m_marbles.size() || index_second >= m_marbles.size())
        throw std::runtime_error("Indicies provided for fusioning are out of bounds!");

    if(index_first > index_second)
        std::swap(index_first, index_second);

    // create new marble based on previous 2 marbles
    m_marbles.emplace_back(
            m_marbles[index_first].GetName() + m_marbles[index_second].GetName(),
            std::max(m_marbles[index_first].GetDailyYield(), m_marbles[index_second].GetDailyYield()) * 5,
            m_marbles[index_first].GetTexturePtr(),
            m_marbles[index_second].GetTexturePtr()
            );

    m_marbles.erase(m_marbles.begin() + index_second);
    m_marbles.erase(m_marbles.begin() + index_first);
}

bool Inventory::IsFusable(uint32_t index_first, uint32_t index_second) const
{
    // Returns false if the indicies provided are out of bounds or if the selected marbles are not basic marbles
    // Otherwise returns true

    if(index_first >= m_marbles.size() || index_second >= m_marbles.size())
        return false;
    if(m_marbles[index_first].GetTexturePtr2() != nullptr ||
       m_marbles[index_second].GetTexturePtr2() != nullptr)
        return false;
    return true;
}
