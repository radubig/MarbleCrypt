#ifndef MARBLECRYPT_DRAWABLEENTITY_H
#define MARBLECRYPT_DRAWABLEENTITY_H

#include <SFML/Graphics.hpp>
#include "Inventory.h"

class DrawableEntity
{
public:
    static float GetOffsetY();
    bool isHovered(float x, float y) const;
    void Draw(sf::RenderWindow& window, float& X, float& Y);
    virtual ~DrawableEntity() = default;

protected:
    static float s_entity_width;
    static float s_entity_height;
    static float s_entity_image_size;
    static float s_entity_offsetX;
    static float s_entity_offsetY;
    static unsigned int s_character_size;

    sf::RectangleShape m_canvas;

private:
    virtual void DrawObject(sf::RenderWindow& window, float& X, float& Y) = 0;
    static void UpdateBounds(sf::RenderWindow& window, float& X, float& Y);
};



class MarbleEntity : public DrawableEntity
{
public:
    explicit MarbleEntity(Marble& marble, const sf::Font& font);
private:
    Marble& m_marble;
    //sf::RectangleShape m_image;
    sf::Text m_name;
    sf::Text m_current_yield;
    sf::Text m_daily_yield;

    void DrawObject(sf::RenderWindow& window, float& X, float& Y) override;
};



class ShopEntity : public DrawableEntity
{
public:
    explicit ShopEntity(sf::Texture* texture, const sf::Font& font, const Inventory& inv);

private:
    sf::RectangleShape m_image;
    sf::Text m_balance;
    sf::Text m_cost;

    void DrawObject(sf::RenderWindow& window, float& X, float& Y) override;
};

#endif //MARBLECRYPT_DRAWABLEENTITY_H
