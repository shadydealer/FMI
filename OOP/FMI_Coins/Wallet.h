#pragma once
#include "string.h" //strcpy()

#define DEFAULT_NAME_LENGTH 256

class Wallet
{
private:
  char owner[DEFAULT_NAME_LENGTH];
  unsigned int id;
  double fiat_money;

public:
  Wallet();
  Wallet(const char [DEFAULT_NAME_LENGTH],
         const double,
         const unsigned int);

  Wallet &operator=(const Wallet &);
public:
  void setMoney(const double);
public:
  const char *getOwner() const;
  const unsigned int& getID() const;
  const double& getMoney() const;

};