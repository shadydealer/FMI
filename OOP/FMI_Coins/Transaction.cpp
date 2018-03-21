#include "Transaction.h"

Transaction::Transaction(): t_time(time(0)),
                            senderId(0),
                            receiverId(0),
                            fmiCoins(0)
{}

Transaction::Transaction(const long long rhs_time,
                         const unsigned int rhs_sender,
                         const unsigned int rhs_receiver,
                         const double rhs_fiatMoney):
                         t_time(rhs_time),
                         senderId(rhs_sender),
                         receiverId(rhs_receiver),
                         fmiCoins(rhs_fiatMoney/375.0)
{}

Transaction& Transaction::operator=(const Transaction & rhs)
{
    if (this != &rhs)
    {
        t_time = rhs.t_time;
        senderId = rhs.senderId;
        receiverId = rhs.receiverId;
        fmiCoins = rhs.fmiCoins;
    }
    return * this;
}

const unsigned int & Transaction::getSenderID() const
{
    return senderId;
}

const unsigned int & Transaction::getReceiverID() const
{
    return senderId;
}

const double & Transaction::getCoins() const
{
    return fmiCoins;
}

const long long & Transaction::getTime() const
{
    return t_time;
}