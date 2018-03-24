#include "Wallet.h"

Wallet::Wallet() : owner(), id(0), fiat_money()
{
    ++id;
}

Wallet::Wallet(const char rhs_owner[DEFAULT_NAME_LENGTH],
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

void Wallet::setMoney(const double rhs_money)
{
    fiat_money = rhs_money;
}
const char *Wallet::getOwner() const
{
    return owner;
}

const unsigned int &Wallet::getID() const
{
    return id;
}

const double &Wallet::getMoney() const
{
    return fiat_money;
}