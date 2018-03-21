#pragma once

enum Type
{
  SELL,
  BUY
};

class Order
{
private:
  Type type;
  unsigned int walletID;
  double fmiCoins;

public:
  Order();
  Order(const Type,
        const unsigned,
        const double);
  Order &operator=(const Order &);

public:
  const Type& getType() const;
  const unsigned int &getWallet() const;
  const double &getCoins() const;
};