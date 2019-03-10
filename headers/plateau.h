#ifndef PLATEAU_H
#define PLATEAU_H

/**
 * \file plateau.h
 * \brief Manages the board and this type of data
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019 
 */

/**
 * \struct Coord
 * \brief Object coordinates
 * Represent the coordinates couple (x,y) on the board
 */

typedef struct 
{
    int x;
    int y;
} Coord;

/**
 * \brief Define the type Pcoord as a Coord pointer
 */

typedef struct Coord* Pcoord; 



/**
 * \struct Board
 * \brief Object Board
 *  Represent the Board of the game with width, height and his 2d table of coord pointers
 */

typedef struct
{
    int width;
    int height;
    Pcoord** points;
} Board;


/**
 * \fn int check_file(char* path)
 * \brief Function which verifies the integrity and structure of a file
 * \param path : the path to the file to verify, can't be NULL
 * \return (1 : true)  if file structure is correct else return ( 0 : false )
 */
int check_file(char* path); 

/**
 * \fn int read_file(Board* pboard, char* path)
 * \brief Function which read a file and initialize the related Board
 * \param  pboard : A board pointer, can't be NULL
 * \param  path : the path to the file to verify, can't be NULL
 * \return (1 : true)  if no errors occured else return ( 0 : false )
 */
int read_file(Board* pboard, char* path); 

/**
 * \fn void create_empty_board(Board* pboard)
 * \brief Function which initialize an empty board
 * \param  pboard : A board pointer, can't be NULL
 * \return void
 */
void create_empty_board(Board* pboard); 

/**
 * \fn Pcoord* get_valid_moves(Board* pboard)
 * \brief Function which gives a valid moves list 
 * \param  pboard : A board pointer, can't be NULL
 * \return a Coord list
 */
Pcoord* get_valid_moves(Board* pboard);

/**
 * \fn int is_move_valid(Board* pboard,Pcoord pcoord);
 * \brief Function which verify that a move is valid
 * \param  pboard : A board pointer, can't be NULL
 * \param  pcoord : The coordinates of the selected move , can't be NULL
 * \return (1 : true)  if no errors occured else return ( 0 : false )
 */
int is_move_valid(Board* pboard,Pcoord pcoord);

/**
 * \fn Board* initialize_rand()
 * \brief Function which initialize a board randomly
 * \return A pointer to a board
 */
Board* initialize_rand();

/**
 * \fn int play_move(Board* pboard, Pcoord pcoord)
 * \brief Add a point on the board.
 *
 * \param pboard Pointer to the board being played.
 * \param pcoord Pointer to selected coordinates.
 * \return 1 if point successfully added, 0 otherwise.
 */
int play_move(Board* pboard,Pcoord pcoord);

/**
 * \fn int is_game_over(Board* pboard);
 * \brief check that no points can be added 
 * \param pboard Pointer to the board being played.
 * \return 1 if point successfully added, 0 otherwise.
 */
int is_game_over(Board* pboard);

#endif
