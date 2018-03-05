#include "string.h" //strcpy()

class Wallet
{
private:
  char owner[256];
  static unsigned int id;
  double fiat_money;

public:
  Wallet();
  Wallet(const double rhs_money,
         const char rhs_owner[256]);
  Wallet &operator=(const Wallet &);

public:
  const char *get_owner() const;
  const unsigned int get_id() const;
  const double get_money() const;
};