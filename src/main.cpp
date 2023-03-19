#include <GameApp.h>
#include <iostream>
#include <Inventory.h>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

[[maybe_unused]] static inline void class_test()
{
    Inventory inventory;
    inventory.LoadTextures("data/textures.txt");
    inventory.LoadMarbleData("data/marbles.txt");
    inventory.SetDefault();
    for(int i = 1; i <= 2; i++)
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

int main()
{
#ifdef __linux__
    XInitThreads();
#endif

    class_test();

    try
    {
        GameApp app;
        app.SetResolution(1280, 720);
        app.SetFramerateLimit(144);
        app.Init();
        app.Run();
    }
    catch(const std::runtime_error& err)
    {
        std::cerr << "[Runtime Error Exception]: " << err.what() << "\n";
    }
    catch(...)
    {
        std::cerr << "An unknown exception has occured!\n";
    }
    return 0;
}
