#include "DataLoader.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "Generator.h"

void MarbleLoader::LoadMarbleData(const std::string& filePath, std::vector<sf::Texture>& textures)
{
    // TODO: Assign Texture ID properly in case of error at loading file
    std::fstream fin(filePath);
    if(!fin.is_open())
        throw ResourceLoadException(filePath);

    std::string line;
    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        int rarity;
        std::string name;
        uint32_t texID;
        ss >> rarity >> name >> texID;
        // Extra checking to ensure the texture exists in memory
        if(texID > textures.size() - 1)
        {
            std::cout << "[WARNING] Texture ID #" << texID << " is not loaded in memory, so marble " << name << " has been discarded!\n";
            continue;
        }
        switch(rarity)
        {
            case 1: m_normal.emplace_back(name, textures[texID]); break;
            case 2: m_rare.emplace_back(name, textures[texID]); break;
            case 3: m_super.emplace_back(name, textures[texID]); break;
            case 4: m_ultra.emplace_back(name, textures[texID]); break;
            case 5: m_legendary.emplace_back(name, textures[texID]); break;
            default: std::cout << "[WARNING] Marble " << name << " has invalid rarity, so it has been discarded!\n";
        }
    }
    fin.close();
}

template<MarbleRarity T>
MarbleLoader::MarbleData<T>::MarbleData(std::string _name, sf::Texture& _texture) :
    name(std::move(_name)),
    texture(&_texture)
{}

MarbleLoader::MarbleData<MarbleRarity::Normal> MarbleLoader::GetNormalMarble() const
{
    Generator gen;
    gen.SetRange(0, m_normal.size()-1);
    return m_normal[gen()];
}
MarbleLoader::MarbleData<MarbleRarity::Rare> MarbleLoader::GetRareMarble() const
{
    Generator gen;
    gen.SetRange(0, m_rare.size()-1);
    return m_rare[gen()];
}
MarbleLoader::MarbleData<MarbleRarity::SuperRare> MarbleLoader::GetSuperRareMarble() const
{
    Generator gen;
    gen.SetRange(0, m_super.size()-1);
    return m_super[gen()];
}
MarbleLoader::MarbleData<MarbleRarity::UltraRare> MarbleLoader::GetUltraRareMarble() const
{
    Generator gen;
    gen.SetRange(0, m_ultra.size()-1);
    return m_ultra[gen()];
}
MarbleLoader::MarbleData<MarbleRarity::Legendary> MarbleLoader::GetLegendaryMarble() const
{
    Generator gen;
    gen.SetRange(0, m_legendary.size()-1);
    return m_legendary[gen()];
}