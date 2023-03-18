#include <Inventory.h>
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
    std::fstream fin(filePath);
    if(!fin.is_open())
    {
        std::cerr << "File " << filePath << " could not be open!\n";
        return;
    }
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
    std::fstream fin(filePath);
    if(!fin.is_open())
    {
        std::cerr << "File " << filePath << " could not be open!\n";
        return;
    }
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

void Inventory::Clear()
{
    m_wallet = CryptoCoin();
    m_marbles.clear();
    m_generator.ResetPrice();
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

bool Inventory::BuyMarble() // NOTE: this may need refactoring
{
    if(!m_wallet.Pay(m_generator.GetPrice()))
        return false;
    auto index = m_generator();

    Marble marble(
        m_marble_data_list[index].name,
        m_marble_data_list[index].daily_yield,
        m_marble_data_list[index].textureID
        );
    m_marbles.push_back(marble);
    return true;
}

void Inventory::CollectAll()
{
    for(Marble& marble : m_marbles)
    {
        long double ammount = marble.GetYield();
        m_wallet.Add(ammount);
    }
}

sf::Sprite Inventory::GenSprite()
{
    // Test rendering of first marble in list
    sf::Sprite sp;
    auto id = m_marbles[0].GetTextureID();
    sp.setTexture(m_textures[id]);
    return sp;
}

Marble& Inventory::operator[](uint32_t index)
{
    return m_marbles[index];
}
