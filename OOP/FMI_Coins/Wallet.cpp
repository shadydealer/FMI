#include "Wallet.h"

unsigned int Wallet::id = 0;

Wallet::Wallet() : owner(), fiat_money()
{
    ++id;
}

Wallet::Wallet(const double rhs_money,
               const char rhs_owner[256])
               :Wallet()
{
    strcpy(owner, rhs_owner);
    fiat_money = rhs_money;
}

Wallet& Wallet::operator=(const Wallet & rhs)
{
    if(this != &rhs)
    {
        strcpy(owner, rhs.owner);
        fiat_money = rhs.fiat_money;
    }
    return * this;
}

const char * Wallet::get_owner() const
{
    return owner;
}

const unsigned int Wallet::get_id() const
{
    return id;
}

const double Wallet::get_money() const
{
    return fiat_money;
}