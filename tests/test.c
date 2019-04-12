#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "linux/limits.h"
#include "../headers/board.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
/*    if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
        return -1;
    }
    else {
        return 0;
    }*/
    return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
/*    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }*/
    return 0;
}

/************* TESTS *************/
void test_read_file_char_is_invalid(void)
{
    char resolved_path[PATH_MAX];
    realpath("test/test-files/board-char-invalid", resolved_path);
    FILE *fp = fopen(resolved_path, "r");
    CU_ASSERT_FALSE(check_file(fp));
}

void test_read_file_dimensions_are_invalid(void)
{
    char resolved_path[PATH_MAX];
    realpath("test/test-files/board-dimensions-invalid", resolved_path);
    FILE *fp = fopen(resolved_path, "r");
    CU_ASSERT_FALSE(check_file(fp));
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
    if( (NULL == CU_add_test(pSuite, "Read_board_file_invalid_char", test_read_file_char_is_invalid))
        ||
        (NULL == CU_add_test(pSuite, "Read_board_file_dimensions_invalid", test_read_file_dimensions_are_invalid))
        ||
        (NULL == CU_add_test(pSuite, "Adding_already_existing_points", test_adding_already_existing_points)))
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