#include <stdio.h>

#include "DynamicArray.h"
#include "Wallet.h"
#include "CommandHandler.h"

#define WALLET_FILE_NAME "logs/wallets.bin"
#define TRANSACTION_FILE_NAME "logs/transactions.bin"
#define BUY_FILE_NAME "logs/buy_orders.bin"
#define SELL_FILE_NAME "logs/sell_orders.bin"
#define DEFAULT_INPUT_LEN 1024

int main()
{
    try
    {
        CommandHandler *instance = CommandHandler::getInstance();

        instance->updateWallets(WALLET_FILE_NAME);
        instance->updateTransactions(TRANSACTION_FILE_NAME);
        instance->updateBuyOrders(BUY_FILE_NAME);
        instance->updateSellOrders(SELL_FILE_NAME);

        double currency = 0;
        unsigned int id = 0;
        
        char input[DEFAULT_INPUT_LEN] = {};
        scanf(" %s", input);
        //printf("%s\n", input);
        while (strcmp(input, "quit") != 0)
        {

            if (strcmp(input, "add-wallet") == 0)
            {
                scanf(" %lf", &currency);
                scanf(" %s", input);
                instance->addWallet(currency, input);
            }
            else if (strcmp(input, "make-order") == 0)
            {
                scanf(" %s", input);
                scanf(" %lf", &currency);
                scanf(" %d", &id);

                if (strcmp(input, "BUY") == 0)
                {
                    if(!instance->makeOrder(BUY, id, currency))
                        printf("No such wallet exists.\n");
                }
                else if (strcmp(input, "SELL") == 0)
                {
                    if(!instance->makeOrder(SELL,id,currency))
                        printf("No such wallet exists.\n");
                }
            }
            else if(strcmp(input, "wallet-info") == 0)
            {
                scanf(" %d", &id);
                instance->walletInfo(id);
            }
            //instance->printTransactions();
            //instance->addWallet(250.0, "Ivan");
            //instance->makeOrder(SELL,2, 0.20);
            //instance->printWallets();
            //instance->printTransactions();
            scanf(" %s", input);
        }
        instance->logWallets(WALLET_FILE_NAME);
        instance->logTransacitons(TRANSACTION_FILE_NAME);
        instance->logBuyOrders(BUY_FILE_NAME);
        instance->logSellOrders(SELL_FILE_NAME);
    }
    catch (std::bad_alloc())
    {
        printf("Couldn't allocate any more memory.");
    }
    catch (std::out_of_range &oor)
    {
        printf("%s", oor.what());
    }
    return 0;
}
