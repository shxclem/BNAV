#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Getting the functions.h file
#include "functions.h"

int main () {
    
    //Initializing values
    int choice;
    srand(time(NULL));
    int winner = 0;
    int player = 1;

    /*! Printing the menu*/
    printf("Welcome to BNAV Project !\n");
    do {

        printf("What do you want to do ?\n");
        printf("1. Print the rules\n");
        printf("2. Play a game\n");
        printf("3. Quit\n\n");

        //Getting the user's choice
        scanf("%d", &choice);

        switch(choice) {
            //First case, we print the rules
            case 1:
                printf("BNAV is a battleship game in which you play against a bot.\n");
                printf("The rules are simple : first, you need to place your boats onto your board as you wish.\n");
                printf("Then, each turn, you have to try to guess where are your opponent's boats in order to hit them.\n");
                printf("The game is over when one of the players have no boat remaining.\n\n");

                break;
            
            //Second case, we launch the game
            case 2:

                int decision;

                do {

                    printf("Who do you want to play against ?\n");
                    printf("1. A real player\n");
                    printf("2. A bot\n");
                    printf("3. Go back to menu\n");

                    //Getting the user's decision
                    scanf("%d", &decision);

                    switch(decision) {

                        //First case, we play a game against a player
                        case 1:
                            Game* game1 = createGame(PLAYER);

                            // While there is no winner
                            while (!winner) {
                                printf("******************* NEW TURN **************************\n\n");
                                turn(game1, player);

                                // Checking if there is a winner
                                winner = checkWinner(game1, player);

                                // Changing the player
                                player = (player == 1) ? 2 : 1;
                                printf("******************* END TURN **************************\n\n");
                            }

                            break;
                        
                        //Second case, we play a game against a bot
                        case 2:
                            Game* game2 = createGame(BOT);

                            // While there is no winner
                            while (!winner) {
                                printf("******************* NEW TURN **************************\n\n");
                                turn(game2, player);

                                // Checking if there is a winner
                                winner = checkWinner(game2, player);

                                // Changing the player
                                player = (player == 1) ? 2 : 1;
                                printf("******************* END TURN **************************\n\n");
                            }

                                break;

                        //Third case we go back
                        case 3:
                            printf("Back to menu\n");

                            break;
                    }
                } while (choice !=3);
                
                break;
            
            //Third case, we close the program
            case 3:
                printf("See you soon !\n\n");

                break;
            
            //Default case, the number is invalid
            default:
                printf("Invalid choice. Please type a number that is among propositions.\n\n");

        }  
    } while (choice !=3);
    
    return 0;
}