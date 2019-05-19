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
static Tsegm line;

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
    // TO DO
}


void add_line_to_board(Error err,Interface* Interface)
{
    if(err == NO_ERR) {
        fprintf(stderr,"no error\n");
        gui_addLines(Interface->gui,&line,1);
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


enum action select_action(Interface* Interface)
{
    switch (gui_getAction(Interface->gui,&line) ) {
        case GUI_ACT_Segment:
            return PLAY_MOVE;
        case GUI_ACT_Undo:
            return CANCEL_MOVE;
        case GUI_ACT_Help:
            return ASK_HELP;
        case GUI_ACT_Quit:
            return QUIT_GAME;
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

// bool confirm_quit_save(Board* pboard) {
//     gui_close(gui);
// }


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

/*void initPoints(Board* pboard) {


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
}*/

void redraw(Board* pboard,Interface* interface){
    gui_redraw((Tgui*)interface->gui);
}

Interface* init(Board* board)
{
    Interface* gui = (Interface*) malloc(sizeof(Interface));
    gui->gui = gui_open(300,20);
    int i;
    int j;
    for(i = 0 ; i < board->height ; i++ ){
        for (j=0;j<board->width;j++){    
            if(board->points[i][j] != NULL){
                Tint2* points = (Cint2*) malloc( sizeof(Cint2));
                points->x = i;
                points->y = j;
                gui_addPoints(gui->gui , points , TABLE_NB(points));
            }
        }
    }
    return gui; 
}

/*@requires pboard not null
  @assigns pboard
  @ensures executes action of the enum action action*/
void execute_action(Board* pboard,Interface* interface, enum action action, bool* quit, Error* error) {
    switch (action) {
            case PLAY_MOVE:
                if ( abs(line.p1.x-line.p2.x)>9||
                     abs(line.p1.y-line.p2.y)>9 )
                    gui_error(interface->gui, "le segment (%d,%d) --> (%d,%d) est invalide",
                              line.p1.x,line.p1.x, line.p2.y,line.p2.y);
                else
                    gui_addLines(interface->gui,&line,1);
                break;
            case CANCEL_MOVE:
                gui_supLastLine(interface->gui);
                break;
            case ASK_HELP:
                if ( gui_getSegOfSet(interface->gui,linesHelp, TABLE_NB(linesHelp), &line)==GUI_ACT_Quit){
                    gui_close(interface->gui);
                    free_interface(interface);
                }                    
                gui_addLines(interface->gui,&line,1);
                break;
            case QUIT_GAME:
                gui_close(interface->gui);
                free_interface(interface);
                break;
            default:
                fprintf(stderr,"unexpected action\n");
        }

    }

void free_interface(Interface* interface){
    free(interface);
}