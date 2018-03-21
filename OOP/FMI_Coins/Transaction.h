#pragma once
#include <time.h>

class Transaction
{
  private:
    long long t_time;   //transaction time
    unsigned int senderId;
    unsigned int receiverId;
    double fmiCoins;

  public:
    Transaction();
    Transaction(const long long,
                const unsigned int,
                const unsigned int,
                const double);

    Transaction &operator=(const Transaction &);

  public:
    const unsigned int &getSenderID() const;
    const unsigned int &getReceiverID() const;
    const long long &getTime() const;
    const double &getCoins() const;
};