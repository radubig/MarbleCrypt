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
    Marble(std::string, double);
    Marble(const Marble&);
    Marble& operator= (const Marble&);
    ~Marble() = default;
    friend std::ostream& operator<< (std::ostream&, const Marble&);
    double GetYield();

private:
    std::string m_name;
    TP m_timepoint_gen;
    TP m_timepoint_last_yield;
    double m_daily_yield;

    constexpr double YieldPerMinute() const;
};

#endif //MARBLECRYPT_MARBLE_H
