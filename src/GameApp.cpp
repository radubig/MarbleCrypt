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
    // A few constants that will be moved into a proper class later
    static const float ENTITY_SIZE = 200.0f;
    static const float ENTITY_OFFSET = 20.0f;
    // Code for initializations
    sf::Texture shop_tx;
    if(!shop_tx.loadFromFile("data/shop.png"))
        throw std::runtime_error("Shop image could not be loaded!");
    sf::RectangleShape shop;
    shop.setTexture(&shop_tx);
    shop.setSize({ENTITY_SIZE, ENTITY_SIZE});

    m_inv.LoadTextures("data/textures.txt");
    m_inv.LoadMarbleData("data/marbles.txt");
    m_inv.SetDefault();

    //Testing to make sure i don't do stupid alocations
    m_inv.Reserve(10);
    /*for(int i=1; i<=10; i++)
        m_inv.BuyMarble();*/

    // Main rendering loop
    while(m_window.isOpen())
    {
        // Render code here
        m_window.clear(sf::Color::Cyan);

        float renderX = ENTITY_OFFSET, renderY = ENTITY_OFFSET;
        shop.setPosition(renderX, renderY);
        m_window.draw(shop);
        if(renderX + 2 * (ENTITY_SIZE + ENTITY_OFFSET) > float(this->m_width))
            renderY += ENTITY_SIZE + ENTITY_OFFSET, renderX = ENTITY_OFFSET;
        else
            renderX += ENTITY_SIZE + ENTITY_OFFSET;

        for(const Marble& marble : m_inv.GetMarbles())
        {
            sf::RectangleShape sp;
            sp.setTexture(marble.GetTexturePtr());
            sp.setSize({ENTITY_SIZE, ENTITY_SIZE});
            sp.setPosition(renderX, renderY);
            m_window.draw(sp);
            if(renderX + 2 * (ENTITY_SIZE + ENTITY_OFFSET) > float(this->m_width))
                renderY += ENTITY_SIZE + ENTITY_OFFSET, renderX = ENTITY_OFFSET;
            else
                renderX += ENTITY_SIZE + ENTITY_OFFSET;
        }

        m_window.display();

        // Poll events
        sf::Vector2i pos = sf::Mouse::getPosition(m_window);
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
                if(e.mouseButton.button == sf::Mouse::Left &&
                   shop.getGlobalBounds().contains(float(pos.x), float(pos.y)))
                {
                    if(!m_inv.BuyMarble())
                        std::cout << "Not enough funds!" << std::endl;
                    else
                        std::cout << "Balance remaining: " << m_inv.GetBalance() << std::endl;
                }
            }
            else if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Key::A)
                {
                    m_inv.AddCoins(100);
                    std::cout << "Balance remaining: " << m_inv.GetBalance() << std::endl;
                }
            }
            else if(e.type == sf::Event::MouseWheelScrolled)
            {
                std::cout << "Mouse scroll\n";
                auto view = m_window.getView();
                view.move(0, float(e.mouseWheelScroll.delta));
                m_window.setView(view);
            }
        }
    }
}
