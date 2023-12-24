/**
 * @file functions.c
 * @author Clément DURECU
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

/**
 * @brief  Function to initialize a **board** of game 
 * @param[in] size the **size** of the board
 * @return The board we initialized 
 */
Board* initBoard (int size) {

    //Allocate matrix memory
    Board* board = (Board*) malloc(sizeof(Board));
    board->size=size;

    board->matrix = malloc(size * size * sizeof(BoxType));
    board->shots = malloc(size * size * sizeof(BoxType));
    for (int i=0 ; i<size ; i++) {
        board->matrix[i] = malloc(size * sizeof(BoxType));
        board->shots[i] = malloc(size * sizeof(BoxType));
        for (int j=0 ; j<size ; j++) {
            board->matrix[i][j] = WATER;        //Initialize all boxes as WATER
            board->shots[i][j] = WATER;         //Initialize all boxes as WATER_SHOT
        }
    }

    return board;
}

/**
 * @brief Function to free memory allocated to a board
 * @param[in] board the board we want to free memory from
 * @return void
 */
void freeBoard(Board* board) {     
    for (int i = 0; i < board->size; i++) {         
        free(board->matrix[i]);     
    }      
    free(board->matrix);     
    free(board); 
}

/**
 * @brief Function to print the board
 * @param[in] game the game we are currently playing
 * @param[in] player the player we want to print the board of 
 * @return void
 */
void printBoard(Game* game, int player) {
    Board* board = (player == 1) ? game->P1_board : game->P2_board;

    printf("\n");

    // Printing the board
    printf("   1 2 3 4 5 6 7 8 9 10               1 2 3 4 5 6 7 8 9 10\n");
    for (int i = 0; i < board->size; i++) {
        printf("%d ", i + 1);
        if(i < 9) {
            printf(" ");
        }
        for (int j = 0; j < board->size; j++) {
            if (board->matrix[i][j] == WATER) {
                printf("0 ");
            } else if (board->matrix[i][j] == WATER_SHOT) {
                printf("O ");
            } else if (board->matrix[i][j] == BOAT) {
                printf("B ");
            } else if (board->matrix[i][j] == WRECK) {
                printf("X ");
            }
        }
        printf("            ");
        printf("%d ", i + 1);   
        if(i < 9) {
            printf(" ");
        }
        for (int j = 0; j < board->size; j++) {
            if (board->shots[i][j] == WATER) {
                printf("0 ");
            } else if (board->shots[i][j] == WATER_SHOT) {
                printf("O ");
            } else if (board->shots[i][j] == BOAT) {
                printf("B ");
            } else if (board->shots[i][j] == WRECK) {
                printf("X ");
            }
        }

        printf("\n");
    }
}

/**
 * @brief Function to create a boat
 * @param[in] playerBoard the board of the player we want to create a boat on
 * @param[in] boatNumber the number of boats per player
 * @return The boat we created
 */ 
Boat* createBoat(Board* playerBoard, int boatNumber) {
    Boat* boat = (Boat*) malloc(sizeof(Boat));

    int isValid = 0;

    while (!isValid) {
        // Getting the boat size
        boat->size = BOAT_SIZES(boatNumber);
        boat->hits = 0;

        // Getting the boat direction
        boat->direction = (rand() % 2) ? 'H' : 'V';

        // Getting the boat position
        boat->x = rand() % (BOARD_SIZE - boat->size);
        boat->y = rand() % (BOARD_SIZE - boat->size);

        // Verifying if the boat is valid
        isValid = 1;
        for (int i = 0; i < boat->size; i++) {
            if (boat->direction == 'H') {
                if (playerBoard->matrix[boat->x][boat->y + i] != WATER) {
                    isValid = 0;
                }
            } else {
                if (playerBoard->matrix[boat->x + i][boat->y] != WATER) {
                    isValid = 0;
                }
            }
        }
    }

    return boat;
}

/**
 * @brief Function to verify if a boat is still alive
 * @param[in] boat the boat we want to check life status
 * @return 1 if the size of the boat is > 0, else 0
 */ 
int isBoatAlive(Boat* boat) {
    return boat->size > 0;
}

