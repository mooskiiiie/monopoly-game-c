#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// To Do:
// - fix jail_time when both players go to jail


//Instantiate functionsxxq
int roll_dice();
void menu();
int change_player(int);
int check_position(int num[2][3], int, int);
int generate_random(int, int);

int main(){

    // Instantiate variables, important for the loop
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
        int turns = 5;
        char is_buy;
        while(is_end != true){
            
            position = players[current_player - 1][0];
            printf("\nPlayer %d's turn\n\n", current_player);
            printf("Current Position: %d\n\n", position);

            if (is_jail) {
                is_jail = false;
                current_player = change_player(current_player);
            }

            // Roll Dice
            int roll = roll_dice();
            printf("Roll: %d\n\n", roll);

            position = (position + roll) % 7;

            players[current_player - 1][0] = position;

            printf("Updated position: %d\n\n", position);
    
            // players = check_position(players, current_player, position);
            // add check position function
            //check_position(players, current_player, position);
            switch (position)
            {
            case 0:
                players[current_player - 1][1] = players[current_player -1][1] + 200;
                printf("Pass Go! New Balance: %d\n", players[current_player -1][1]);
                break;
            case 1:
                switch (properties % )
                {
                    case 0:
                        printf(" You landed on the Tree House. Do you want to buy this property? (Y or N) ");
                        scanf("%c", &is_buy);
                        printf("\n");
                        if (is_buy == 'Y'){
                            players[current_player -1][1] = players[current_player -1][1] - (7 % 1 * 20);
                            properties += current_player;
                        }
                        break;
                    case 1:
                        if (current_player == 1) {
                            printf(" You landed on the Tree House. Do you want to renovate this property? (Y or N) ");
                            scanf("%c", &is_buy);
                            if (is_buy == 'Y'){
                                players[current_player -1][1] = players[current_player -1][1] - 50;
                            }
                            printf("\n");
                        }
                        else {
                            printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n");
                            players[current_player -1][1] = players[current_player -1][1] - (8 * roll);
                            printf("\nNew balance: $%d", players[current_player -1][1]);
                        }
                        break;
                    case 2:
                        if (current_player == 2) {
                            printf(" You landed on the Tree House. Do you want to renovate this property? (Y or N");
                            scanf("%c", &is_buy);
                            if (is_buy == 'Y'){
                                players[current_player -1][1] = players[current_player -1][1] - 50;
                            }
                            printf("\n");
                        }
                        else {
                            printf("\nYou landed on the Tree House owned by Player 1. You have to pay $%d!\n", 8 * roll);
                            players[current_player -1][1] = players[current_player -1][1] - (8 * roll);
                            printf("\nNew balance: $%d", players[current_player -1][1]);
                        }
                        // to do:
                        // add an if statement if owned by current player
                }
                break;
            case 2:
                int num = properties / 10;
                switch (num % 10000000)
                {
                    case 0:
                        printf(" You landed on the Tree House. Do you want to buy this property? (Y or N) ");
                        scanf("%c", &is_buy);
                        printf("\n");
                        if (is_buy == 'Y'){
                            players[current_player -1][1] = players[current_player -1][1] - 150;
                            properties += current_player;
                        }
                        break;
                    case 1:
                        if (current_player == 1) {
                            printf(" You landed on the Electric Company. Do you want to renovate this property? (Y or N) ");
                            scanf("%c", &is_buy);
                            if (is_buy == 'Y'){
                                players[current_player -1][1] = players[current_player -1][1] - 50;
                            printf("\n");
                        }
                        else {
                            printf("\nYou landed on the Electric Company owned by Player 1. You have to pay $%d!\n");
                            players[current_player -1][1] = players[current_player -1][1] - (8 * roll);
                            printf("\nNew balance: $%d", players[current_player -1][1]);
                        }
                        break;
                    case 2:
                        if (current_player == 2) {
                            printf(" You landed on the Electric Company. Do you want to renovate this property? (Y or N) ");
                            scanf("%c", &is_buy);
                            if (is_buy == 'Y'){
                                players[current_player -1][1] = players[current_player -1][1] - 50;
                            printf("\n");
                        }
                        else {
                            printf("\nYou landed on the Electric Company owned by Player 1. You have to pay $%d!\n");
                            players[current_player -1][1] = players[current_player -1][1] - (8 * roll);
                            printf("\nNew balance: $%d", players[current_player -1][1]);
                        }
                        break;
                }
                break;
            case 3:
                break;
            case 4:
                is_jail = true;
                //current_player = change_player(current_player);
                printf("JAIL TIME! Player loses his/her next turn");
                break;
            case 5:
                break;
            case 6:
                printf("Are you feelin' lucky today? Let's determine your luck by rolling the dice \n");
                int lucky_roll = roll_dice();
                printf("Roll: %d\n\n", lucky_roll);
                int lower, upper, lucky_money;
                switch (lucky_roll)
                {
                    case 1: 
                        is_jail = true;
                        //current_player = change_player(current_player);
                        break;
                    case 2:
                        lower = 100; 
                        upper = 200;
                        lucky_money = generate_random(lower, upper);
                        players[current_player -1][1] = players[current_player -1][1] + lucky_money;
                        printf("New Balance: %d\n", players[current_player -1][1]);
                        break;
                    case 3:
                        lower = 100;
                        upper = 200;
                        lucky_money = generate_random(lower, upper);
                        players[current_player -1][1] = players[current_player -1][1] + lucky_money;
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
                    default:
                        printf("Error");
                        break;
                }
                //position = (position + roll) % 7;
                //players[current_player - 1][0] = position;

                printf("Updated position: %d\n\n", position);
                break;
            
            default:
                printf("Error");
                break;
            }

            for(int i = 1; i < 3 ; i++){
                printf("\nPlayer %d:", i);
                for(int j = 0; j < 3 ; j++){
                    switch(j){
                        case 0:
                            printf("\nPosition: %d", players[i-1][j]);
                            break;
                        case 1:
                            printf("\nMoney: %d", players[i-1][j]);
                            break;
                        case 2:
                            printf("\nProperties: %d\n", players[i-1][j]);
                            break;
                        default:
                            break;
                    }
                }
            }

            // Change players
            current_player = change_player(current_player);
            
            /* if(win condition achieved) {
                is_end = true;
            }*/
            turns --;
            if(turns == 0) {
                is_end = true;
            }
        }
        // Starting a new game, repeats the overarching do-while loop
        printf("Start new game? (Y/N) \n");
        scanf("%c", &is_new_game);
                
    } while (is_new_game != 'N');

    printf("\n\n\nThanks for playing!\n");
    return 0;
}

/* 
    this function mimics the roll of a dice by generating a random number from 1-6
    @return the resulting roll 
*/
int roll_dice() {
    //Using modulo to make sure that the result will always be from 0 - 5, and add 1 to mimic the results of a dice roll
    int roll = rand() % 6 + 1;
    return roll;
}

/*
    this function presents the users the intro to the game
    @return none
*/
void menu() {
    // Initializing main menu screen
    printf("\nWelcome to Property...Property!\n");
    printf("GAME GAME GAME\n\n");
    printf("\t**************\n\n");
}

/*
    this function changes the current player's turn
    @return the current player rolling the dice
*/
int change_player(int current_player){
    if(current_player == 1){
        current_player = 2;
    }
    else {
        current_player = 1;
    }
    return current_player;
}

/*
    this function generates a random number in the range of l and r
    @return  the random number 
*/
int generate_random(int l, int r) { //this will generate random number in range l and r
   int rand_num = (rand() % (r - l + 1)) + l;
   return rand_num;
}