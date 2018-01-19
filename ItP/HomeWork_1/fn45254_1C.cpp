#include "iostream"
#include "stdlib.h"
#include "string.h"
#include "math.h"

struct Character
{
    double maxHealth;
    double Health;
    int Armor;
    int Damage;
    int Luck;
    int Potions;
    bool isFullBlock;
    bool isBlocking;
};

enum Command
{
    Attack,
    Deffend,
    Information,
    Potion,
    Exit,
    Error,
    AddHealth,
    AddDamage,
    AddArmor,
    AddLuck,
    Yes,
    No
};

Command hash_input(const char *);
Command hash_stats_select(const char * input);

double attack(Character &, Character &);
void execute_command(Command c, Character &, Character &);

int main()
{
    int coinPieces = 0;
    int piecesNeeded = 5;
    int points = 5;

    Character player = {100, 100, 25, 10, 5, 5};
    Character enemy = {50, 50, 5, 5, 0, 0};

    Command c;

    while (player.Health > 0)
    {
        char command[1024];

        std::cout << "[I] - Stats\n"
                  << "[X] - Exit game\n"
                  << "Any other input will Start the game.\n";
        std::cin >> command;
        c = hash_input(command);

        if (c == Exit)
            break;

        if (c == Information)
        {

            std::cout << "Player stats:"
                      << "\n\tHealth: " << player.Health
                      << "\n\tArmor: " << player.Armor
                      << "\n\tDamage: " << player.Damage
                      << "\n\tLuck: " << player.Luck
                      << "\n\tPotions: " << player.Potions;

            std::cout << "\nEnemy stats:"
                      << "\n\tHealth: " << enemy.Health
                      << "\n\tArmor: " << enemy.Armor
                      << "\n\tDamage: " << enemy.Damage
                      << "\n\tLuck: " << enemy.Luck
                      << std::endl;
        }

        else
        {
            std::cout << "The battle has begun!\n";

            while (enemy.Health > 0 && player.Health > 0)
            {
                std::cout << "Players turn!" << std::endl;

                std::cin >> command;
                c = hash_input(command);

                while (c != Attack && c != Deffend && c != Potion)
                {
                    std::cin >> command;
                    c = hash_input(command);
                    execute_command(c, player, enemy);
                }

                execute_command(c, player, enemy);

                enemy.isBlocking = 0;
                enemy.isFullBlock = 0;

                std::cout << "Monsters turn!" << std::endl;
                execute_command((Command)(rand() % 2), enemy, player);

                std::cout << "------\n";
                std::cout << "Enemy Health: " << enemy.Health << std::endl;
                std::cout << "Player Health: " << player.Health << std::endl;
                std::cout << "------\n";

                player.isBlocking = 0;
                player.isFullBlock = 0;
            }

            if (player.Health == 0)
            {
                std::cout << "You have died!\n";
                if (coinPieces >= 5)
                {
                    std::cout << "You have " << coinPieces << "/" << piecesNeeded << " coin Pieces."
                              << "Would you like to pay and continue playing?\n";

                    do
                    {
                        std::cout << "Enter Y or N." << std::endl;
                        std::cin >> command;
                        c = hash_input(command);

                    } while (c != Yes && c != No);

                    if (c == Yes)
                        coinPieces -= 5;
                }
                else
                    break;
            }

            if (enemy.Health == 0)
            {

                ++coinPieces;

                std::cout << "You have " << coinPieces << " out of "<< piecesNeeded <<" coin pieces!\n";
                std::cout << "You have " << points << " points to spend on stats!\n";
                std::cout << "Choose from: \n"
                          << "[H] - health\n"
                          << "[D] - damage\n"
                          << "[A] - armor\n"
                          << "[L] - luck \n";

                for (size_t i = 0; i < points; ++i)
                {
                    std::cin >> command;
                    c = hash_stats_select(command);

                    while (c != AddHealth && c != AddArmor && c != AddDamage && c != AddLuck)
                    {
                        std::cout << "Please input one of the above commands.\n";
                        std::cin >> command;
                        c = hash_stats_select(command);
                    }

                    switch (c)
                    {
                    case AddHealth:
                        ++player.maxHealth;
                        break;
                    case AddDamage:
                        ++player.Damage;
                        break;
                    case AddArmor:
                        ++player.Armor;
                        break;
                    case AddLuck:
                        ++player.Luck;
                        break;
                    default:
                        break;
                    }
                }
                enemy.maxHealth += 2;
                enemy.Health = enemy.maxHealth;
                enemy.Damage += 2;
                enemy.Armor += 2;
                enemy.Luck += 2;
            }
        }
    }

    return 0;
}

Command hash_input(const char *input)
{
    Command c;
    if (!strcmp(input, "[A]"))
        c = Attack;
    else if (!strcmp(input, "[D]"))
        c = Deffend;
    else if (!strcmp(input, "[I]"))
        c = Information;
    else if (!strcmp(input, "[P]"))
        c = Potion;
    else if (!strcmp(input, "[X]"))
        c = Exit;
    else if (!strcmp(input, "Y"))
        c = Yes;
    else if (!strcmp(input, "N"))
        c = No;
    else
        c = Error;
    return c;
};

Command hash_stats_select(const char * input)
{
    Command c;
    if (!strcmp(input, "[H]"))
        c = AddHealth;
    else if (!strcmp(input, "[D]"))
        c = AddDamage;
    else if (!strcmp(input, "[A]"))
        c = AddArmor;
    else if (!strcmp(input, "[L]"))
        c = AddLuck;
    else
        c = Error;
    
    return c;
}

double attack(Character &attacker, Character &reciever)
{
    double damage = attacker.Damage;

    if (!reciever.isFullBlock)
    {
        //Checks if its a crit.
        if ((rand() % 100 + attacker.Luck) >= (attacker.Luck + (100 - attacker.Luck) / 2))
            damage *= 2;

        //calculates the damage reduction due to armor.
        damage -= damage * (((double)reciever.Armor / 10) * 0.05);

        if (reciever.isBlocking)
            damage /= 2;

        damage = floor(damage * 100 + 0.5) / 100;
        if (reciever.Health >= damage)
            reciever.Health -= damage;
        else
            reciever.Health = 0;
    }

    else
        damage = 0;

    return damage;
}

void execute_command(Command c, Character &executor, Character &reciever)
{
    switch (c)
    {
    case Attack:
    {
        double currAttack = 0;
        currAttack = attack(executor, reciever);
        std::cout << "Attacked for: " << currAttack << " damage!\n";
        break;
    }

    case Deffend:
    {
        executor.isBlocking = 1;
        executor.isFullBlock = rand() % 2;

        if (executor.isFullBlock)
            std::cout << "The next attack against this target will deal no dmg!\n";
        else
            std::cout << "The next attack against this target will deal 50\% less dmg!\n";
        break;
    }

    case Potion:
    {
        if (executor.Potions--)
        {
            executor.Health = executor.maxHealth;
            std::cout << "You drank a potion and now you're fully healed!\n";
            std::cout << executor.Potions << " potions left!\n";
        }
        break;
    }
    break;
    default:
    {
        std::cout << "Please enter one of the following commands:\n"
                  << "[A]\n"
                  << "[D]\n"
                  << "[P]\n";
    }
    }
}