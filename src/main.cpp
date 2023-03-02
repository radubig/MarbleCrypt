#include <iostream>
#include "../include/Marble.h"
#include "../include/CryptoCoin.h"

int main()
{
    Marble marble("Bilutza", 1440.0);
    std::cout << marble << "\n";
    marble.GetYield();
    return 0;
}
