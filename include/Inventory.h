#ifndef MARBLECRYPT_INVENTORY_H
#define MARBLECRYPT_INVENTORY_H

#include <ostream>
#include <vector>
#include "CryptoCoin.h"
#include "Marble.h"

class Inventory
{
public:
    Inventory() = default;
    ~Inventory() = default;
    friend std::ostream& operator<< (std::ostream& os, const Inventory& inv);

private:
    CryptoCoin m_wallet;
    std::vector<Marble> m_marbles;
    // + un generator de bile
};

#endif //MARBLECRYPT_INVENTORY_H
