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
#include <stdio.h>

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
	ASK_HELP, /**< Ask for help to be displayed */
	QUIT_GAME /**<Quit the game */
};

/**
 * \struct playedMove
 * \brief Played moves since the beginning of the game.
 *
 * Data are saved in a double linked-list structure that contains all the played moves.
 */

/**
 * \struct coord
 * \brief Coordinates on the Board
 */
typedef struct coord* Move;
typedef struct coord{
  int x; /**< Horizontal address */
  int y; /**< Vertical address */
  Move previous;
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

void update_points_scored();

int get_points_scored();

void update_points_scored_val(int val);

/**
 * \fn void create_empty_board(Board* pboard)
 * \brief Initialize an empty Board
 *
 * \param pboard : Pointer to Board, pboard->points SHOULD be NULL
 */
Board create_empty_board(int width,int height); 

/**
 * \fn p_point* get_valid_moves(Board* pboard)
 * \brief Give a list of all valid moves.
 *
 * \param pboard Board pointer
 * \return A p_point list
 */
void get_valid_moves(Board* pboard,Move* pvalid_points);

/**
 * \fn bool is_move_valid(Board* pboard,p_point p_point);
 * \brief Check if a move is valid.
 *
 * \param pboard Board pointer
 * \param p_point Coordinates of the selected move
 * \return true if no error occured, false otherwise
 */
bool is_move_valid(Board* pboard,Coord coord,Move* pmove,int* error);

/**
 * \fn void print_error(int* error);
 * \brief print error type.
 *
 * \param int* error not null
 */
void print_error(int* error);

/**
 * \fn bool is_move_in_board(Board* pboard,Coord coord);
 * \brief tests if desired move is within the board
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \return true if move is in board else false
 */
bool is_move_in_board(Board* pboard,Coord coord);

/**
 * \fn bool is_move_exists_already(Board* pboard,Coord coord);
 * \brief tests if desired move exists already
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \return true if move exists already else false
 */
bool is_move_exists_already(Board* pboard,Coord coord);

/**
 * \fn void horizontal_search(Move* pcand_lines,Coord coord,Board* pboard);
 * \brief searches for possible alignements on horizontal axis
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \param pcand_lines pointer to list of possible alignements
 * \ensures pcand_lines contains all possible horizontal alignements
 */
void horizontal_search(Move* pcand_lines,Coord coord,Board* pboard);

/**
 * \fn void vertical_search(Move* pcand_lines,Coord coord,Board* pboard);
 * \brief searches for possible alignements on vertical axis
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \param pcand_lines pointer to list of possible alignements
 * \ensures pcand_lines contains all possible vertical alignements
 */
void vertical_search(Move* pcand_lines,Coord coord,Board* pboard);

/**
 * \fn void NE_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard);
 * \brief searches for possible alignements on north east diagonal axis
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \param pcand_lines pointer to list of possible alignements
 * \ensures pcand_lines contains all possible north east diagonal alignements
 */
void NE_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard);

/**
 * \fn void NW_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard);
 * \brief searches for possible alignements on north west diagonal axis
 *
 * \param pboard pointer to board
 * \param coord Coord structure of desired point
 * \param pcand_lines pointer to list of possible alignements
 * \ensures pcand_lines contains all possible north west diagonal alignements
 */
void NW_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard);


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
void execute_action(Board* pboard, enum action action, bool* quit);

/**
 * \fn bool is_game_over(Board* pboard);
 * \brief Check if game is over. 
 *
 * \param pboard Pointer to the Board being played.
 * \return true if game is over, false otherwise.
 */
bool is_game_over(Board* pboard);

/**
 * \fn void free_board(Board* pboard)
 * \brief free allocated memory of board
 *
 * \param Board* pboard pointer to board 
 */
void free_board(Board* pboard);

int get_random_number(int min, int max);

/**
 * \fn void remove_point(Board* pboard,Coord coord);
 * \brief removes point from board
 *
 * \param Board* pboard pointer to board 
 * \param coord Coord structure of point to be removed
 * \ensures removes point from board by freeing allocated memory and by calling remove_lines to remove all corresponding alignements
 */
void remove_point(Board* pboard,Coord coord);

/**
 * \fn void remove_points(Board* pboard);
 * \brief remove all points from board
 *
 * \param Board* pboard pointer to board
 * \ensures removes all points from board, freeing allocated memory, without calling remove lines 
 */
void remove_points(Board* pboard);

/*void horizontal_lines_on_init(Board* pboard);*/

/**
 * \fn void save_board(Board* pboard)
 * \brief Save the current board into a file.
 *
 * @param pboard Pointer to the board being played
 */
void save_board(Board* pboard);

/**
 * \fn Board* initialize_rand(void)
 * \brief Randomly initalize a Board.
 *
 * \return Pointer to a Board
 */
Board initialize_rand(void);

/**
 * \fn bool read_file(Board* pboard, char* path)
 * \brief Read the given file and initialize the Board accordingly.
 *
 * \param pboard Board pointer, SHOULD be NULL
 * \param path File absolute path
 * \return true if no error occured, false otherwise
 */
bool initialize_file(Board* pboard, char* path);

#endif
