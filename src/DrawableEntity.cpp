#include "DrawableEntity.h"
#include <iostream>
#include <sstream>
#include <iterator>

float DrawableEntity::s_entity_width = 200.0f;
float DrawableEntity::s_entity_height = 300.0f;
float DrawableEntity::s_entity_image_size = 150.0f;
float DrawableEntity::s_entity_offsetX = 20.0f;
float DrawableEntity::s_entity_offsetY = 20.0f;
unsigned int DrawableEntity::s_character_size = 19;

void DrawableEntity::OnLeftClick() {} // By default, the function does nothing

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

void DrawableEntity::SetOutlineColor(sf::Color color)
{
    m_canvas.setOutlineColor(color);
}

MarbleEntity::MarbleEntity(Inventory& inventory, uint32_t index, const sf::Font& font)
    :m_inv(inventory), m_indexOfMarble(index)
{
    // Set canvas color and size
    m_canvas.setSize({s_entity_width, s_entity_height});
    m_canvas.setFillColor(sf::Color::Transparent);
    m_canvas.setOutlineColor(sf::Color::White);
    m_canvas.setOutlineThickness(2.0f);

    // Set text properties
    m_current_yield.setFont(font);
    m_current_yield.setCharacterSize(s_character_size);
    m_current_yield.setFillColor(sf::Color::White);
    m_name = m_daily_yield = m_current_yield;
    m_current_yield.setString("Current yield: " + std::to_string(m_inv[index].GetYield()));
    m_daily_yield.setString("Daily yield: " + std::to_string(m_inv[index].GetDailyYield()));
    m_name.setString(m_inv[index].GetName());
}

void MarbleEntity::DrawObject(sf::RenderWindow& window, float X, float Y)
{
    float x, y;
    const Marble& m_marble = m_inv[m_indexOfMarble];

    // Render image
    x = (s_entity_width - s_entity_image_size) / 2.0f;
    y = 10.0f; // Hardcoded for now
    sf::RectangleShape imag1, imag2;
    imag1.setSize({s_entity_image_size, s_entity_image_size});
    imag1.setPosition(X + x, Y + y);
    imag2.setSize({s_entity_image_size, s_entity_image_size});
    imag2.setPosition(X + x, Y + y);
    if(m_marble.GetTexturePtr2() == nullptr)
    {
        imag1.setTexture(m_marble.GetTexturePtr());
        window.draw(imag1);
    }
    else
    {
        imag1.setTexture(m_marble.GetTexturePtr());
        imag2.setTexture(m_marble.GetTexturePtr2());
        auto cl2 = imag1.getFillColor();
        cl2.a /= 2;
        imag2.setFillColor(cl2);
        window.draw(imag1);
        window.draw(imag2);
    }

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

void MarbleEntity::OnLeftClick()
{
    m_inv.AddCoins(m_inv[m_indexOfMarble].GetYield());
    m_inv[m_indexOfMarble].CollectYield();
}

uint32_t MarbleEntity::GetMarbleIndex() const
{
    return m_indexOfMarble;
}

ShopEntity::ShopEntity(sf::Texture* texture, const sf::Font& font, Inventory& inv)
    :m_inv(inv)
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
    long double newMarblePrice = inv.GetNewMarblePrice();
    long double balance = inv.GetBalance();
    if(newMarblePrice < 1e9)
        m_cost.setString("Cost: " + std::to_string(uint64_t(newMarblePrice)));
    else
    {
        std::ostringstream ss;
        ss << newMarblePrice;
        m_cost.setString("Cost: " + ss.str());
    }
    if(balance < 1e9)
        m_balance.setString("Balance: " + std::to_string(uint64_t(balance)));
    else
    {
        std::ostringstream ss;
        ss << balance;
        m_balance.setString("Balance: " + ss.str());
    }
}

void ShopEntity::DrawObject(sf::RenderWindow& window, float X, float Y)
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

void ShopEntity::OnLeftClick()
{
    if(!m_inv.BuyMarble())
        std::cout << "Not enough funds!" << std::endl;
}

