#ifndef MARBLECRYPT_DATALOADER_H
#define MARBLECRYPT_DATALOADER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class MarbleRarity {
    Normal = 200ll, Rare = 320ll, SuperRare = 510ll, UltraRare = 820ll, Legendary = 2000ll, Mythic = 16000ll
};

class MarbleLoader
{
public:
    template<MarbleRarity T>
    struct MarbleData
    {
        MarbleData(std::string , sf::Texture&);
        std::string name;
        sf::Texture* texture;
    };

    unsigned GetTotalDistinctMarbles() const;
    void LoadMarbleData(const std::string& filePath, std::vector<sf::Texture>& textures);
    MarbleData<MarbleRarity::Normal> GetNormalMarble() const;
    MarbleData<MarbleRarity::Rare> GetRareMarble() const;
    MarbleData<MarbleRarity::SuperRare> GetSuperRareMarble() const;
    MarbleData<MarbleRarity::UltraRare> GetUltraRareMarble() const;
    MarbleData<MarbleRarity::Legendary> GetLegendaryMarble() const;

private:
    std::vector<MarbleData<MarbleRarity::Normal>> m_normal;
    std::vector<MarbleData<MarbleRarity::Rare>> m_rare;
    std::vector<MarbleData<MarbleRarity::SuperRare>> m_super;
    std::vector<MarbleData<MarbleRarity::UltraRare>> m_ultra;
    std::vector<MarbleData<MarbleRarity::Legendary>> m_legendary;
};


#endif //MARBLECRYPT_DATALOADER_H
