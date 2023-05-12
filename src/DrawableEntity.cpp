#include "DrawableEntity.h"

float DrawableEntity::s_entity_width = 200.0f;
float DrawableEntity::s_entity_height = 300.0f;
float DrawableEntity::s_entity_image_size = 150.0f;
float DrawableEntity::s_entity_offsetX = 20.0f;
float DrawableEntity::s_entity_offsetY = 20.0f;
unsigned int DrawableEntity::s_character_size = 20;

float DrawableEntity::GetOffsetY()
{
    return s_entity_offsetY;
}

bool DrawableEntity::isHovered(float x, float y) const
{
    return m_canvas.getGlobalBounds().contains(x, y);
}

void DrawableEntity::Draw(sf::RenderWindow& window, float& X, float& Y)
{
    // Add X offset to create some space
    X += s_entity_offsetX;

    // Render canvas
    m_canvas.setPosition(X, Y);
    window.draw(m_canvas);

    // Custom draw behaviour
    DrawObject(window, X, Y);

    // Update Bounds
    UpdateBounds(window, X, Y);
}

void DrawableEntity::UpdateBounds(sf::RenderWindow& window, float& X, float& Y)
{
    const float w_width = static_cast<float>(window.getSize().x);
    X += s_entity_width;
    if(X + s_entity_width + s_entity_offsetX > w_width)
        Y += s_entity_height + s_entity_offsetY, X = 0;
}

MarbleEntity::MarbleEntity(Marble& marble, const sf::Font& font)
    :m_marble(marble)
{
    // Set canvas color and size
    m_canvas.setSize({s_entity_width, s_entity_height});
    m_canvas.setFillColor(sf::Color::Transparent);
    m_canvas.setOutlineColor(sf::Color::White);
    m_canvas.setOutlineThickness(2.0f);

    // Set image properties
    m_image.setTexture(m_marble.GetTexturePtr());
    m_image.setSize({s_entity_image_size, s_entity_image_size});

    // Set text properties
    m_current_yield.setFont(font);
    m_current_yield.setCharacterSize(s_character_size);
    m_current_yield.setFillColor(sf::Color::White);
    m_name = m_daily_yield = m_current_yield;
    m_current_yield.setString("Current yield: " + std::to_string(m_marble.GetYield()));
    m_daily_yield.setString("Daily yield: " + std::to_string(m_marble.GetDailyYield()));
    m_name.setString(m_marble.GetName());
}

void MarbleEntity::DrawObject(sf::RenderWindow& window, float& X, float& Y)
{
    float x, y;
    // Render image
    x = (s_entity_width - s_entity_image_size) / 2.0f;
    y = 10.0f; // Hardcoded for now
    m_image.setPosition(X + x, Y + y);
    window.draw(m_image);

    // Render text
    x = 5.0f;
    y = s_entity_image_size + 25.0f;
    m_name.setPosition(X + x, Y + y);
    window.draw(m_name);
    y += 35.0f;
    m_current_yield.setPosition(X + x, Y + y);
    window.draw(m_current_yield);
    y += 35.0f;
    m_daily_yield.setPosition(X + x, Y + y);
    window.draw(m_daily_yield);
}

ShopEntity::ShopEntity(sf::Texture* texture, const sf::Font& font, const Inventory& inv)
{
    // Set canvas color and size
    m_canvas.setSize({s_entity_width, s_entity_height});
    m_canvas.setFillColor(sf::Color::Transparent);
    m_canvas.setOutlineColor(sf::Color::White);
    m_canvas.setOutlineThickness(2.0f);

    // Set image properties
    m_image.setTexture(texture);
    m_image.setSize({s_entity_image_size, s_entity_image_size});

    // Set text properties
    m_cost.setFont(font);
    m_cost.setCharacterSize(s_character_size);
    m_cost.setFillColor(sf::Color::White);
    m_balance = m_cost;
    m_cost.setString("Cost: " + std::to_string(uint64_t(inv.GetNewMarblePrice())));
    m_balance.setString("Balance: " + std::to_string(uint64_t(inv.GetBalance())));
}

void ShopEntity::DrawObject(sf::RenderWindow& window, float& X, float& Y)
{
    float x, y;

    // Render image
    x = (s_entity_width - s_entity_image_size) / 2.0f;
    y = 10.0f; // Hardcoded for now
    m_image.setPosition(X + x, Y + y);
    window.draw(m_image);

    // Render text
    x = 5.0f;
    y = s_entity_image_size + 25.0f;
    m_cost.setPosition(X + x, Y + y);
    window.draw(m_cost);
    y += 35.0f;
    m_balance.setPosition(X + x, Y + y);
    window.draw(m_balance);
}

SpecialMarble::SpecialMarble(Marble& marble, const sf::Font& font)
    :m_marble(marble)
{
    // Set canvas color and size
    m_canvas.setSize({s_entity_width, s_entity_height});
    m_canvas.setFillColor(sf::Color::Transparent);
    m_canvas.setOutlineColor(sf::Color::Red);
    m_canvas.setOutlineThickness(2.0f);

    // Set image properties
    m_image.setTexture(m_marble.GetTexturePtr());
    m_image.setSize({s_entity_image_size, s_entity_image_size});

    // Set text properties
    m_text.setFont(font);
    m_text.setCharacterSize(s_character_size + 4);
    m_text.setString("Special marble");
    m_text.setFillColor(sf::Color::Red);
}

void SpecialMarble::DrawObject(sf::RenderWindow& window, float& X, float& Y)
{
    float x, y;
    // Render image
    x = (s_entity_width - s_entity_image_size) / 2.0f;
    y = 10.0f; // Hardcoded for now
    m_image.setPosition(X + x, Y + y);
    window.draw(m_image);

    // Render text
    x = 5.0f;
    y = s_entity_image_size + 25.0f;
    m_text.setPosition(X + x, Y + y);
    window.draw(m_text);
}
