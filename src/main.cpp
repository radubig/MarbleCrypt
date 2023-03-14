#include <SFML/Graphics.hpp>
#include <iostream>
#include <Inventory.h>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

static inline void class_test()
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
}

static inline void graphics_test()
{
    sf::RenderWindow window;
    // NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:30
    window.create(sf::VideoMode({1280, 720}), "MarbleCrypt", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    while(window.isOpen())
    {
        sf::Event e{};
        while(window.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.display();
    }
}

int main()
{
#ifdef __linux__
    XInitThreads();
#endif

    class_test();
    graphics_test();
    return 0;
}
