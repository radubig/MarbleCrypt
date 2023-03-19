#include <GameApp.h>
#include <iostream>

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
    m_inv.LoadTextures("data/textures.txt");
    m_inv.LoadMarbleData("data/marbles.txt");
    m_inv.SetDefault();

    //Testing to make sure i don't do stupid alocations
    //m_inv.Reserve(10);
    for(int i=1; i<=10; i++)
        m_inv.BuyMarble();

    // Main rendering loop
    while(m_window.isOpen())
    {
        sf::Event e{};
        while(m_window.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    break;
            }
        }
        m_window.clear();

        // Render code here
        float renderX = 0, renderY = 0;
        for(const Marble& marble : m_inv.GetMarbles())
        {
            sf::RectangleShape sp;
            sp.setTexture(marble.GetTexturePtr());
            sp.setSize({200, 200});
            sp.setPosition(renderX, renderY);
            m_window.draw(sp);
            if(renderX + 400 > float(this->m_width))
                renderY += 200, renderX = 0;
            else
                renderX += 200;
        }

        m_window.display();
    }
}
