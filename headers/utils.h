#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>


typedef enum error
{
    WRONG_INPUT_ERR, /**< Wrong user input */
    FILE_PTR_ERR, /**< File could not be opened */
    FILE_DIMENSION_ERR, /**< Board dimensions in file are not NxM */
    FILE_UNKNOWN_CHAR_ERR, /**< Board character in file is unknown */
    POINT_ALREADY_EXIST_ERR, /**< The point already exists */
    INVALID_COORDINATES_ERR, /**< Coordinates are invalid */
    ALIGNMENT_ERR, /**< Alignment is incorrect */
    /* ADD MORE ENUMERATIONS IF REQUIRED */
} Error;

void install_dependencies(void);

size_t get_file_board_width(FILE *fp);

size_t get_file_board_height(FILE *fp);

/**
 * \fn bool check_file(char* path)
 * \brief Check the integrity and structure of a file.
 *
 * \param path : the path to the file to verify
 * \return true if file structure is correct, false otherwise
 */
bool check_file(FILE *fp, Error* err);

void empty_input_buffer(void);

#endif
