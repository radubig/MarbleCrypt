#include "GameApp.h"
#include "DrawableEntity.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>

bool GameApp::s_instance = false;

GameApp::GameApp()
{
    if(s_instance)
        throw std::runtime_error("Multiple instances of GameApp detected!");
    s_instance = true;
}

GameApp::~GameApp()
{
    if(m_window.isOpen())
        m_window.close();
    s_instance = false;
}

void GameApp::SetResolution(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;
}

void GameApp::SetFramerateLimit(unsigned int value)
{
    m_framerate_limit = value;
}

void GameApp::Init()
{
    m_window.create(sf::VideoMode({m_width, m_height}), m_title, sf::Style::Default);
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(m_framerate_limit);
}

void GameApp::Run()
{
    // Code for initializations
    // Load font (Mandatory)
    sf::Font font;
    const std::string fontFilePath = "data/OpenSans-Regular.ttf";
    if(!font.loadFromFile(fontFilePath))
        throw FontLoadException(fontFilePath);

    // Load Shop Texture (Mandatory)
    sf::Texture shop_tx;
    const std::string textureFilePath = "data/shop.png";
    if(!shop_tx.loadFromFile(textureFilePath))
        throw TextureLoadException(textureFilePath);

    m_inv.LoadTextures("data/textures.txt");
    m_inv.LoadMarbleData("data/marbles.txt");
    m_inv.SetDefault();

    // Test de memorie - cumpar 7 bile
    /*for(int i = 0; i < 7; i++)
        m_inv.BuyMarble();*/

    // Main rendering loop
    while(m_window.isOpen())
    {
        // Render code here
        m_window.clear(sf::Color(80, 80, 80));

        float renderX = 0, renderY = DrawableEntity::GetOffsetY(); // will be refactored

        std::vector<std::shared_ptr<DrawableEntity>> renderItems;
        renderItems.push_back(std::make_shared<ShopEntity>(&shop_tx, font, m_inv));
        for(Marble& marble : m_inv.GetMarbles())
            renderItems.push_back(std::make_shared<MarbleEntity>(marble, font));

        for(auto& item : renderItems)
            item->Draw(m_window, renderX, renderY);

        m_window.display();

        // Poll events
        auto view = m_window.getView();
        sf::Vector2f pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
        sf::Vector2f scrollOffset = view.getCenter() - (view.getSize() / 2.0f);
        pos += scrollOffset;
        sf::Event e{};
        while(m_window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                m_window.close();
            }
            else if(e.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, float(e.size.width), float(e.size.height));
                m_window.setView(sf::View(visibleArea));
                m_width = e.size.width;
                m_height = e.size.height;
            }
            else if(e.type == sf::Event::MouseButtonPressed)
            {
                // Handle events based on Drawable Entities
                if(e.mouseButton.button == sf::Mouse::Left)
                {
                    //preluare entitati
                    std::shared_ptr<ShopEntity> shopEntity;
                    std::vector<std::shared_ptr<MarbleEntity>> marbles;
                    for(auto& i : renderItems)
                    {
                        auto shop_ptr = std::dynamic_pointer_cast<ShopEntity>(i);
                        if(shop_ptr) shopEntity = shop_ptr;
                        else
                        {
                            auto marble_ptr = std::dynamic_pointer_cast<MarbleEntity>(i);
                            if(marble_ptr)
                                marbles.push_back(marble_ptr);
                        }
                    }

                    if(shopEntity->isHovered(pos.x, pos.y))
                    {
                        if(!m_inv.BuyMarble())
                            std::cout << "Not enough funds!" << std::endl;
                    }
                    else for(size_t i = 0; i < marbles.size(); i++)
                        if(marbles[i]->isHovered(pos.x, pos.y))
                        {
                            m_inv.AddCoins(m_inv[i].GetYield());
                            m_inv[i].CollectYield();
                        }
                }
            }
            else if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::A)
                {
                    m_inv.AddCoins(100);
                }
                else if(e.key.code == sf::Keyboard::Key::B)
                {
                    m_inv.BuyMarble();
                }
                else if(e.key.code == sf::Keyboard::Key::C)
                {
                    m_inv.CollectAll();
                }
                else if(e.key.code == sf::Keyboard::Key::F)
                {
                    m_inv.FusionMarbles(0, 1);
                }
            }
            else if(e.type == sf::Event::MouseWheelScrolled)
            {
                // TODO: Add scrollbar
                view.move(0, -e.mouseWheelScroll.delta * 80);
                m_window.setView(view);
            }
        }
    }
}
