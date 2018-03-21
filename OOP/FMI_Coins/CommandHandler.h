#pragma once
#include <fstream>
#include <limits> //std::numeric_limits<unsigned int>::max()

#include "DynamicArray.h"
#include "Wallet.h"
#include "Transaction.h"
#include "Order.h"

class CommandHandler
{
private:
  static CommandHandler instance;
  unsigned int curr_id; //holds the next id to be used to create a new wallet.
  DynamicArray<Wallet> wallets;
  DynamicArray<Transaction> transactions;
  DynamicArray<Order> orders;

private:
  CommandHandler();

  private:
  void _addWallet(const double,
                 const char[256]);

public:
  CommandHandler(const CommandHandler &) = delete;
  CommandHandler &operator=(const CommandHandler &) = delete;

public:
  static CommandHandler *getInstance();
  void printWallets() const;
  void printTransactions() const;

public:
  void addWallet(const double,
                 const char[256]);
  void updateWallets(const char *);
  void logWallets(const char *) const;

public:
  void makeTransaction(const long long,
                       const unsigned int,
                       const unsigned int,
                       const double);
  void updateTransactions(const char *);
  void logTransacitons(const char *) const;

public:
  void makeOrder(const Type,
                 const unsigned int,
                 const double);
};