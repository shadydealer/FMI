#include "CommandHandler.h"

CommandHandler CommandHandler::instance;

CommandHandler::CommandHandler() : curr_id(1),
                                   wallets(),
                                   transactions(),
                                   sell_orders(),
                                   buy_orders()
{
}

CommandHandler *CommandHandler::getInstance()
{
    return &instance;
}

void CommandHandler::printWallets() const
{
    unsigned int wallets_count = instance.wallets.getSize();

    for (unsigned int i = 0; i < wallets_count; ++i)
    {
        printf("id: %u, balance: %lf, name: %s \n",
               instance.wallets[i].getID(),
               instance.wallets[i].getMoney(),
               instance.wallets[i].getOwner());
    }
}

void CommandHandler::printTransactions() const
{
    unsigned int transactions_count = instance.transactions.getSize();
    //printf("%u", transactions_count);

    for (unsigned int i = 0; i < transactions_count; ++i)
    {
        printf("sender: %u, receiver: %u, fmiCoins: %lf, time: %llu\n",
               instance.transactions[i].getSenderID(),
               instance.transactions[i].getReceiverID(),
               instance.transactions[i].getCoins(),
               instance.transactions[i].getTime());
    }
}

void CommandHandler::_addWallet(const double balance,
                                const char owner[256])
{
    Wallet temp_w(owner, balance, curr_id++);
    instance.wallets.pushBack(temp_w);
}

unsigned int number_len(long long number)
{
    unsigned int len = 1;
    while (number > 10)
    {
        number /= 10;
        ++len;
    }

    return len;
}

char *CommandHandler::_genOrderLogName(unsigned int id)
{
    char *log_name = new char[(sizeof(unsigned int) * 8 + //to store the id
                               sizeof(long long) * 8 +    //to store the time
                               6)];                       //to store _ and .txt and the \0 char.

    unsigned int counter = 0;

    unsigned int len = number_len(id);
    unsigned long long ten_pow = 1;

    for (unsigned int i = 0; i < len - 1; ++i)
        ten_pow *= 10;

    for (unsigned int i = 0; i < len; ++i)
    {
        log_name[counter++] = static_cast<char>((id / ten_pow) % 10) + '0';
        ten_pow /= 10;
    }

    log_name[counter++] = '_';

    long long curr_time = time(0);
    len = number_len(curr_time);
    ten_pow = 1;

    for (unsigned int i = 0; i < len - 1; ++i)
        ten_pow *= 10;

    for (unsigned int i = 0; i < len; ++i)
    {
        log_name[counter++] = static_cast<char>((curr_time / ten_pow) % 10) + '0';
        ten_pow /= 10;
    }
    log_name += counter;
    strcpy(log_name, ".txt");
    log_name[4] = 0;
    log_name -= counter;

    return log_name;
}

unsigned int CommandHandler::_buy(const unsigned int wallet_id,
                                  double coins)
{
    unsigned int orders_satisfied = 0;

    if (instance.wallets[wallet_id-1].getMoney() / 375.0 >= coins)
    {
        instance.wallets[wallet_id-1].setMoney(instance.wallets[wallet_id-1].getMoney() - coins*375.0);

        unsigned int sell_order_len = sell_orders.getSize();

        Order *temp_order = NULL;
        double recieving_amount = 0; //amount to be reciever by each
                                     //SELL order that we've satisfied fully/partially.

        while (sell_order_len && coins > std::numeric_limits<double>::epsilon())
        {
            if (coins - sell_orders[0].getCoins() > std::numeric_limits<double>::epsilon())
            {
                coins -= recieving_amount = sell_orders[0].getCoins();
            }
            else
            {
                recieving_amount = coins;
                if (sell_orders[0].getCoins() - coins > std::numeric_limits<double>::epsilon())
                {
                    coins = 0;
                    temp_order = new Order(SELL,
                                           sell_orders[0].getWallet(),
                                           sell_orders[0].getCoins() - recieving_amount);
                }
            }

            wallets[sell_orders[0].getWallet()-1]
                .setMoney(wallets[sell_orders[0].getWallet()-1].getMoney()
                          + recieving_amount*375.0);

            makeTransaction(sell_orders[0].getWallet(),
                            wallet_id,
                            recieving_amount);

            //
            // remove the current sell order we've satisfied fully/partially.
            //
            sell_orders.remove(0);
            --sell_order_len;
        }

        //
        //if we've itterated
        //through the whole list of sell_orders
        //we have to put up a buy order for the rest
        //of the coins the client wants to buy.
        //
        if (!temp_order)
        {
            if (coins > std::numeric_limits<double>::epsilon())
            {
                temp_order = new Order(BUY,
                                       wallet_id,
                                       coins);

                buy_orders.pushBack(*temp_order);
            }
        }
        //
        //In case we've bough all the coins we needed
        //and the last order we've bought from
        //still has coins to sell, we have to make a new sell order.
        //
        else
            sell_orders.pushBack(*temp_order);

        delete temp_order;
    }
    else
    {
        printf("Wallet with id: %u "
               "doesn't have enought fiat money "
               "to acquire the selected amount of coins.",
               wallet_id);
    }
    return orders_satisfied;
}

