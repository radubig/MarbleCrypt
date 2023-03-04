#ifndef MARBLECRYPT_INVENTORY_H
#define MARBLECRYPT_INVENTORY_H

#include <ostream>
#include <vector>
#include "CryptoCoin.h"
#include "Marble.h"
#include "Generator.h"

class Inventory
{
public:
    Inventory() = default;
    ~Inventory() = default;
    friend std::ostream& operator<< (std::ostream& os, const Inventory& inv);

    void Clear();
    void ResetDefault();
    long double GetBalance() const;
    long double GetNewMarblePrice() const;
    bool BuyMarble();
    void ShowGeneratorData() const;
    void CollectAll();

private:
    CryptoCoin m_wallet;
    std::vector<Marble> m_marbles;
    Generator m_generator;
};

#endif //MARBLECRYPT_INVENTORY_H
