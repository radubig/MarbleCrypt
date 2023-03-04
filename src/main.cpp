#include <iostream>
#include "../include/Inventory.h"

int main()
{
    Inventory inventory;
    inventory.ResetDefault();
    inventory.ShowGeneratorData();
    for(int i = 1; i <= 10; i++)
    {
        if(!inventory.BuyMarble())
            std::cout << "Not enough money to buy another marble!\n";
        else
            std::cout << "Marble added to colection!\n";

        std::cout <<"Balance: " << inventory.GetBalance() << "\n" <<
        "Next marble costs: " << inventory.GetNewMarblePrice() << "\n";
    }
    std::cout << inventory;

    //Simulare colectare yield
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << "Collecting yields:\n";
    inventory.CollectAll();
    std::cout << "Balance after collecting all: " << inventory.GetBalance() << "\n";

    // Utilizare Clear ca sa fie commit-ul stabil
    inventory.Clear();
    return 0;
}
