#pragma once
#include "string.h" //strcpy()

class Wallet
{
private:
  char owner[256];
  unsigned int id;
  double fiat_money;

public:
  Wallet();
  Wallet(const char [256],
         const double,
         const unsigned int);

  Wallet &operator=(const Wallet &);

public:
  const char *get_owner() const;
  const unsigned int& get_id() const;
  const double& get_money() const;
};