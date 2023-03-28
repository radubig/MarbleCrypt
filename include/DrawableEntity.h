#ifndef MARBLECRYPT_DRAWABLEENTITY_H
#define MARBLECRYPT_DRAWABLEENTITY_H

#include <SFML/Graphics.hpp>
#include "Inventory.h"

class DrawableEntity : protected sf::RectangleShape
{
public:
    // TODO: Generate getters and setters
    static float s_entity_width;
    static float s_entity_height;
    static float s_entity_image_size;
    static float s_entity_offsetX;
    static float s_entity_offsetY;
    static unsigned int s_character_size;

    virtual void Draw(sf::RenderWindow& window, float& X, float& Y) = 0;
    virtual bool isHovered(float x, float y) const;
    // TODO: Make a function that automaticly updates render coords
    //  * Maybe redefine Draw to be non-virtual and call another custom, protected virtual Draw function?
};

class MarbleEntity : public DrawableEntity
{
public:
    explicit MarbleEntity(Marble& marble, const sf::Font& font);
    void Draw(sf::RenderWindow& window, float& X, float& Y) override;
private:
    Marble& m_marble;
    sf::RectangleShape m_image;
    sf::Text m_name;
    sf::Text m_current_yield;
    sf::Text m_daily_yield;
};

class ShopEntity : public DrawableEntity
{
public:
    explicit ShopEntity(sf::Texture* texture, const sf::Font& font, const Inventory& inv);
    void Draw(sf::RenderWindow& window, float& X, float& Y) override;

private:
    sf::RectangleShape m_image;
    sf::Text m_balance;
    sf::Text m_cost;
};

#endif //MARBLECRYPT_DRAWABLEENTITY_H