/**
 * @brief Function to create a new game
 * @param[in] gameType the type of game : **player mode, normal bot mode or hardcore bot mode**
 * @return The game we created
 */
Game* createGame(GameType gameType) {
    Game* game = (Game*) malloc(sizeof(Game));
    game->P1_board = initBoard(BOARD_SIZE);
    game->P2_board = initBoard(BOARD_SIZE);
    game->P1_boats = (Boat*) malloc(BOAT_NUMBER * sizeof(Boat));
    game->P2_boats = (Boat*) malloc(BOAT_NUMBER * sizeof(Boat));
    game->gameType = gameType;

    // Creating the boats for player 1
    for (int i = 0; i < BOAT_NUMBER; i++) {
        game->P1_boats[i] = *createBoat(game->P1_board, i);

        for (int j = 0; j < game->P1_boats[i].size; j++) {
            if (game->P1_boats[i].direction == 'H') {
                game->P1_board->matrix[game->P1_boats[i].x][game->P1_boats[i].y + j] = BOAT;
            } else {
                game->P1_board->matrix[game->P1_boats[i].x + j][game->P1_boats[i].y] = BOAT;
            }
        }
    }

    // Creating the boats for player 2
    for (int i = 0; i < BOAT_NUMBER; i++) {
        game->P2_boats[i] = *createBoat(game->P2_board, i);

        for (int j = 0; j < game->P2_boats[i].size; j++) {
            if (game->P2_boats[i].direction == 'H') {
                game->P2_board->matrix[game->P2_boats[i].x][game->P2_boats[i].y + j] = BOAT;
            } else {
                game->P2_board->matrix[game->P2_boats[i].x + j][game->P2_boats[i].y] = BOAT;
            }
        }
    }


    return game;
}

/**
 * @brief Function to free memory allocated to a game
 * @param[in] game the game we want to free memory allocated to
 * @return void
 */
void freeGame(Game* game) {
    freeBoard(game->P1_board);
    freeBoard(game->P2_board);
    free(game->P1_boats);
    free(game->P2_boats);
    free(game);
}

/** 
 * @brief Function to print the boats of a player
 * @param[in] game the game we are currently playing
 * @param[in] player the player we want to print the boats of 
 * @return void
 */
void printBoats(Game* game, int player) {
    Boat* boats = (player == 1) ? game->P1_boats : game->P2_boats;

    for (int i = 0; i < BOAT_NUMBER; i++) {
        if(boats[i].size > 0) {
            printf("Boat %d - Size %d - HealthPoint %d - Postion %d %d - Direction %c\n", i+1, boats[i].size,  boats[i].size - boats[i].hits, boats[i].x + 1, boats[i].y + 1, boats[i].direction);
        }
    }
}

/**
 * @brief Function to show the POV of the player : **player board + shot board**
 * @param[in] game the game we are currently playing
 * @param[in] player the player we want to show the POV of 
 * @return void
 */ 
void showPOV(Game* game, int player) {
    Board* board = (player == 1) ? game->P1_board : game->P2_board;

    printf("\nTHIS IS PLAYER %d BOARD / SHOT BOARD\n", player);
    printBoard(game, player);
    printf("\nTHIS IS PLAYER %d BOATS \n", player);
    printBoats(game, player);
}

/**
 * @brief Function to sequence the turn of the players
 * @param[in] game the game we are currently playing 
 * @param[in] player the player we want to sequence the turn of 
 * @param[in] gameType the type of game : **player mode, normal bot mode or hardcore bot mode**
 * @return 0 if no error
 */ 