double CommandHandler::calculateCoins(const unsigned int client_id)
{

    unsigned int transactions_len = instance.transactions.getSize();
    double balance = 0;

    for (unsigned int i = 0; i < transactions_len; ++i)
    {
        if (instance.transactions[i].getReceiverID() == client_id)
        {
            balance += instance.transactions[i].getCoins();
        }
        else if (instance.transactions[i].getSenderID() == client_id)
        {
            balance -= instance.transactions[i].getCoins();
        }
    }

    return balance;
}

unsigned int CommandHandler::_sell(const unsigned int wallet_id,
                                   double coins)
{
    unsigned int orders_satisfied = 0;

    if (calculateCoins(instance.wallets[wallet_id-1].getID()) - coins >= std::numeric_limits<double>::epsilon())
    {
        unsigned int buy_orders_len = instance.buy_orders.getSize();
        double recieving_amount = 0;

        Order *temp_order = NULL;

        while (buy_orders_len && coins > std::numeric_limits<double>::epsilon())
        {
            if (coins - buy_orders[0].getCoins() > std::numeric_limits<double>::epsilon())
            {
                coins -= recieving_amount = buy_orders[0].getCoins();
            }
            else
            {
                if (buy_orders[0].getCoins() - coins > std::numeric_limits<double>::epsilon())
                {
                    recieving_amount = coins;
                    coins = 0;
                    temp_order = new Order(BUY,
                                           buy_orders[0].getWallet(),
                                           buy_orders[0].getCoins() - coins);
                }
            }

            instance.wallets[wallet_id-1].setMoney(instance.wallets[wallet_id -1].getMoney() + (recieving_amount*375.0));

            makeTransaction(wallet_id,
                            buy_orders[0].getWallet(),
                            recieving_amount);

            //
            // remove the current buy order we've satisfied fully/partially.
            //
            buy_orders.remove(0);
            --buy_orders_len;
            ++orders_satisfied;
        }

        //
        //if we've itterated
        //through the whole list of buy_orders
        //we have to put up a sell order for the rest
        //of the coins the client wants to sell.
        //
        if (!temp_order)
        {
            if (coins > std::numeric_limits<double>::epsilon())
            {
                temp_order = new Order(SELL,
                                       wallet_id,
                                       coins);

                sell_orders.pushBack(*temp_order);
            }
        }
        //
        //In case we've sold all the coins we wanted to sell
        //and the last order we've sold to
        //still has coins to buy, we have to make a new buy order.
        //
        else
            buy_orders.pushBack(*temp_order);

        delete temp_order;
    }
    else
    {
        printf("Wallet with id: %u "
               "doesn't have enought coins to sell.",
               wallet_id);
    }
    return orders_satisfied;
}

void CommandHandler::addWallet(const double balance,
                               const char owner[256])
{
    _addWallet(balance, owner);
    makeTransaction(std::numeric_limits<unsigned int>::max(), curr_id - 1, balance / 375.0);
}

