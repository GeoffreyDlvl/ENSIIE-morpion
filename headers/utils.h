#ifndef UTILS_H
#define UTILS_H

/**
 * \file utils.h
 * \brief Utility file.
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_b
 * \date 04.2019
 *
 * Handles various functions that had no place in project files, that is to say
 * error handling, file checking, installing dependencies, etc.
 *
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * \enum Error
 * \brief All errors.
 */
typedef enum
{
    WRONG_INPUT_ERR, /**< Wrong user input */
    FILE_PTR_ERR, /**< File could not be opened */
    FILE_DIMENSION_ERR, /**< Board dimensions in file are not NxM */
    FILE_UNKNOWN_CHAR_ERR, /**< Board character in file is unknown */
    POINT_ALREADY_EXIST_ERR, /**< The point already exists */
    INVALID_COORDINATES_ERR, /**< Coordinates are invalid */
    ALIGNMENT_ERR, /**< Alignment is incorrect */
} Error;

/**
 * \fn void install_dependencies(void);
 * \brief Install required dependencies on user machine.
 */
void install_dependencies(void);

/**
 * \fn size_t get_file_board_width(FILE *fp);
 * \brief Get the width of the Board represented by a file.
 *
 * \param fp FILE pointer.
 * \return The width of the Board.
 */
size_t get_file_board_width(FILE *fp);

/**
 * \fn size_t get_file_board_height(FILE *fp);
 * \brief Get the height of the Board represented by a file.
 *
 * \param fp FILE pointer.
 * \return The height of the Board.
 */
size_t get_file_board_height(FILE *fp);

/**
 * \fn bool check_file(FILE *fp, Error* err)
 * \brief Check the integrity and structure of a file.
 *
 * \param fp FILE pointer
 * \param err Pointer to Error that will hold potential Error (if file is incorrect).
 * \return True if file structure is correct, false otherwise
 */
bool check_file(FILE *fp, Error* err);

/**
 * \fn void empty_input_buffer(void);
 * \brief Empty the input buffer.
 */
void empty_input_buffer(void);

/**
 * \fn int get_random_number(int min, int max);
 * \brief Generate a random integer between min and max.
 *
 * Random number generator must be seeded.
 *
 * \param min Min value.
 * \param max Max value.
 * \return Integer between min and max.
 */
int get_random_number(int min, int max);

#endif