ActionEntity::ActionEntity(Inventory& inventory, GameApp::SelectedMarbles_t& selectedMarbles, const sf::Font& font)
    :m_inv(inventory), m_selectedMarbles(selectedMarbles)
{
    // Set canvas color and size
    m_canvas.setSize({s_entity_width, s_entity_height});
    m_canvas.setFillColor(sf::Color::Transparent);
    m_canvas.setOutlineColor(sf::Color::White);
    m_canvas.setOutlineThickness(2.0f);

    // Set text properties
    m_action_name.setFont(font);
    m_action_name.setCharacterSize(s_character_size);
    m_action_name.setFillColor(sf::Color::White);
    m_action_value = m_action_name;
}

void ActionEntity::DrawObject(sf::RenderWindow& window, float X, float Y)
{
    float x, y;
    DetermineAction();

    switch(m_action_type)
    {
        case ActionType::Collect:
        {
            m_action_name.setString("Collect all");
            m_action_name.setFillColor(sf::Color::Green);
            x = (s_entity_width - m_action_name.getGlobalBounds().width) / 2.0f;
            y = s_entity_height / 2.0f - m_action_name.getGlobalBounds().height;
            m_action_name.setPosition(X + x, Y + y);
            window.draw(m_action_name);
        } break;

        case ActionType::Burn:
        {
            m_action_name.setString("Burn marble for:");
            m_action_name.setFillColor(sf::Color::Red);
            x = (s_entity_width - m_action_name.getGlobalBounds().width) / 2.0f;
            y = s_entity_height / 2.0f - m_action_name.getGlobalBounds().height;
            m_action_name.setPosition(X + x, Y + y);
            window.draw(m_action_name);

            auto index = *m_selectedMarbles.begin();
            auto value = m_inv.GetBurnValue(index);
            if(value < 1e9)
                m_action_value.setString(std::to_string(uint64_t(value)) + " $MTK");
            else
            {
                std::ostringstream ss;
                ss << value;
                m_action_value.setString(ss.str() + " $MTK");
            }
            x = (s_entity_width - m_action_value.getGlobalBounds().width) / 2.0f;
            y += 35.0f;
            m_action_value.setPosition(X + x, Y + y);
            window.draw(m_action_value);
        } break;

        case ActionType::Fusion:
        {
            // Selected marbles are fusable
            m_action_name.setString("Fuse Marbles!");
            m_action_name.setFillColor(sf::Color::Cyan);
            x = (s_entity_width - m_action_name.getGlobalBounds().width) / 2.0f;
            y = s_entity_height / 2.0f - m_action_name.getGlobalBounds().height;
            m_action_name.setPosition(X + x, Y + y);
            window.draw(m_action_name);
        } break;

        default:
        {
            // Show option to de-select marbles
            m_action_name.setString("De-select all");
            x = (s_entity_width - m_action_name.getGlobalBounds().width) / 2.0f;
            y = s_entity_height / 2.0f - m_action_name.getGlobalBounds().height;
            m_action_name.setPosition(X + x, Y + y);
            window.draw(m_action_name);
        }
    }
}

void ActionEntity::OnLeftClick()
{
    DetermineAction();
    switch(m_action_type)
    {
        case ActionType::Collect:
            m_inv.CollectAll();
            break;

        case ActionType::Burn:
            m_inv.BurnMarble(*m_selectedMarbles.begin());
            m_selectedMarbles.clear();
            break;

        case ActionType::Fusion:
        {
            auto ind1 = *m_selectedMarbles.begin();
            auto ind2 = *std::next(m_selectedMarbles.begin());
            m_inv.FusionMarbles(ind1, ind2);
            m_selectedMarbles.clear();
        }
            break;

        case ActionType::Deselect:
            m_selectedMarbles.clear();
            break;

        default: ;
    }
}

void ActionEntity::DetermineAction()
{
    if(m_selectedMarbles.empty())
        m_action_type = ActionType::Collect;
    else if(m_selectedMarbles.size() == 1)
        m_action_type = ActionType::Burn;
    else if(m_selectedMarbles.size() == 2 &&
            m_inv.IsFusable(*m_selectedMarbles.begin(), *(std::next(m_selectedMarbles.begin()))) )
        m_action_type = ActionType::Fusion;
    else
        m_action_type = ActionType::Deselect;
}
