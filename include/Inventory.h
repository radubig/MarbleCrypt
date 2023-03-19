#ifndef MARBLECRYPT_INVENTORY_H
#define MARBLECRYPT_INVENTORY_H

#include <ostream>
#include <vector>
#include <CryptoCoin.h>
#include <Marble.h>
#include <Generator.h>

class Inventory
{
    struct MarbleData
    {
        std::string name;
        long long daily_yield;
        uint32_t textureID;
        //int rarity;
    };

public:
    Inventory() = default;
    ~Inventory() = default;
    friend std::ostream& operator<< (std::ostream& os, const Inventory& inv);

    Marble& operator[](uint32_t index);
    void LoadTextures(const std::string& filePath);
    void LoadMarbleData(const std::string& filePath);
    void Clear();
    void SetDefault();
    long double GetBalance() const;
    long double GetNewMarblePrice() const;
    const std::vector<Marble>& GetMarbles() const; // TODO: refactor this
    [[maybe_unused]] void Reserve(size_t size);
    bool BuyMarble();
    void CollectAll();

private:
    std::vector<sf::Texture> m_textures;
    std::vector<MarbleData> m_marble_data_list;
    CryptoCoin m_wallet;
    std::vector<Marble> m_marbles;
    Generator m_generator;
};

#endif //MARBLECRYPT_INVENTORY_H
