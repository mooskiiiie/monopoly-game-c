#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Instantiate functions
int roll_dice();
void menu();
int change_player(int);
int check_position(int num[2][3], int, int);
int generate_random(int, int);

int roll_dice() {
    int roll = rand() % 6 + 1;
    return roll;
}

void menu() {
    printf("\nWelcome to Property...Property!\n");
    printf("GAME GAME GAME\n\n");
    printf("\t**************\n\n");
}

int change_player(int current_player){
    if(current_player == 1) {
        current_player = 2;
    }
    else {
        current_player = 1;
    }
    return current_player;
}

int generate_random(int l, int r) { //this will generate random number in range l and r
   int rand_num = (rand() % (r - l + 1)) + l;
   return rand_num;
}


int main() {

    // Instantiate variables
    char is_new_game;
    srand((unsigned) time(0));

    do {
        menu();
        printf("\n\n");
        bool is_end = false;
        bool is_jail = false;
        int current_player = 1;
        int players[2][2] = {{0, 200}, {0, 200}};
        int properties = 0;
        int position = 0;
        // int turns = 5;
        int r;
        char is_buy;
        int jail;

        while (is_end != true) {
            
            printf("\n\nProperties owned: %d\n\n", properties);
            
            char is_roll = 'N';

            position = players[current_player - 1][0];
            printf("\nPlayer %d's turn\n\n", current_player);
            printf("Current Position: %d\n\n", position);

            // Roll Dice
            printf("Roll Dice? (Y/N) ");
            scanf(" %c", &is_roll);

            if ((is_roll == 'Y' || is_roll == 'y') && jail != current_player){
                
                // Basically resets jail, so that no one is in it
                jail = 3;

                int roll = roll_dice();
                printf("Roll: %d\n\n", roll);

                position = (position + roll) % 7;

                players[current_player - 1][0] = position;

                printf("Updated position: %d\n\n", position);

                switch (position)
                {
                // Player lands on GO and gets 200
                case 0:
                    players[current_player - 1][1] = players[current_player - 1][1] + 200;
                    printf("Pass Go! New Balance: %d\n", players[current_player - 1][1]);
                    break;
                // Player lands on Tree House
                case 1:
                    // players[current_player - 1][1] = players[current_player - 1][1] + 200;
                    // printf("You passed by Go! New Balance: %d\n", players[current_player - 1][1]);
                    r = properties / pow(10,0);
                    r = r % 10;
                    switch (r)
                    {
                        case 0:
                            printf(" You landed on the Tree House. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                           
                           
                            // TODO: Not enough cash! player can sell properties 
                            // TODO: Bankrupt
                            // TODO: passes by GO

                            if (is_buy == 'Y') {
                                if (current_player == 1) {
                                    if (players[current_player - 1][1] >= 20) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (1 % 7 * 20);
                                        properties += 1;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 20) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (1 % 7 * 20);
                                        properties += 2;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                    
                                }
                            }
                            break;
                        case 1:
                            r = properties / pow(10,0);
                            r = r % 10;
                            if (current_player == 1) {
                                printf(" You landed on the Tree House. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 2;
                                }
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                printf("You have already renovated this property.");
                            } else {
                                r = properties / pow(10,0);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n", 9);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 9) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[0][1] = players[0][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n", 4);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[0][1] = players[0][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Tree House. Do you want to renovate this property? (Y or N");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y'){
                                    players[current_player -1][1] = players[current_player -1][1] - 50;
                                    properties += 2;
                                }
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                printf("You have already renovated this property.");
                            } else {
                                r = properties / pow(10,0);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Tree House owned by Player 2. You have to pay $%d!\n", 9);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[1][1] = players[1][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Tree House owned by Player 2. You have to pay $%d!\n", 4);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[1][1] = players[1][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                // Player lands on Electric Company
                case 2:
                    // players[current_player - 1][1] = players[current_player - 1][1] + 200;
                    // printf("You passed by Go! New Balance: %d\n", players[current_player - 1][1]);
                    r = properties / pow(10,1);
                    r = r % 10;
                    switch (r) 
                    {
                        case 0:
                            printf(" You landed on the Electric Company. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                if (current_player == 1) {
                                    if (players[current_player - 1][1] >= 150) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 150;
                                        properties += 10;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 150) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 150;
                                        properties += 20;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                }
                            }
                            break;
                        case 1:
                            r = properties / pow(10,1);
                            r = r % 10;
                            if (current_player == 2) {
                                printf("\nYou landed on the Electrical Company owned by Player 1. You have to pay $%d!\n", (8 * roll));
                                players[current_player - 1][1] = players[current_player - 1][1] - (8 * roll);
                                players[0][1] = players[0][1] + (8 * roll);
                                printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if ((current_player == 1) && (r == 1)) {
                                    printf("You already own this property.");
                                }
                                printf("\n");
                            break;
                        case 2:
                            r = properties / pow(10,1);
                            r = r % 10;
                            if (current_player == 1) {
                                printf("\nYou landed on the Electrical Company owned by Player 2. You have to pay $%d!\n", (8 * roll));
                                players[current_player - 1][1] = players[current_player - 1][1] - (8 * roll);
                                players[1][1] = players[1][1] + (8 * roll);
                                printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if ((current_player == 2) && (r == 2)) {
                                    printf("You already own this property.");
                                }
                                printf("\n");
                            break;
                    }
                    break;
                // Player lands on Beach House
                case 3:
                    r = properties / pow(10,2);
                    r = r % 10;
                    switch (r)
                    {
                        // The bank owns the beach house
                        case 0:
                            printf(" You landed on the Beach House. Do you want to buy this property? (Y or N)");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                if (current_player == 1) { // player one buys the property 
                                    if (players[current_player - 1][1] >= 60) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (3 % 7 * 20);
                                        properties += 100; // adds 100 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 60) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (3 % 7 * 20);
                                        properties += 200;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                }
                            }
                            break;
                        // Player one already owns the beach house
                        case 1: 
                            if (current_player == 1) {
                                printf(" You landed on the Beach House. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 200; // adds 200 to make it 3
                                }
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,2);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Beach House owned by Player 1. You have to pay $%d!\n", 25);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 25;
                                    players[0][1] = players[0][1] + 25;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Beach House owned by Player 1. You have to pay $%d!\n", 12);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 12;
                                    players[0][1] = players[0][1] + 12;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the beach house
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Beach House. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 200;
                                }
                                printf("\n");
                            }  else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,2);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Beach House owned by Player 2. You have to pay $%d!\n", 25);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 25;
                                    players[1][1] = players[1][1] + 25;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Beach House owned by Player 2. You have to pay $%d!\n", 12);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 12;
                                    players[1][1] = players[1][1] + 12;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                // Player lands on Jail Time
                case 4:
                    jail = current_player;
                    printf("JAIL TIME! Player %d loses their next turn.\n", current_player);
                    break;
                // Player lands on Castle
                case 5:
                    r = properties / pow(10,4);
                    r = r % 10;
                    switch (r)
                    {
                        // The bank owns the Castle
                        case 0:
                            printf(" You landed on the Castle. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                if (current_player == 1) { // player one buys the property 
                                    if (players[current_player - 1][1] >= 100) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (5 % 7 * 20);
                                        properties += 10000; // adds 10000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 100) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (5 % 7 * 20);
                                        properties += 20000; // adds 20000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } 
                            }
                            break;
                        // Player one already owns the Castle
                        case 1: 
                            if (current_player == 1) {
                                printf(" You landed on the Castle. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 20000; // adds 20000 to make it 3
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,4);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Castle owned by Player 1. You have to pay $%d!\n", 41);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 41;
                                    players[0][1] = players[0][1] + 41;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Castle owned by Player 1. You have to pay $%d!\n", 20);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 20;
                                    players[0][1] = players[0][1] + 20;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Castle
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Castle. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 20000;
                                } 
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,4);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Castle owned by Player 2. You have to pay $%d!\n", 41);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 41;
                                    players[1][1] = players[1][1] + 41;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Castle owned by Player 2. You have to pay $%d!\n", 20);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 20;
                                    players[1][1] = players[1][1] + 20;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                // Player lands on Feelin' Lucky
                case 6:
                    printf("Are you feelin' lucky today? Let's determine your luck by rolling the dice \n");
                    int lucky_roll = roll_dice();
                    printf("Roll: %d\n\n", lucky_roll);
                    int lower, upper, lucky_money;
                    switch (lucky_roll)
                    {
                        case 1: // Player will go to jail
                            jail = current_player;
                            break;
                        case 2: // Player will get money based on a random number 
                            lower = 100;
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player - 1][1] = players[current_player - 1][1] + lucky_money;
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 3: 
                            lower = 100;
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player - 1][1] = players[current_player - 1][1] + lucky_money;
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 4:
                            lower = 50;
                            upper = 150;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] - lucky_money;
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 5:
                            lower = 100; 
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] + lucky_money;
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 6:
                            lower = 50; 
                            upper = 150;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] - lucky_money;
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                    }     
                    break;
                // Player lands on RailRoad
                case 7:
                    r = properties / pow(10,6);
                    r = r % 10;
                    switch (r) 
                    {
                        case 0:
                            printf(" You landed on the Railroad. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                //players[current_player - 1][1] = players[current_player - 1][1] - 150;
                                if (current_player == 1) {
                                    if (players[current_player - 1][1] >= 100) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 100;
                                        properties += 1000000;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 100) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 100;
                                        properties += 2000000;
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                }
                            }
                            break;
                        case 1:
                            r = properties / pow(10,6);
                            r = r % 10;
                            if (current_player == 2) {
                                printf("\nYou landed on the Railroad owned by Player 1. You have to pay $%d!\n", 35);
                                players[current_player - 1][1] = players[current_player - 1][1] - 35;
                                players[0][1] = players[0][1] + 35;
                                printf("\nNew balance: $%d", players[current_player - 1][1]);
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                printf("You already own this property.");
                            }
                            break;
                        case 2:
                            r = properties / pow(10,6);
                            r = r % 10;
                            if (current_player == 1) {
                                printf("\nYou landed on the Railroad owned by Player 2. You have to pay $%d!\n", 35);
                                players[current_player - 1][1] = players[current_player - 1][1] - 35;
                                players[1][1] = players[1][1] + 35;
                                printf("\nNew balance: $%d", players[current_player - 1][1]);
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                printf("You already own this property.");
                            }
                            break;
                            
                    }
                    break;
                // Player lands on Igloo
                case 8:
                    r = properties / pow(10,7);
                    r = r % 10;
                    switch (r)
                    {
                        // The bank owns the Igloo
                        case 0:
                            printf(" You landed on the Igloo. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                if (current_player == 1) { // player one buys the property 
                                    if (players[current_player - 1][1] >= 20) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (8 % 7 * 20);
                                        properties += 10000000; // adds 10000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 20) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (8 % 7 * 20);
                                        properties += 20000000; // adds 20000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } 
                            }
                            break;
                        // Player one already owns the Igloo
                        case 1: 
                            if (current_player == 1) {
                                printf(" You landed on the Igloo. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 20000000; 
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,7);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Igloo owned by Player 1. You have to pay $%d!\n", 9);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[0][1] = players[0][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Igloo owned by Player 1. You have to pay $%d!\n", 4);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[0][1] = players[0][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Igloo
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Igloo. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 20000000;
                                } 
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,7);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Igloo owned by Player 2. You have to pay $%d!\n", 9);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[1][1] = players[1][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Igloo owned by Player 2. You have to pay $%d!\n", 4);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[1][1] = players[1][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                // Player lands on Farm House
                case 9:
                    r = properties / pow(10,8);
                    r = r % 10;
                    switch (r)
                    {
                        // The bank owns the Farm House
                        case 0:
                            printf(" You landed on the Farm House. Do you want to buy this property? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if (is_buy == 'Y') {
                                if (current_player == 1) { // player one buys the property 
                                    if (players[current_player - 1][1] >= 40) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (9 % 7 * 20);
                                        properties += 100000000; // adds 10000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } else if (current_player == 2) {
                                    if (players[current_player - 1][1] >= 40) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - (9 % 7 * 20);
                                        properties += 200000000; // adds 20000 to the current properties number
                                    } else {
                                        printf("You dont have enough money to buy this property.\n");
                                    }
                                } 
                            }
                            break;
                        // Player one already owns the Farm House
                        case 1: 
                            if (current_player == 1) {
                                printf(" You landed on the Farm House. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 200000000; 
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,8);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Farm House owned by Player 1. You have to pay $%d!\n", 17);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 17;
                                    players[0][1] = players[0][1] + 17;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Farm House owned by Player 1. You have to pay $%d!\n", 8);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 8;
                                    players[0][1] = players[0][1] + 8;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Farm House
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Farm House. Do you want to renovate this property? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if (is_buy == 'Y') {
                                    players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                    properties += 200000000;
                                }
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,8);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Farm House owned by Player 2. You have to pay $%d!\n", 17);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 17;
                                    players[1][1] = players[1][1] + 17;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Farm House owned by Player 2. You have to pay $%d!\n", 8);
                                    players[current_player - 1][1] = players[current_player - 1][1] - 8;
                                    players[1][1] = players[1][1] + 8;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                    

                default:
                    break;
                }

                // Displays the player's money and property
                for (int i = 1; i < 3; i++) {
                    printf("\nPlayer %d:", i);
                    for (int j = 0; j < 3; j++) {
                        switch (j) {
                            case 0:
                                printf("\nPosition: %d", players[i-1][j]);
                                break;
                            case 1:
                                printf("\nMoney: %d\n", players[i-1][j]);
                                break;
                            // case 2:
                            //     printf("\nProperties: %d", players[i-1][j]);
                            //     break;
                            default:
                                break;
                        }
                    }
                }


                // Change players
                current_player = change_player(current_player);

                // turns --;
            }
            else {
                printf("Turn Skipped");
                current_player = change_player(current_player);
            }

            if (players[current_player -1][1] < 0) {
                    printf("Player %d is bankrupt! GAME OVER!\n\n", current_player);
                    is_end = true;
                }
            else if (players[change_player(current_player)-1][1] < 0){
                    printf("Player %d is bankrupt! GAME OVER!\n\n", change_player(current_player));
                    is_end = true;
            }
        }

        //starting a new game
        printf("Start new game? (Y or N) ");
        scanf(" %c", &is_new_game);
    }
    while (is_new_game != 'N');

    printf("\n\nThanks for playing!\n");

    return 0;
}