void CommandHandler::makeTransaction(const unsigned int senderID,
                                     const unsigned int receiverID,
                                     const double fmiCoins)
{
    Transaction temp(senderID, receiverID, fmiCoins, time(0));
    instance.transactions.pushBack(temp);
}

bool CommandHandler::makeOrder(const Type type,
                               const unsigned int wallet_id,
                               const double fmiCoins)
{
    if(wallet_id <= curr_id)
    {
        unsigned int transactions_made = 0;
        if (type == BUY)
            transactions_made = _buy(wallet_id, fmiCoins);
        else if (type == SELL)
            transactions_made = _sell(wallet_id, fmiCoins);

        logOrderTransactions(type, transactions_made, wallet_id);
        return true;
    }

    return false;
}

void CommandHandler::updateWallets(const char *file_name)
{
    std::ifstream wallets_file(file_name, std::ios::binary);

    if (wallets_file.is_open())
    {
        char owner[256] = {};
        double balance = 0;

        wallets_file.peek();
        while (wallets_file.good())
        {
            wallets_file.read(owner, DEFAULT_SIZE);
            wallets_file.read(reinterpret_cast<char *>(&balance), sizeof(balance));
            wallets_file.peek();
            _addWallet(balance, owner);
        }
        wallets_file.close();
    }
}

void CommandHandler::updateTransactions(const char *file_name)
{
    std::ifstream transactions_file(file_name, std::ios::binary);

    if (transactions_file.is_open())
    {
        unsigned int senderID = 0, receiverID = 0;
        double fmiCoins = 0;
        long long tr_time = 0; //transaction_time

        transactions_file.peek();
        while (transactions_file.good())
        {
            transactions_file.read(reinterpret_cast<char *>(&(senderID)), sizeof(senderID));
            transactions_file.read(reinterpret_cast<char *>(&receiverID), sizeof(receiverID));
            transactions_file.read(reinterpret_cast<char *>(&fmiCoins), sizeof(fmiCoins));
            transactions_file.read(reinterpret_cast<char *>(&tr_time), sizeof(tr_time));
            transactions_file.peek();

            instance.transactions.pushBack(Transaction(senderID, receiverID, fmiCoins, tr_time));
        }
        transactions_file.close();
    }
}

void CommandHandler::updateBuyOrders(const char *file_name)
{
    std::ifstream buy_orders_file(file_name);

    unsigned int wallet_id = 0;
    double coins = 0;

    if (buy_orders_file.is_open())
    {
        buy_orders_file.peek();
        while (buy_orders_file.good())
        {
            buy_orders_file.read(reinterpret_cast<char *>(&(wallet_id)),
                                 sizeof(wallet_id));
            buy_orders_file.read(reinterpret_cast<char *>(&(coins)),
                                 sizeof(coins));
            buy_orders_file.peek();

            buy_orders.pushBack(Order(BUY, wallet_id, coins));
        }
        buy_orders_file.close();
    }
}

void CommandHandler::updateSellOrders(const char *file_name)
{
    std::ifstream sell_orders_file(file_name);

    unsigned int wallet_id = 0;
    double coins = 0;

    if (sell_orders_file.is_open())
    {
        sell_orders_file.peek();
        while (sell_orders_file.good())
        {
            sell_orders_file.read(reinterpret_cast<char *>(&(wallet_id)),
                                  sizeof(wallet_id));
            sell_orders_file.read(reinterpret_cast<char *>(&(coins)),
                                  sizeof(coins));
            sell_orders_file.peek();

            sell_orders.pushBack(Order(SELL, wallet_id, coins));
        }
        sell_orders_file.close();
    }
}

void CommandHandler::walletInfo(const unsigned int client_id)
{
    if(client_id <= curr_id)
    {
        printf("Owner: %s Fiat Money: %lf FMI Coins: %lf",
                instance.wallets[client_id-1].getOwner(),
                instance.wallets[client_id-1].getMoney(),
                calculateCoins(client_id));
    }
    else
    {
        printf("No such wallet exists.\n");
    }
}
void CommandHandler::logWallets(const char *file_name) const
{
    std::ofstream out(file_name, std::ios::binary | std::ios::trunc);

    if (out.is_open())
    {
        int size = instance.wallets.getSize();

        for (int w = 0; w < size; ++w)
        {
            if (out.good())
            {
                out.write(instance.wallets[w].getOwner(),
                          DEFAULT_SIZE);
                out.write(reinterpret_cast<const char *>(&(instance.wallets[w].getMoney())),
                          sizeof(instance.wallets[w].getMoney()));
            }
        }
        out.close();
    }
}

