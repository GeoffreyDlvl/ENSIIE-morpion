#ifndef BOARD_H
#define BOARD_H

/**
 * \file board.h
 * \brief This file handles the Board.
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019 
 *
 * Handles the grid, points and lines on it.
 *
 */

#include <stdbool.h> 

/**
 * \enum action
 * \brief Represents a game action.
 */
enum action 
{ 
	PLAY_MOVE, /**< Play a move */ 
	CANCEL_MOVE, /**< Cancel last move */
	REPLAY_MOVE, /**< Replay a canceled move */
	LIST_MOVES, /**< List all valid moves */
	ASK_HELP /**< Ask for help to be displayed */
};

/**
 * \struct coord
 * \brief Coordinates on the Board
 */
typedef struct coord
{
    int x; /**< Horizontal address */
    int y; /**< Vertical address */
} Coord;
/**< \brief coord structure alias */

/**
 * \brief Pointer to Coord
 */
typedef int* Ppoint; 

/**
 * \struct board
 * \brief Represent the Board of the game with width, height and a 2d table of Coord pointers.
 */
typedef struct board
{
    int width; /**< Board width */
    int height; /**< Board height */
    Ppoint** points; /**< Bidimensionnal array of Ppoint */ 
} Board;
/**< \brief board structure alias */

/**
 * \fn bool check_file(char* path)
 * \brief Check the integrity and structure of a file.
 *
 * \param path : the path to the file to verify
 * \return true if file structure is correct, false otherwise
 */
bool check_file(char* path); 

/**
 * \fn bool read_file(Board* pboard, char* path)
 * \brief Read the given file and initialize the Board accordingly.
 *
 * \param pboard Board pointer, SHOULD be NULL
 * \param path File absolute path
 * \return true if no error occured, false otherwise
 */
bool read_file(Board* pboard, char* path); 

/**
 * \fn void create_empty_board(Board* pboard)
 * \brief Initialize an empty Board
 *
 * \param pboard : Pointer to Board, pboard->points SHOULD be NULL
 */
void create_empty_board(Board* pboard); 

/**
 * \fn p_point* get_valid_moves(Board* pboard)
 * \brief Give a list of all valid moves.
 *
 * \param pboard Board pointer
 * \return A p_point list
 */
Coord* get_valid_moves(Board* pboard);

/**
 * \fn bool is_move_valid(Board* pboard,p_point p_point);
 * \brief Check if a move is valid.
 *
 * \param pboard Board pointer
 * \param p_point Coordinates of the selected move
 * \return true if no error occured, false otherwise
 */
bool is_move_valid(Board* pboard,Coord coord);

/**
 * \fn Board* initialize_rand(void)
 * \brief Randomly initalize a Board.
 *
 * \return Pointer to a Board
 */
Board* initialize_rand(void);

/**
 * \fn bool add_point(Board* pboard, p_point p_point)
 * \brief Add a point on the Board.
 *
 * \param pboard Pointer to the Board being played
 * \param p_point Pointer to selected coordinates
 * \return true if point successfully added, false otherwise.
 */
bool add_point(Board* pboard, Coord coord);

/**
 * \fn void execute_action(Board* pboard, enum choice choice, p_point p_point)
 * \brief Execute action passed as a parameter.
 * 
 * \param pboard Pointer to the Board being played
 * \param action Action to execute
 * \param p_point Coordinates affected by the action (NULL if action does not affect any coordinate)
 */
void execute_action(Board* pboard, enum action action, Coord coord);

/**
 * \fn bool is_game_over(Board* pboard);
 * \brief Check if game is over. 
 *
 * \param pboard Pointer to the Board being played.
 * \return true if game is over, false otherwise.
 */
bool is_game_over(Board* pboard);

/**
 * \fn void free_board(Board* pboard);
 * \brief free allocated memory of board
 *
 * \param Board* pboard pointer to board 
 */
void free_board(Board* pboard);

#endif
