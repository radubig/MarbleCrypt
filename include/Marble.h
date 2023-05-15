#ifndef MARBLECRYPT_MARBLE_H
#define MARBLECRYPT_MARBLE_H

#include <SFML/Graphics.hpp>
#include <cinttypes>
#include <string>
#include <chrono>
#include <utility>

class Marble
{
    typedef std::chrono::time_point<std::chrono::system_clock> TP;

public:
    Marble(std::string, int64_t, sf::Texture* = nullptr, sf::Texture* = nullptr);
    Marble(const Marble&);
    Marble& operator= (const Marble&);
    Marble(Marble&&) = default;
    Marble& operator= (Marble&&) = default;
    ~Marble();
    friend std::ostream& operator<< (std::ostream&, const Marble&);

    sf::Texture* GetTexturePtr() const;
    sf::Texture* GetTexturePtr2() const;
    int64_t GetYield() const;
    int64_t GetDailyYield() const;
    void CollectYield();
    const std::string& GetName() const;

private:
    std::string m_name;
    sf::Texture* m_texture;
    sf::Texture* m_texture_2;
    TP m_timepoint_gen;
    TP m_timepoint_last_yield;
    int64_t m_daily_yield;
    // Rarity may be added later as specialized classes

    constexpr double YieldPerSec() const;
};

#endif //MARBLECRYPT_MARBLE_H
