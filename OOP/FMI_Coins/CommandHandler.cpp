#include "CommandHandler.h"

CommandHandler CommandHandler::instance;

CommandHandler::CommandHandler() : curr_id(), wallets(), transactions(), orders()
{
}

CommandHandler *CommandHandler::getInstance()
{
    return &instance;
}

void CommandHandler::printWallets() const
{
    unsigned int wallets_count = instance.wallets.get_size();

    for (unsigned int i = 0; i < wallets_count; ++i)
    {
        printf("id: %u, balance: %lf, name: %s \n",
               instance.wallets[i].get_id(),
               instance.wallets[i].get_money(),
               instance.wallets[i].get_owner());
    }
}

void CommandHandler::printTransactions() const
{
    unsigned int transactions_count = instance.transactions.get_size();
    //printf("%u", transactions_count);
    
    for (unsigned int i = 0; i < transactions_count; ++i)
    {
        printf("sender: %u, receiver: %u, fmiCoins: %lf, time: %llu",
                transactions[i].getSenderID(),
                transactions[i].getReceiverID(),
                transactions[i].getCoins(),
                transactions[i].getTime());
    }
}

void CommandHandler::_addWallet(const double balance,
                               const char owner[256])
{
    Wallet temp_w(owner, balance, curr_id++);
    instance.wallets.push_back(temp_w);
}

void CommandHandler::addWallet(const double balance,
                               const char owner[256])
{
    _addWallet(balance, owner);
    makeTransaction(time(0), std::numeric_limits<unsigned int>::max(), curr_id, balance);
}

void CommandHandler::updateWallets(const char *file_name)
{
    std::ifstream in(file_name, std::ios::binary);

    if (in.is_open())
    {
        char owner[256] = {};
        double balance = 0;

        while (in.good())
        {
            in.read(owner, DEFAULT_SIZE);
            in.read(reinterpret_cast<char *>(&balance), sizeof(balance));

            _addWallet(balance, owner);
        }
        in.close();
    }
}

void CommandHandler::logWallets(const char *file_name) const
{
    std::ofstream out(file_name, std::ios::binary);

    if (out.is_open())
    {
        int size = instance.wallets.get_size() - 1;

        for (int w = 0; w < size; ++w)
        {
            if (out.good())
            {
                out.write(instance.wallets[w].get_owner(),
                          DEFAULT_SIZE);
                out.write(reinterpret_cast<const char *>(&(instance.wallets[w].get_money())),
                          sizeof(instance.wallets[w].get_money()));
            }
        }
        out.close();
    }
}

void CommandHandler::makeTransaction(const long long time,
                                     const unsigned int senderID,
                                     const unsigned int receiverID,
                                     const double fmiCoins)
{
    Transaction temp(time, senderID, receiverID, fmiCoins);
    instance.transactions.push_back(temp);
}

void CommandHandler::updateTransactions(const char *file_name)
{
    std::ifstream in(file_name, std::ios::binary);

    if (in.is_open())
    {
        unsigned int senderID = 0, receiverID = 0;
        double fmiCoins = 0;
        long long tr_time = 0;       //transaction_time

        while (in.good())
        {
            in.read(reinterpret_cast<char*>(&(senderID)), sizeof(senderID));
            in.read(reinterpret_cast<char*>(&receiverID), sizeof(receiverID));
            in.read(reinterpret_cast<char*>(&fmiCoins), sizeof(fmiCoins));
            in.read(reinterpret_cast<char*>(&tr_time), sizeof(tr_time));
        }
        in.close();
    }
}

void CommandHandler::logTransacitons(const char *file_name) const
{
    std::ofstream out(file_name, std::ios::binary);

    if (out.is_open())
    {
        int size = instance.transactions.get_size() - 1;

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

void CommandHandler::makeOrder(const Type type,
                               const unsigned int wallet_id,
                               const double fmiCoins)
{
    Wallet * client = NULL;
    unsigned int wallets_count = instance.wallets.get_size();
    for(unsigned int i = 0; i < wallets_count; ++i)
    {
        if (wallets[i].get_id() == wallet_id)
            client = &wallets[i];
    }
}
