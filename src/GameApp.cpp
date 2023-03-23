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
    static const float ENTITY_IMG_SZ = 150.0f;
    static const float ENTITY_HORIZONTAL_OFFSET = 20.0f;
    static const float ENTITY_VERTICAL_OFFSET = 60.0f;

    // Code for initializations
    // Load font (Mandatory)
    sf::Font font;
    if(!font.loadFromFile("data/OpenSans-Regular.ttf"))
        throw std::runtime_error("Font could not be loaded!");

    // Load Shop Texture (Mandatory)
    sf::Texture shop_tx;
    if(!shop_tx.loadFromFile("data/shop.png"))
        throw std::runtime_error("Shop image could not be loaded!");
    sf::RectangleShape shop;
    shop.setTexture(&shop_tx);
    shop.setSize({ENTITY_IMG_SZ, ENTITY_IMG_SZ});

    m_inv.LoadTextures("data/textures.txt");
    m_inv.LoadMarbleData("data/marbles.txt");
    m_inv.SetDefault();

    //Testing to make sure i don't do stupid alocations
    m_inv.Reserve(10);
    /*for(int i=1; i<=10; i++)
        m_inv.BuyMarble();*/

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Main rendering loop
    while(m_window.isOpen())
    {
        // Render code here
        m_window.clear(sf::Color(80, 80, 80));

        float renderX = ENTITY_HORIZONTAL_OFFSET, renderY = ENTITY_HORIZONTAL_OFFSET;
        // Render shop
        shop.setPosition(renderX, renderY);
        m_window.draw(shop);
        text.setString(std::to_string(int(m_inv.GetBalance())) + " | " + std::to_string(int(m_inv.GetNewMarblePrice())));
        text.setPosition(renderX, renderY + ENTITY_IMG_SZ);
        m_window.draw(text);
        if(renderX + 2 * (ENTITY_IMG_SZ + ENTITY_HORIZONTAL_OFFSET) > float(this->m_width))
            renderY += ENTITY_IMG_SZ + ENTITY_VERTICAL_OFFSET, renderX = ENTITY_HORIZONTAL_OFFSET;
        else
            renderX += ENTITY_IMG_SZ + ENTITY_HORIZONTAL_OFFSET;

        // Render Marbles
        for(const Marble& marble : m_inv.GetMarbles())
        {
            sf::RectangleShape sp;
            sp.setTexture(marble.GetTexturePtr());
            sp.setSize({ENTITY_IMG_SZ, ENTITY_IMG_SZ});
            sp.setPosition(renderX, renderY);
            m_window.draw(sp);
            text.setString(std::to_string(marble.GetYield()));
            text.setPosition(renderX, renderY + ENTITY_IMG_SZ);
            m_window.draw(text);
            if(renderX + 2 * (ENTITY_IMG_SZ + ENTITY_HORIZONTAL_OFFSET) > float(this->m_width))
                renderY += ENTITY_IMG_SZ + ENTITY_VERTICAL_OFFSET, renderX = ENTITY_HORIZONTAL_OFFSET;
            else
                renderX += ENTITY_IMG_SZ + ENTITY_HORIZONTAL_OFFSET;
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
                // TODO: Add scrollbar
                auto view = m_window.getView();
                view.move(0, -e.mouseWheelScroll.delta * 80);
                m_window.setView(view);
            }
        }
    }
}
