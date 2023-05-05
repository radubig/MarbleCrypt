#include "Inventory.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Inventory& inv)
{
    os << "Cryptomonede detinute: " << inv.m_wallet << "\n";

    if(inv.m_marble_data_list.empty())
        os << "No marble data loaded!\n";
    else
    {
        os << "Marble data loaded:\n";
        for(const Inventory::MarbleData& md : inv.m_marble_data_list)
        {
            os << md.name << " " << md.daily_yield << " " << md.textureID << "\n";
        }
    }
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
    // TODO: Assign Texture ID properly in case of error at loading file
    std::fstream fin(filePath);
    if(!fin.is_open())
        throw ResourceLoadException(filePath);

    std::string line;
    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        MarbleData md;
        ss >> md.name >> md.daily_yield >> md.textureID;
        // Extra checking to ensure the texture exists in memory
        if(md.textureID > m_textures.size() - 1)
        {
            std::cout << "[WARNING] Texture ID #" << md.textureID << " is not loaded in memory!\n";
            std::cout << "[WARNING] The marble " << md.name << " has been discarded!\n";
            continue;
        }
        m_marble_data_list.push_back(std::move(md));
    }
    fin.close();
    m_generator.SetRange(0, m_marble_data_list.size()-1);
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
    auto index = m_generator();

    m_marbles.emplace_back(
        m_marble_data_list[index].name,
        m_marble_data_list[index].daily_yield,
        &m_textures[m_marble_data_list[index].textureID]
        );
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
