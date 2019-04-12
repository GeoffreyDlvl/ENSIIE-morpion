#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

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
bool check_file(FILE *fp);

#endif
