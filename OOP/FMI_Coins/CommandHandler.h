#pragma once
#include <fstream>
#include <iostream>
#include <limits> //std::numeric_limits<unsigned int>::max()
#include <stdlib.h>

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
  DynamicArray<Order> sell_orders;
  DynamicArray<Order> buy_orders;

private:
  CommandHandler();

private:
  void _addWallet(const double,
                  const char[256]);
  char *_genOrderLogName(unsigned int); //generates a name for the order log file.
  unsigned int _buy(const unsigned int,
                    double); //returns the amount of transactions made after making the order.
  unsigned int _sell(const unsigned int,
                     double); //returns the amount of trasactions made after making the order.

public:
  CommandHandler(const CommandHandler &) = delete;
  CommandHandler &operator=(const CommandHandler &) = delete;

public:
  static CommandHandler *getInstance();
  void printWallets() const;
  void printTransactions() const;

public:
  double calculateCoins(const unsigned int);
  void addWallet(const double,
                 const char[256]);
  void makeTransaction(const unsigned int,
                       const unsigned int,
                       const double);
  bool makeOrder(const Type,
                 const unsigned int,
                 const double);

public:
  void updateWallets(const char *);
  void updateTransactions(const char *);
  void updateBuyOrders(const char *);
  void updateSellOrders(const char *);

public:
  void walletInfo(const unsigned int);
  void logWallets(const char *) const;
  void logTransacitons(const char *) const;
  void logBuyOrders(const char *);
  void logSellOrders(const char *);
  void logOrderTransactions(const Type,
                            const unsigned int,
                            const unsigned int);
};