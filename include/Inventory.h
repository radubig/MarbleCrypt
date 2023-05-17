#ifndef MARBLECRYPT_INVENTORY_H
#define MARBLECRYPT_INVENTORY_H

#include <ostream>
#include <vector>
#include "CryptoCoin.h"
#include "Marble.h"
#include "Generator.h"
#include "DataLoader.h"

class Inventory
{
public:
    Inventory() = default;
    ~Inventory() = default;
    friend std::ostream& operator<< (std::ostream& os, const Inventory& inv);

    Marble& operator[](uint32_t index);
    void LoadTextures(const std::string& filePath);
    void LoadMarbleData(const std::string& filePath);
    void SetDefault();
    long double GetBalance() const;
    long double GetNewMarblePrice() const;
    size_t GetMarblesSize() const; // TODO: refactor this
    bool BuyMarble();
    void CollectAll();
    void AddCoins(long double ammount) noexcept;
    void FusionMarbles(uint32_t index_first, uint32_t index_second);
    bool IsFusable(uint32_t index_first, uint32_t index_second) const;
    void BurnMarble(uint32_t index);
    long double GetBurnValue(uint32_t index) const;

    //Cheats:
    void GenerateEachRarity();

private:
    std::vector<sf::Texture> m_textures;
    CryptoCoin m_wallet;
    std::vector<Marble> m_marbles;
    Generator m_generator;
    MarbleLoader m_marble_loader;
};

#endif //MARBLECRYPT_INVENTORY_H
