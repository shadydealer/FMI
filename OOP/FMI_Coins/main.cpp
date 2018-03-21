#include <stdio.h>

#include "DynamicArray.h"
#include "Wallet.h"
#include "CommandHandler.h"

#define WALLET_FILE_NAME "logs/wallets.bin"
#define TRANSACTION_FILE_NAME "logs/transactions.bin"

int main()
{
    try
    {
        CommandHandler *instance = CommandHandler::getInstance();
        instance->updateWallets(WALLET_FILE_NAME);
        instance->updateTransactions(TRANSACTION_FILE_NAME);
        
        instance->printWallets();
        instance->printTransactions();

        instance->logWallets(WALLET_FILE_NAME);
        instance->logTransacitons(TRANSACTION_FILE_NAME);
        
    }
    catch (std::bad_alloc())
    {
        printf("Couldn't allocate any more memory.");
    }
    catch (std::out_of_range& oor)
    {
        printf("%s", oor.what());
    }
    return 0;
}

