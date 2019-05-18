#include "../headers/history.h"
#include "../headers/interface.h"

#include <gtk-3.0/gtk/gtk.h>
#include "../gtk-gui/gui.h"
#include "../gtk-gui/canvas.h"



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/limits.h>

/* Colors and effects support */
#define RESET   "\033[0m"
#define RED     "\033[31m"              /* Red */
#define BOLDRED     "\033[1m\033[31m"   /* Bold Red */
#define LIGHTYELLOW "\033[93m"          /* Light Yellow */
#define LIGHTGREEN   "\033[92m"         /* Light Green */
#define BLINK   "\033[5m"               /* Blinking effect */



static Tint2 points[9999];//    = { { 4,4}, {5,5} };
static Tsegm lines[]     = { { { 6,6}, {6,11} },  { { 6,6}, {11,6} },
                             { { 6,6}, {10,8} }, { { 2,4}, { 6,6} },
                             { { 6,6}, {10,4} }, { { 2,8}, { 6,6} },
};
static Tsegm linesHelp[] = { { { 1,1}, { 1,5} }, { { 1,2}, { 1, 6} },
                             { { 1,3}, { 1,7} }, { { 1,4}, { 1, 8} },
                             { { 1,5}, { 1,9} }, { { 1,6}, { 1,10} },
                             { { 1,1}, { 5,5} }, { { 1,1}, { 5, 1} },
};
static Tgui* gui;
static Tsegm   line;





static bool hint;

void set_hint(bool boolean){
  hint=boolean;
}

bool get_hint(){
  return hint;
}

void set_fullscreen(bool set) {
    /* TO DO */
}

/*@requires pboard not null
  @assigns nothing
  @ensures prints board, shows possible moves if hint set to true */
void print_board(Board* pboard)
{
    gui_redraw(gui);
}


void add_line_to_board(Error err)
{
    if(err == NO_ERR) {
        fprintf(stderr,"no error\n");
        gui_addLines(gui,&line,1);
    } else
        fprintf(stderr,"error\n");
}

Coord select_move(void)
{
    Coord coord;
    coord.x = line.p2.x;
    coord.y = line.p2.y;
    coord.previous = NULL;
    return coord;
}


enum action select_action(void)
{
    switch ( gui_getAction(gui,&line) ) {
        case GUI_ACT_Segment:
            return PLAY_MOVE;
            break;
        case GUI_ACT_Undo:
            return CANCEL_MOVE;
            break;
        case GUI_ACT_Help:
            return ASK_HELP;
            break;
        case GUI_ACT_Quit:
            return QUIT_GAME;
            break;
        default:
            fprintf(stderr,"unexpected action\n");
    }
}

void print_help(void)
{
	/* TO DO */
}

/*@requires pmove not null
  @assings pmove
  @ensures asks player to chose amongst possible lines and frees all those not chosen*/
void select_line(Move* pmove){

}

bool confirm_quit_save(Board* pboard) {
    gui_close(gui);
}


char* ask_savefile_name(void){
    /* TO DO */
}


void display_logo(void){
    /* TO DO */
}

void clear_screen(void){
    /* TO DO */
}

void press_enter_to_continue(void){
    /* TO DO */
}

void print_error(Error err) {
    switch (err) {
        case WRONG_INPUT_ERR:
            fprintf(stderr, RED "Wrong input.\n" RESET);
            break;
        case FILE_PTR_ERR:
            fprintf(stderr, BOLDRED "File could not be opened.\n" RESET);
            break;
        case FILE_DIMENSION_ERR:
            fprintf(stderr, BOLDRED "File error: board width must be equal for each line.\n" RESET);
            break;
        case FILE_UNKNOWN_CHAR_ERR:
            fprintf(stderr, BOLDRED "File error: unknown character.\n" RESET);
            break;
        case POINT_ALREADY_EXIST_ERR:
            fprintf(stderr, BOLDRED "This point already exists.\n" RESET);
            break;
        case INVALID_COORDINATES_ERR:
            fprintf(stderr, BOLDRED "Coordinates are invalid.\n" RESET);
            break;
        case ALIGNMENT_ERR:
            fprintf(stderr, BOLDRED "No valid alignment.\n" RESET);
            break;
        case CANCEL_ERR:
            fprintf(stderr, BOLDRED "Cannot cancel: no move to cancel.\n" RESET);
            break;
        case REPLAY_ERR:
            fprintf(stderr, BOLDRED "Cannot replay: no move has been cancelled.\n" RESET);
            break;
        default:
            fprintf(stderr, RED "Undefined error (requires implementation)." RESET);
            exit(EXIT_FAILURE);
            break;
    }
}

void print_game_over(void) {
    /* TO DO */
}

void print_score(void) {
    /* TO DO */
}

void initPoints(Board* pboard) {
    /*Move current = get_points_history();
    fprintf(stderr, "point : %s %s", current->x, current->y);*/

    //count points
/*    int count = 0;
    int i, j;
    for(i=0 ; i<pboard->width ; ++i)
    {
        for(j=0 ; j<pboard->height ; ++j)
        {
            if (pboard->points[i][j] != NULL) {
                count++;
            }
        }
    }*/

    int i,j,k = 0;
    for(i=0 ; i<pboard->width ; ++i)
    {
        for(j=0 ; j<pboard->height ; ++j)
        {
            if (pboard->points[i][j] != NULL) {
                Tint2 p = {j, i};
                points[k++] = p;
            }
        }
    }
}

void init(Board* pboard)
{
    gui = gui_open(300,20);

    initPoints(pboard);
    gui_addPoints(gui , points , TABLE_NB(points));

    //gui_addLines (gui , lines  , TABLE_NB(lines));

    /*Taction action;
    Tsegm   line;
    Tgui* gui = gui_open(300,20);

    gui_addPoints(gui , points , TABLE_NB(points));
    gui_addLines (gui , lines  , TABLE_NB(lines));

    int fini=0;
    while ( ! fini ) {
        gui_redraw(gui);

        switch ( gui_getAction(gui,&line) ) {
            case GUI_ACT_Segment:
                if ( abs(line.p1.x-line.p2.x)>9||
                     abs(line.p1.y-line.p2.y)>9 )
                    gui_error(gui, "le segment (%d,%d) --> (%d,%d) est invalide",
                              line.p1.x,line.p1.x, line.p2.y,line.p2.y);
                else
                    gui_addLines(gui,&line,1);
                break;
            case GUI_ACT_Undo:
                gui_supLastLine(gui);
                break;
            case GUI_ACT_Help:
                if ( gui_getSegOfSet(gui,linesHelp, TABLE_NB(linesHelp), &line)==GUI_ACT_Quit)
                    goto end;
                gui_addLines(gui,&line,1);
                break;
            case GUI_ACT_Quit:
                fini = 1;
                break;
            default:
                fprintf(stderr,"unexpected action\n");
        }

    }

end:
    gui_close(gui);*/

}