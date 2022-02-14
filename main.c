/*
    Description: This program is a simulation of a Monopoly Game where two players compete to acquire wealth by buying or renting properties.
    Programmed by: Athena Mae Arlegui
    Last Modified: Feb 6
    Version: 3
*/


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
int checkProperties(int*, int, int*);

/*
    This function simulates the roll of a dice
    @return the resulting roll of the dice
*/
int roll_dice() {
    int roll = rand() % 6 + 1;
    return roll;
}

/*
    This function shows the whole instruction of the game
    @return all the instructions and cost of the positions
*/
void menu() {
    printf("\nWelcome to Property...Property!\n\n");
    printf("This is a turn-based two-player board game. Players compete to acquire wealth by buying or renting properties.\nThe game ends when a player goes bankrupt.");
    printf("\n\nHere is the board:\n");
    printf("Position 0: GO - Collect $200 everytime you land or pass by this position.\n");
    printf("Position 1: Tree House - Cost $20\n");
    printf("Position 2: Electric Company - Cost $150\n");
    printf("Position 3: Beach House - Cost $60\n");
    printf("Position 4: Jaim Time - If the player lands here, he/she will lose his/her next turn.\n");
    printf("Position 5: Castle - Cost $100.\n");
    printf("Position 6: Feelin' Lucky - The player rolls the dice to determine his/her luck.\n");
    printf("\tIf its a prime number - collect an amount from 100-200\n");
    printf("\tIf its not a prime number - pay an amount from 50-150\n");
    printf("\tIt its 1 - the player goes to jail\n");
    printf("Position 7: Railroad - Cost $100.\n");
    printf("Position 8: Igloo - Cost $20.\n");
    printf("Position 9: Farm House - Cost $40.\n");
    printf("\n\nGAME GAME GAME\n\n");
    printf("*****************************\n");
    
}

/*
    This function changes the player every turn
    @param current_player - the current player
    @return returns the new player
*/
int change_player(int current_player){
    if(current_player == 1) {
        current_player = 2;
    }
    else {
        current_player = 1;
    }
    return current_player;
}

/*
    This function generates a random number in range l and r
    Precondition: l and r are based on feelin' lucky parameters
    @param l the first number of the range
    @param r the last number of the range
    @return the resulting random number from the given range
*/
int generate_random(int l, int r) { //this will generate random number in range l and r
   int rand_num = (rand() % (r - l + 1)) + l;
   return rand_num;
}

/*
    This function check the properties of the current player to see which one he/she can sell
    @param properties refers to the properties owned
    @param current_player this is the current_player
    @param balance refers to the current_player's balance
    @return returns your balance after selling your properties
*/
int checkProperties(int *properties, int current_player, int *balance) {
    int check_properties = *properties; // same value as the 9 digit 
    int count = 0; // to determine which element in the list we will use and what exponent
    char is_sell; // determines if the player will sell the property
    int new_balance = 0; // this is the balance of the player when he sells
    int value_properties[] = {10, 75, 30, 99999, 50, 99999, 50, 10, 20}; // the resale cost of the properties
    for (int x=9; x>0; x-=1) { // if x > 0 keep looping, but every loop we minus 1 to x
        printf("Property %d\n", check_properties % 10); // check_properties % 10 just gives us the right most number
        count += 1;

        if ((check_properties % 10 == current_player) || (check_properties % 10 == current_player + 2)) { // this condition just checks if it is owned by the current player
            printf("Do you want to sell this property for %d? (Y or N) ", value_properties[count - 1]); //value_properties[determines which element in the list to select]
            scanf(" %c", &is_sell);

            if (is_sell == 'Y') {
                *properties -= check_properties % 10 * pow(10, count - 1); // read this as 10 raised to (count - 1)
                new_balance += value_properties[count - 1]; // this adds the resale cost 
            }
        }
        check_properties /= 10; // removes the number that you just checked
    }
    *balance += new_balance;
    return 0;
}

