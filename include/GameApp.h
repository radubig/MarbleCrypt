#ifndef MARBLECRYPT_GAMEAPP_H
#define MARBLECRYPT_GAMEAPP_H

#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include <memory>
#include <stdexcept>

// NOTE: yes, this class *should be* a singleton, will refactor later
class GameApp
{
public:
    explicit GameApp();
    GameApp(const GameApp& other) = delete;
    GameApp(GameApp&& other) = delete;
    ~GameApp();

    void SetResolution(unsigned int width, unsigned int height);
    void SetFramerateLimit(unsigned int value);
    void Init();
    void Run();

private:
    const std::string m_title = "MarbleCrypt";

    static bool s_instance;
    sf::RenderWindow m_window;
    unsigned int m_width = 1280;
    unsigned int m_height = 720;
    unsigned int m_framerate_limit = 144;
    Inventory m_inv;
};

#endif //MARBLECRYPT_GAMEAPP_H
