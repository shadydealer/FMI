#include "Wallet.h"

Wallet::Wallet() : owner(), id(0), fiat_money()
{
    ++id;
}

Wallet::Wallet(const char rhs_owner[256],
               const double rhs_money,
               const unsigned int rhs_id)
    : owner(),
      id(rhs_id),
      fiat_money(rhs_money)
{
    strcpy(owner, rhs_owner);
    id = rhs_id;
    fiat_money = rhs_money;
}

Wallet &Wallet::operator=(const Wallet &rhs)
{
    if (this != &rhs)
    {
        strcpy(owner, rhs.owner);
        id = rhs.id;
        fiat_money = rhs.fiat_money;
    }
    return *this;
}

const char *Wallet::get_owner() const
{
    return owner;
}

const unsigned int &Wallet::get_id() const
{
    return id;
}

const double &Wallet::get_money() const
{
    return fiat_money;
}