int turn(Game* game, int player, GameType gameType) {
    int x, y;

    // Getting the player board
    Board* playerBoard = (player == 1) ? game->P1_board : game->P2_board;

    // Getting the opponent board
    Board* opponentBoard = (player == 1) ? game->P2_board : game->P1_board;

    // Getting the opponent boats
    Boat* opponentBoats = (player == 1) ? game->P2_boats : game->P1_boats;
    
    if(player == 1 || game->gameType == PLAYER) {
        // Showing the POV of the player
        showPOV(game, player);

        // Getting the shot position
        printf("Player %d, enter the shot position (format = [x] [y]) : ", player);
        scanf("%d %d", &x, &y);

        // Verifying if the shot position is valid
        if (x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE) {
            printf("Invalid shot position!\n");
            sleep(1);
            return 0;
        }

        // Verifying if the shot position has already been shot
        if (opponentBoard->matrix[x - 1][y - 1] == WATER_SHOT || opponentBoard->matrix[x - 1][y - 1] == WRECK) {
            printf("You have already shot this position!\n");
            sleep(1);
            return 0;
        }
    }
    else {    
        // Getting the shot position
        x = rand() % BOARD_SIZE + 1;
        y = rand() % BOARD_SIZE + 1;

        while (gameType == BOT_H && opponentBoard->matrix[x - 1][y - 1] != BOAT || gameType == BOT && opponentBoard->matrix[x - 1][y - 1] != WATER && opponentBoard->matrix[x - 1][y - 1] != BOAT) {
            x = rand() % BOARD_SIZE + 1;
            y = rand() % BOARD_SIZE + 1;
        }
        printf("The bot has shot the position %d %d\n", x, y);
        sleep(1);
    }
    
    // Shooting
    shoot(x, y, playerBoard, opponentBoard, opponentBoats);
}

/**
 * @brief Function to simulate a shot on the other board
 * @param[in] x the reference position in x
 * @param[in] y the reference position in y 
 * @param[in] playerBoard the board of the player who shots
 * @param[in] opponentBoard the board of the player who gets shot
 * @param[in] opponentBoats the position of the opponent boats
 * @return void
*/
void shoot(int x, int y, Board* playerBoard, Board* opponentBoard, Boat* opponentBoats) {
    int isHit = 0;

    // Verifying if the shot position has a boat
    if (opponentBoard->matrix[x - 1][y - 1] == BOAT) {
        printf("You have hit a boat!\n");
        sleep(1);
        // Setting the shot position as WRECK
        opponentBoard->matrix[x - 1][y - 1] = WRECK;
        playerBoard->shots[x - 1][y - 1] = WRECK;

        // Verifying if the boat has been destroyed
        for (int i = 0; i < BOAT_NUMBER; i++) {
            if(opponentBoats[i].direction == 'H') {
                if (opponentBoats[i].x == x - 1 && opponentBoats[i].y <= y - 1 && opponentBoats[i].y + opponentBoats[i].size > y - 1) {
                    opponentBoats[i].hits++;
                }
            } else {
                if (opponentBoats[i].y == y - 1 && opponentBoats[i].x <= x - 1 && opponentBoats[i].x + opponentBoats[i].size > x - 1) {
                    opponentBoats[i].hits++;
                }
            }

            if (opponentBoats[i].hits == opponentBoats[i].size) {
                opponentBoats[i].size = 0;
                printf("You have destroyed a boat!\n");
                sleep(1);
            }
        }

        isHit = 1;
    } else {
        // Setting the shot position as WATER_SHOT
        playerBoard->shots[x - 1][y - 1] = WATER_SHOT;
        printf("You have hit the water!\n");
        sleep(1);
    }
}

/**
 * @brief Function to verify if there is a winner
 * @param[in] game the game we are currently playing
 * @param[in] player the player we want to check if he is a winner
 * @return 1 if there is a winner, else 0
 */ 
int checkWinner(Game* game, int player) {
    Board* opponentBoard = (player == 1) ? game->P2_board : game->P1_board;
    Boat* opponentBoats = (player == 1) ? game->P2_boats : game->P1_boats;

    int isWinner = 1;

    // Verifying if there is a boat alive
    for (int i = 0; i < BOAT_NUMBER; i++) {
        if (isBoatAlive(&opponentBoats[i])) {
            isWinner = 0;
        }
    }

    // Verifying if all the boats have been shot
    for (int i = 0; i < opponentBoard->size; i++) {
        for (int j = 0; j < opponentBoard->size; j++) {
            if (opponentBoard->matrix[i][j] == BOAT) {
                isWinner = 0;
            }
        }
    }

    if (isWinner) {
        sleep(1);
        printf("Player %d has won!\n", player);
    }

    return isWinner;
}