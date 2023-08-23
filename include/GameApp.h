#ifndef MARBLECRYPT_GAMEAPP_H
#define MARBLECRYPT_GAMEAPP_H

#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include <memory>
#include <stdexcept>
#include <unordered_set>

class GameApp
{
public:
    GameApp(const GameApp& other) = delete;
    GameApp(GameApp&& other) = delete;
    ~GameApp();

    static GameApp& getInstance();

    void SetResolution(unsigned int width, unsigned int height);
    void SetFramerateLimit(unsigned int value);
    void InitWindow();
    void Run();
    void EnableCheats();

    typedef std::unordered_set<uint32_t> SelectedMarbles_t;

private:
    explicit GameApp();
    const std::string m_title = "MarbleCrypt";
    const std::string fontFilePath = "data/OpenSans-Regular.ttf";
    const std::string shopTextureFilePath = "data/shop.png";

    bool m_cheats_enabled = false;
    sf::RenderWindow m_window;
    unsigned int m_width = 1280;
    unsigned int m_height = 720;
    unsigned int m_framerate_limit = 144;
    float m_scroll = 0.0f;
    Inventory m_inv;

    sf::Font m_font;
    sf::Texture m_shop_tx;
    SelectedMarbles_t m_selected_marbles;
};

#endif //MARBLECRYPT_GAMEAPP_H