/*
    The main function that runs the whole program
*/
int main() {

    // Instantiate variables
    char is_new_game; // this variable checks if you want to start a new game
    srand((unsigned) time(0)); // it creates a seed so that every turn there's a new random number generated

    do {
        menu(); 
        
        bool is_end = false; // checks if the game is over
        bool is_jail = false;   // checks if the player is in jail
        int current_player = 1; // this is the current player
        int players[2][2] = {{0, 200}, {0, 200}}; // a list of the player's position and balance respectively
        int properties = 0; // keeps track of who owns the properties & this is also the 9 digit integer
        int position = 0; // also refers to the player's position
        int r; 
        char is_buy; // asks the player if they want to buy the property
        int jail;

        while (is_end != true) { // while is_end is not true, the game will keep looping
            
            char is_roll = 'N'; // it keeps track if the player rolled the dice or not

            // Basically resets jail, so that no one is in it
            if (current_player == jail){
                current_player = change_player(current_player);
                jail = 3;
            }
            
            position = players[current_player - 1][0];
            printf("\nPlayer %d's turn\n\n", current_player); //prints the current player
            printf("Current Position: %d\n", position); // prints the player's position
            printf("Properties owned: %d\n\n", properties); // prints the player's properties

            // Roll Dice
            printf("Roll Dice? (Y/N) ");
            scanf(" %c", &is_roll);

            if (is_roll == 'Y' || is_roll == 'y'){
        
                int roll = roll_dice(); // this returns the roll of a dice
                printf("Roll: %d\n\n", roll);

                if (position +  roll>= 11){ // this checks if the player passed by GO or position 0
                    int new_balance = players[current_player - 1][1] + 200;
                    players[current_player - 1][1] = new_balance;
                    printf("You Passed by Go! New Balance: %d\n", new_balance);
                }

                position = (position + roll) % 10; // updates the position of the player based on the roll

                players[current_player - 1][0] = position; // updates the position of the player based on the roll

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
                    r = properties / pow(10,0); // gets the owner of the property inside the 9 digit integer. Whatever the number is beside the case, that is the property we are getting
                    r = r % 10;
                    switch (r)
                    { // 123412341
                    // 1
                        case 0:
                            printf("You landed on the Tree House. Do you want to buy this property for $20? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                           
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
                                if (current_player == 1) { // checks if the current_player is 1
                                    if (players[current_player - 1][1] >= 20) { // checks if player 1 has more than 20 
                                        players[current_player - 1][1] = players[current_player - 1][1] - (1 % 7 * 20); // subtract 20 from player 1's money
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
                        case 1: // if player 1 bought the property
                            r = properties / pow(10,0);
                            r = r % 10;
                            if (current_player == 1) {
                                printf(" You landed on the Tree House. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) { // do you want to buy
                                    if (players[current_player - 1][1] >= 50) { // do you have enough money
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50; //subtract
                                        properties += 2;  
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                }
                                printf("\n"); 
                            } else if ((current_player == 1) && (r == 3)) {
                                printf("You have already renovated this property.");
                            } else {
                                r = properties / pow(10,0);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n", 9); // cost of rent is 1/5 of the property cost times 2 + 1
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 9) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9; // subtract rent
                                    players[0][1] = players[0][1] + 9; // add the rent to player 1
                                    printf("\nNew balance: $%d", players[current_player - 1][1]); // prints new money of player 2
                                } else if (r == 1) {
                                    printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n", 4); // cost of rent is 1/5 of property cost
                                    //check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 4) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4; // subtract rent
                                    players[0][1] = players[0][1] + 4; // add rent to player 1
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        case 2:
                            if (current_player == 2) {
                                printf("You landed on the Tree House. Do you want to renovate this property for $50? (Y or N");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player -1][1] = players[current_player -1][1] - 50;
                                        properties += 2;
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                }
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                printf("You have already renovated this property.");
                            } else {
                                r = properties / pow(10,0);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Tree House owned by Player 2. You have to pay $%d!\n", 9);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 9) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[1][1] = players[1][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Tree House owned by Player 2. You have to pay $%d!\n", 4);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 4) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell
                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[1][1] = players[1][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                    }
                    break;
                // Player lands on Electric Company
                case 2: // 
                    r = properties / pow(10,1);
                    r = r % 10;
                    switch (r) 
                    { 
                        case 0:
                            printf("You landed on the Electric Company. Do you want to buy this property for $150? (Y or N) "); // do you want to buy the property
                            scanf(" %c", &is_buy); //ask if they want to buy
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) { // check if they said yes
                                if (current_player == 1) { // check who is buying
                                    if (players[current_player - 1][1] >= 150) { // check if they have money
                                        players[current_player - 1][1] = players[current_player - 1][1] - 150; // subtract the money if they have enough money
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
                        case 1: // player 1 owns this property
                            r = properties / pow(10,1);
                            r = r % 10;
                            if (current_player == 2) {
                                printf("\nYou landed on the Electrical Company owned by Player 1. You have to pay $%d!\n", (8 * roll)); // 8 times the roll the player got
                                // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < (8 * roll)) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                players[current_player - 1][1] = players[current_player - 1][1] - (8 * roll); // subtract the rent
                                players[0][1] = players[0][1] + (8 * roll); // add the rent to the other player
                                printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if ((current_player == 1) && (r == 1)) {
                                    printf("You already own this property.");
                                }
                                printf("\n");
                            break;
                        case 2: // player 2 owns this property
                            r = properties / pow(10,1);
                            r = r % 10;
                            if (current_player == 1) {
                                printf("\nYou landed on the Electrical Company owned by Player 2. You have to pay $%d!\n", (8 * roll));
                                if (players[current_player - 1][1] < (8 * roll)) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                            printf("You landed on the Beach House. Do you want to buy this property for $60? (Y or N)");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
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
                                printf("You landed on the Beach House. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 200; // adds 200 to make it 3
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                }
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,2);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Beach House owned by Player 1. You have to pay $%d!\n", 25);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 25) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 25;
                                    players[0][1] = players[0][1] + 25;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Beach House owned by Player 1. You have to pay $%d!\n", 12);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 12) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 12;
                                    players[0][1] = players[0][1] + 12;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the beach house
                        case 2:
                            if (current_player == 2) {
                                printf("You landed on the Beach House. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 200;  
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                }
                                printf("\n");
                            }  else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,2);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Beach House owned by Player 2. You have to pay $%d!\n", 25);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 25) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 25;
                                    players[1][1] = players[1][1] + 25;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Beach House owned by Player 2. You have to pay $%d!\n", 12);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 12) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                            printf("You landed on the Castle. Do you want to buy this property for $100? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
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
                                printf("You landed on the Castle. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 20000; // adds 20000 to make it 3
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,4);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Castle owned by Player 1. You have to pay $%d!\n", 41);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 41) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 41;
                                    players[0][1] = players[0][1] + 41;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Castle owned by Player 1. You have to pay $%d!\n", 20);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 20) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 20;
                                    players[0][1] = players[0][1] + 20;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Castle
                        case 2:
                            if (current_player == 2) {
                                printf("You landed on the Castle. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 20000;
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }                                   
                                } 
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,4);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Castle owned by Player 2. You have to pay $%d!\n", 41);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 41) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 41;
                                    players[1][1] = players[1][1] + 41;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Castle owned by Player 2. You have to pay $%d!\n", 20);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 20) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                            printf("JAIL TIME! Player %d loses their turn.\n", current_player);
                            break;
                        case 2: // Player will get money based on a random number 
                            lower = 100;
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player - 1][1] = players[current_player - 1][1] + lucky_money;
                            printf("You get $%d!\n", lucky_money);
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 3: 
                            lower = 100;
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player - 1][1] = players[current_player - 1][1] + lucky_money;
                            printf("You get $%d!\n", lucky_money);
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 4: // Player will pay money
                            lower = 50;
                            upper = 150;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] - lucky_money;
                            printf("You need to pay $%d\n", lucky_money);
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 5:
                            lower = 100; 
                            upper = 200;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] + lucky_money;
                            printf("You get $%d!\n", lucky_money);
                            printf("New Balance: %d\n", players[current_player -1][1]);
                            break;
                        case 6:
                            lower = 50; 
                            upper = 150;
                            lucky_money = generate_random(lower, upper);
                            players[current_player -1][1] = players[current_player -1][1] - lucky_money;
                            printf("You need to pay $%d\n", lucky_money);
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
                            printf("You landed on the Railroad. Do you want to buy this property for $100? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
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
                                // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 35) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                                // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 35) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                            printf("You landed on the Igloo. Do you want to buy this property for $20? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
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
                                printf("You landed on the Igloo. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 20000000; 
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,7);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Igloo owned by Player 1. You have to pay $%d!\n", 9);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 9) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[0][1] = players[0][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Igloo owned by Player 1. You have to pay $%d!\n", 4);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 4) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 4;
                                    players[0][1] = players[0][1] + 4;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Igloo
                        case 2:
                            if (current_player == 2) {
                                printf("You landed on the Igloo. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 20000000;
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }                                   
                                } 
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,7);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Igloo owned by Player 2. You have to pay $%d!\n", 9);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 9) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 9;
                                    players[1][1] = players[1][1] + 9;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Igloo owned by Player 2. You have to pay $%d!\n", 4);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 4) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                            printf("You landed on the Farm House. Do you want to buy this property for $40? (Y or N) ");
                            scanf(" %c", &is_buy);
                            printf("\n");
                            if ((is_buy == 'Y') || (is_buy == 'y')) {
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
                                printf("You landed on the Farm House. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] >= 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 200000000;
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }                                    
                                } 
                                printf("\n");
                            } else if ((current_player == 1) && (r == 3)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,8);
                                r = r % 10;
                                if (r == 3) {
                                    printf("\nYou landed on the Farm House owned by Player 1. You have to pay $%d!\n", 17);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 17) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 17;
                                    players[0][1] = players[0][1] + 17;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 1) {
                                    printf("\nYou landed on the Farm House owned by Player 1. You have to pay $%d!\n", 8);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 8) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 8;
                                    players[0][1] = players[0][1] + 8;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                }
                            }
                            break;
                        // Player 2 owns the Farm House
                        case 2:
                            if (current_player == 2) {
                                printf(" You landed on the Farm House. Do you want to renovate this property for $50? (Y or N) ");
                                scanf(" %c", &is_buy);
                                if ((is_buy == 'Y') || (is_buy == 'y')) {
                                    if (players[current_player - 1][1] > 50) {
                                        players[current_player - 1][1] = players[current_player - 1][1] - 50;
                                        properties += 200000000;
                                    } else {
                                        printf("You dont have enough money to renovate this property.");
                                    }                                   
                                }
                                printf("\n");
                            } else if ((current_player == 2) && (r == 4)) {
                                    printf("You already renovated this property.");
                                } else {
                                r = properties / pow(10,8);
                                r = r % 10;
                                if (r == 4) {
                                    printf("\nYou landed on the Farm House owned by Player 2. You have to pay $%d!\n", 17);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 17) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
                                    players[current_player - 1][1] = players[current_player - 1][1] - 17;
                                    players[1][1] = players[1][1] + 17;
                                    printf("\nNew balance: $%d", players[current_player - 1][1]);
                                } else if (r == 2) {
                                    printf("\nYou landed on the Farm House owned by Player 2. You have to pay $%d!\n", 8);
                                    // check if the player has enough money to pay rent
                                    if (players[current_player - 1][1] < 8) {
                                        printf("Uh oh! You dont have enough money to pay rent. Choose a property you would like to sell to the bank:\n");
                                        checkProperties(&properties, current_player, &players[current_player - 1][1]);
                                        // Show the player which properties he/she can sell

                                    }
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
                printf("---------------------------\n");
                printf("Summary:\n");
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
                printf("---------------------------\n");
            }
            else {
                printf("Turn Skipped"); // they said no to rolling the dice
            }

            // chekcs if anyone is bankrupt
            if (players[current_player -1][1] < 0) {
                    printf("Player %d is bankrupt! GAME OVER!\n\n", current_player);
                    is_end = true;
                }
            else if (players[change_player(current_player)-1][1] < 0){
                    printf("Player %d is bankrupt! GAME OVER!\n\n", change_player(current_player));
                    is_end = true;
            }
            // Change players

            current_player = change_player(current_player);

            // turns --;
        }

        //starting a new game
        printf("Start new game? (Y or N) ");
        scanf(" %c", &is_new_game);
    }
    while (is_new_game != 'N');

    printf("\n\nThanks for playing!\n");

    return 0;
}