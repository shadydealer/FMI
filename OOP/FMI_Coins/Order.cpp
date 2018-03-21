#include "Order.h"

Order::Order():type(BUY), walletID(0), fmiCoins(0)
{}

Order::Order(const Type rhs_type,
             const unsigned int rhs_ID,
             const double rhs_coins): type(rhs_type),
                                      walletID(rhs_ID),
                                      fmiCoins(rhs_coins)
{}

Order& Order::operator=(const Order & rhs)
{
    if(this != &rhs)
    {
        type = rhs.type;
        walletID = rhs.walletID;
        fmiCoins = rhs.fmiCoins;
    }
    
    return * this;

}

const Type& Order::getType() const
{
    return type;
}

const unsigned int& Order::getWallet() const
{
    return walletID;
}

const double & Order::getCoins() const
{
    return fmiCoins;
}

