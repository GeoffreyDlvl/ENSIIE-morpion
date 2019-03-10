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

/**
 * \struct Coord
 * \brief Coordinates on the Board
 */
typedef struct 
{
    int x; /**< Horizontal address */
    int y; /**< Vertical address */
} Coord;

/**
 * \brief Define the type Pcoord as a Coord pointer.
 */
typedef struct Coord* Pcoord; 

/**
 * \struct Board
 * \brief Represent the Board of the game with width, height and his 2d table of coord pointers.
 */
typedef struct
{
    int width; /**< Board width */
    int height; /**< Board height */
    Pcoord** points; /**< Bidimensionnal array of Pcoord */ 
} Board;


/**
 * \fn int check_file(char* path)
 * \brief Check the integrity and structure of a file.
 *
 * \param path : the path to the file to verify
 * \return 1 if file structure is correct, 0 otherwise
 */
int check_file(char* path); 

/**
 * \fn int read_file(Board* pboard, char* path)
 * \brief Read the given file and initialize the Board accordingly.
 *
 * \param pboard Board pointer, SHOULD be NULL
 * \param path File absolute path
 * \return 1 if no error occured, 0 otherwise
 */
int read_file(Board* pboard, char* path); 

/**
 * \fn void create_empty_board(Board* pboard)
 * \brief Initialize an empty Board
 *
 * \param pboard : Pointer to Board, SHOULD be NULL
 */
void create_empty_board(Board* pboard); 

/**
 * \fn Pcoord* get_valid_moves(Board* pboard)
 * \brief Give a list of all valid moves.
 *
 * \param pboard Board pointer
 * \return A Pcoord list
 */
Pcoord* get_valid_moves(Board* pboard);

/**
 * \fn int is_move_valid(Board* pboard,Pcoord pcoord);
 * \brief Check if a move is valid.
 *
 * \param pboard Board pointer
 * \param pcoord Coordinates of the selected move
 * \return 1 if no error occured, 0 otherwise
 */
int is_move_valid(Board* pboard,Pcoord pcoord);

/**
 * \fn Board* initialize_rand()
 * \brief Randomly initalize a Board.
 ù
 * \return Pointer to a Board
 */
Board* initialize_rand();

/**
 * \fn int play_move(Board* pboard, Pcoord pcoord)
 * \brief Add a point on the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param pcoord Pointer to selected coordinates.
 * \return 1 if point successfully added, 0 otherwise.
 */
int play_move(Board* pboard,Pcoord pcoord);

/**
 * \fn int is_game_over(Board* pboard);
 * \brief Check if game is over. 
 *
 * \param pboard Pointer to the Board being played.
 * \return 1 if game is over, 0 otherwise.
 */
int is_game_over(Board* pboard);

#endif