void CommandHandler::logTransacitons(const char *file_name) const
{
    std::ofstream out(file_name, std::ios::binary | std::ios::trunc);

    if (out.is_open())
    {
        int size = instance.transactions.getSize();

        for (int w = 0; w < size; ++w)
        {
            if (out.good())
            {
                out.write(reinterpret_cast<const char *>(&(instance.transactions[w].getSenderID())),
                          sizeof(instance.transactions[w].getSenderID()));

                out.write(reinterpret_cast<const char *>(&(instance.transactions[w].getReceiverID())),
                          sizeof(instance.transactions[w].getReceiverID()));

                out.write(reinterpret_cast<const char *>(&(instance.transactions[w].getCoins())),
                          sizeof(instance.transactions[w].getCoins()));

                out.write(reinterpret_cast<const char *>(&(instance.transactions[w].getTime())),
                          sizeof(instance.transactions[w].getTime()));
            }
        }
        out.close();
    }
}

void CommandHandler::logBuyOrders(const char *file_name)
{
    std::ofstream buy_orders_file(file_name, std::ios::binary | std::ios::trunc);
    if (buy_orders_file.is_open())
    {
        unsigned int orders_len = buy_orders.getSize();
        for (unsigned int i = 0; i < orders_len; ++i)
        {
            if (buy_orders_file.good())
            {
                buy_orders_file.write(reinterpret_cast<const char *>(&(buy_orders[i].getWallet())),
                                      sizeof(buy_orders[i].getWallet()));
                buy_orders_file.write(reinterpret_cast<const char *>(&(buy_orders[i].getCoins())),
                                      sizeof(buy_orders[i].getCoins()));
            }
        }

        buy_orders_file.close();
    }
}

void CommandHandler::logSellOrders(const char *file_name)
{
    std::ofstream sell_orders_file(file_name, std::ios::binary);
    if (sell_orders_file.is_open())
    {
        unsigned int orders_len = sell_orders.getSize();
        for (unsigned int i = 0; i < orders_len; ++i)
        {
            if (sell_orders_file.good())
            {
                sell_orders_file.write(reinterpret_cast<const char *>(&(sell_orders[i].getWallet())),
                                       sizeof(sell_orders[i].getWallet()));
                sell_orders_file.write(reinterpret_cast<const char *>(&(sell_orders[i].getCoins())),
                                       sizeof(sell_orders[i].getCoins()));
            }
        }
        sell_orders_file.close();
    }
}

void CommandHandler::logOrderTransactions(const Type type,
                                          const unsigned int transactions_made,
                                          const unsigned int client_id)
{
    char *order_log_name = _genOrderLogName(client_id);

    std::ofstream log_file(order_log_name);

    if (log_file.is_open())
    {
        double amount_transfered = 0; //holds the amount transfered as fmiCoins at first
                                      //but we convert it to fiatMoney after.
        unsigned int transactions_len = instance.transactions.getSize();
        unsigned int i = instance.transactions.getSize() - transactions_made;

        for (; i < transactions_len; ++i)
        {
            if (log_file)
            {
                log_file << wallets[transactions[i].getSenderID()-1].getOwner();
                log_file << ", " << wallets[transactions[i].getReceiverID()-1].getOwner();
                log_file << ", " << instance.transactions[i].getCoins() << '\n';
            }
            amount_transfered += instance.transactions[i].getCoins();
        }

        amount_transfered *= 375.0; //convert from fmiCoins to fiatMoney.

        if (log_file)
        {
            log_file << "Transactions made: " << transactions_made
                     << ", Amount transfered: " << amount_transfered
                     << '\n';
        }
        log_file.close();
    }

    delete[] order_log_name;
}