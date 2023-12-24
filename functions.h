/**
 * @file functions.h
 * @author Clément DURECU
*/

#ifndef FUNCTIONS_H
    #define FUNCTIONS_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    // Defining the number of boats per player
    #define BOAT_NUMBER 5           
    // Define an array with the size of boats
    #define BOAT_SIZES(i) (i==0 ? 5 : (i==1 ? 4 : (i==2 ? 3 : (i==3 ? 3 : 2))))
    // Defining the side's size of the board
    #define BOARD_SIZE 10           

    /**
     * @brief Enumeration that contains the different possible states of a box
     */ 
    typedef enum boxType {
        WATER,                                                //No boat
        WATER_SHOT,                                           //No boat and has been shot
        BOAT,                                                 //There is a part of a boat
        WRECK                                                 //A part of a boat has been shot
    }BoxType;

    /**
     * @brief Enumeration that contains the different possible states of direction
     */
    typedef enum direction {
        H,
        V
    }Direction;

    /**
     * @brief Enumeration that contains the different possible states of game type
     */
    typedef enum gameType {
        PLAYER,                                               //Playing against a player
        BOT_H,                                                //Playing against a hardcore bot
        BOT                                                   //Playing against a normal bot
    }GameType;

    
    /**
     * @brief Structure that defines the parameters of each boats 
     */
    typedef struct boat {
        int size;                                             // Size of the boat
        int hits;                                             // Number of hits
        int x;                                                // x reference's position                                         
        int y;                                                // y reference's position
        char direction;                                       // 'V' for vertical - 'H' for horizontal
    }Boat;

    
    /**
     * @brief Structure that defines the parameters of the board
     */
    typedef struct board {
        int size;                                             //Size of the side of the board
        BoxType** matrix;                                     //Matrix that represents the board
        BoxType** shots;                                      //Matrix that represents the shots
    }Board;

    /** 
     * @brief Structure that defines the parameters of the game 
     */
    typedef struct game {
        Board* P1_board;                                       //Board of the Player 1
        Board* P2_board;                                       //Board of the Player 2
        Boat* P1_boats;                                       //List of Player 1 boats
        Boat* P2_boats;                                       //List of Player 2 boats
        GameType gameType;                                        //Type of the game
    }Game;

    // Function to initialize a board
    Board* initBoard(int size);

    // Function to free a board memory 
    void freeBoard(Board* board);

    // Function to print the board 
    void printBoard(Game* game, int player);
    
    // Function to create a boat with the given parameters 
    Boat* createBoat(Board* playerBoard, int boatNumber);

    // Function to verify if a boat is still alive 
    int isBoatAlive(Boat* boat);

    // Function to create a new game 
    Game* createGame();

    // Function to free a game memory 
    void freeGame(Game* game);

    // Function to print the boats 
    void printBoats(Game* game, int player);

    // Function to show the board from the point of view of a player 
    void showPOV(Game* game, int player);

    int turn(Game* game, int player, GameType gameType);

    int checkWinner(Game* game, int player);

    void shoot(int x, int y, Board* playerBoard, Board* opponentBoard, Boat* opponentBoats);

#endif