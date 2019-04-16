#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "linux/limits.h"
#include "../headers/board.h"
#include "../headers/utils.h"


static Error* error;

/* The suite initialization function.
 * Opens a file and write the date of the execution of the test suite
 * Returns the zero on success, non-zero otherwise.
 */
int init_suite(void){
    error = (Error*) malloc(sizeof(Error));
    system("date");
    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
    free(error);
    return 0;
}

/************* TESTS *************/
void test_read_file_char_is_invalid(void)
{
    char resolved_path[PATH_MAX];
    realpath("test-files/board-invalid-char", resolved_path);
    FILE *fp = fopen(resolved_path, "r");
    CU_ASSERT_FALSE(check_file(fp,error))
    fclose(fp);
    free(fp);
}

void test_read_file_dimensions_are_invalid(void)
{
    char resolved_path[PATH_MAX];
    realpath("test-files/board-invalid-dimensions", resolved_path);
    FILE *fp = fopen(resolved_path, "r");
    CU_ASSERT_FALSE(check_file(fp,error));
    fclose(fp);
    free(fp);
}

void test_read_file_board_is_valid(void)
{
    char resolved_path[PATH_MAX];
    realpath("test-files/board-valid", resolved_path);
    FILE *fp = fopen(resolved_path, "r");
    CU_ASSERT(check_file(fp,error));
    fclose(fp);
    free(fp);
}

void test_adding_already_existing_points(void)
{
    Board* pboard = (Board*) malloc(sizeof(Board));
    *pboard = create_empty_board(10,10);
    int* point = (int*) malloc(sizeof(int));
    *point =1;
    pboard->points[0][0] = point;
    Coord* coord = (Coord*) malloc(sizeof(Coord));
    coord->x = 0;
    coord->y = 0;
    CU_ASSERT_EQUAL(add_point(pboard,*coord),false);
    free_board(pboard);
    free(coord);
    free(point);
}

void test_creating_empty_board(void){
    Board* pboard = (Board*) malloc(sizeof(Board));
    *pboard = create_empty_board(300,300);
    CU_ASSERT_NOT_EQUAL(pboard,NULL);
    CU_ASSERT_EQUAL(pboard->height,300);
    CU_ASSERT_EQUAL(pboard->width,300);
    free(pboard);
}

void test_is_move_valid(void){
    /*TODO :2 Cases
     * - invalid move
     * - valid move
     */
}

int main(void)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    /* add a suite to the registry */
    pSuite = CU_add_suite("Board_suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if((NULL == CU_add_test(pSuite, "Read_board_file_invalid_char", test_read_file_char_is_invalid))
        ||
        (NULL == CU_add_test(pSuite, "Read_board_file_dimensions_invalid", test_read_file_dimensions_are_invalid))
        ||
        (NULL == CU_add_test(pSuite, "Read_board_valid", test_read_file_board_is_valid))
        ||
        (NULL == CU_add_test(pSuite, "Adding_already_existing_points", test_adding_already_existing_points))
        ||
        (NULL == CU_add_test(pSuite, "Adding_already_existing_points", test_creating_empty_board)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}