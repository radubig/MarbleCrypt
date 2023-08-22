#ifndef MARBLECRYPT_MARBLE_H
#define MARBLECRYPT_MARBLE_H

#include <SFML/Graphics.hpp>
#include <cinttypes>
#include <string>
#include <chrono>
#include <utility>
#include "DataLoader.h"

class Marble
{
    typedef std::chrono::time_point<std::chrono::system_clock> TP;

public:
    Marble(std::string, int64_t, sf::Texture*, sf::Texture*, MarbleRarity);
    Marble(std::string, int64_t, sf::Texture*, sf::Texture*, MarbleRarity, size_t);
    template<MarbleRarity T> explicit Marble(MarbleLoader::MarbleData<T> data);
    Marble(const Marble&) = delete;
    Marble& operator= (const Marble&) = delete;
    Marble(Marble&&) = default;
    Marble& operator= (Marble&&) = default;
    ~Marble();
    friend std::ostream& operator<< (std::ostream&, const Marble&);

    sf::Texture* GetTexturePtr() const;
    sf::Texture* GetTexturePtr2() const;
    int64_t GetYield() const;
    int64_t GetDailyYield() const;
    MarbleRarity GetRarity() const;
    void CollectYield();
    const std::string& GetName() const;

private:
    std::string m_name;
    sf::Texture* m_texture;
    sf::Texture* m_texture_2;
    MarbleRarity m_rarity;
    TP m_timepoint_last_yield;
    int64_t m_daily_yield;

    constexpr double YieldPerSec() const;
};

#endif //MARBLECRYPT_MARBLE_H
