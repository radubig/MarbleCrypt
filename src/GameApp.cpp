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

    // Load m_font (Mandatory)
    if(!m_font.loadFromFile(fontFilePath))
        throw FontLoadException(fontFilePath);

    // Load Shop Texture (Mandatory)
    if(!m_shop_tx.loadFromFile(shopTextureFilePath))
        throw TextureLoadException(shopTextureFilePath);

    // Load inventory data
    m_inv.LoadTextures("data/textures.txt");
    m_inv.LoadMarbleData("data/marbles.txt");
    m_inv.SetDefault();
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

void GameApp::InitWindow()
{
    // create window
    m_window.create(sf::VideoMode({m_width, m_height}), m_title, sf::Style::Default);
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(m_framerate_limit);
}

void GameApp::Run()
{
    // Main rendering loop
    while(m_window.isOpen())
    {
        // Render code here
        m_window.clear(sf::Color(80, 80, 80));

        std::vector<std::shared_ptr<DrawableEntity>> renderItems;
        // insert shop into renderItems
        renderItems.push_back(std::make_shared<ShopEntity>(&m_shop_tx, m_font, m_inv));
        // insert action into renderItems
        renderItems.push_back(std::make_shared<ActionEntity>(m_inv, m_selected_marbles, m_font));
        // insert all marbles into renderItmes
        for(uint32_t i = 0; i < m_inv.GetMarblesSize(); i++)
        {
            renderItems.push_back(std::make_shared<MarbleEntity>(m_inv, i, m_font));
            if(m_selected_marbles.contains(i))
                (*(renderItems.rbegin()))->SetOutlineColor(sf::Color::Red);
        }

        float renderX = 0, renderY = DrawableEntity::GetOffsetY();
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
                auto point = m_window.mapPixelToCoords({0, 0});
                sf::FloatRect visibleArea(point.x, point.y, float(e.size.width), float(e.size.height));
                m_window.setView(sf::View(visibleArea));
                m_width = e.size.width;
                m_height = e.size.height;
            }
            else if(e.type == sf::Event::MouseButtonPressed)
            {
                // Left Click events
                if(e.mouseButton.button == sf::Mouse::Left)
                {
                    for(auto& i : renderItems)
                        if(i->isHovered(pos.x, pos.y))
                            i->OnLeftClick();
                }
                // Right click events
                else if(e.mouseButton.button == sf::Mouse::Right)
                {
                    for(auto& i : renderItems) if(i->isHovered(pos.x, pos.y))
                    {
                        auto marble_ptr = std::dynamic_pointer_cast<MarbleEntity>(i);
                        if(marble_ptr)
                        {
                            uint32_t index = marble_ptr->GetMarbleIndex();
                            if(m_selected_marbles.contains(index))
                                m_selected_marbles.erase(index);
                            else
                                m_selected_marbles.insert(index);
                        }
                    }
                }
            }
            else if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::A)
                {
                    m_inv.AddCoins(100);
                }
                else if(e.key.code == sf::Keyboard::Key::G)
                {
                    m_inv.GenerateEachRarity();
                }
            }
            else if(e.type == sf::Event::MouseWheelScrolled)
            {
                m_scroll -= e.mouseWheelScroll.delta * 80;
                if(m_scroll < 0)
                    m_scroll = 0;
                else
                {
                    view.move(0, -e.mouseWheelScroll.delta * 80);
                    m_window.setView(view);
                }
            }
        }
    }
}
