#ifndef MARBLECRYPT_MARBLE_H
#define MARBLECRYPT_MARBLE_H

#include <cinttypes>
#include <string>
#include <chrono>
#include <utility>

class Marble
{
    typedef std::chrono::time_point<std::chrono::system_clock> TP;

public:
    Marble(std::string, int64_t);
    Marble(const Marble&);
    Marble& operator= (const Marble&);
    ~Marble() = default;
    friend std::ostream& operator<< (std::ostream&, const Marble&);

    int64_t GetYield();

private:
    std::string m_name; // Auto-initialized to ""
    std::string m_texture; // May refactor after adding graphics API
    TP m_timepoint_gen;
    TP m_timepoint_last_yield;
    int64_t m_daily_yield;
    // Rarity may be added later as specialized classes

    constexpr int64_t YieldPer30s() const;
};

#endif //MARBLECRYPT_MARBLE_H
