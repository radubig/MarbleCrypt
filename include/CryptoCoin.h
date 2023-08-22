#ifndef MARBLECRYPT_CRYPTOCOIN_H
#define MARBLECRYPT_CRYPTOCOIN_H

#include <ostream>

class CryptoCoin
{
public:
    static const long double s_initial_ammount;

    explicit CryptoCoin(long double balance = s_initial_ammount);
    CryptoCoin(const CryptoCoin& other);
    CryptoCoin& operator= (const CryptoCoin& other);
    ~CryptoCoin();
    friend std::ostream& operator<< (std::ostream& os, const CryptoCoin& wallet);

    bool Pay(long double ammount);
    void Add(long double ammount) noexcept;
    long double Balance() const;

private:
    long double m_balance;
};

#endif //MARBLECRYPT_CRYPTOCOIN_H
