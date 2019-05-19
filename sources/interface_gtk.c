#include "../headers/history.h"
#include "../headers/interface.h"

#include <gtk-3.0/gtk/gtk.h>
#include "../gtk-gui/gui.h"
#include "../gtk-gui/canvas.h"



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <linux/limits.h>
#include <string.h>

/* Colors and effects support */
#define RESET   "\033[0m"
#define RED     "\033[31m"              /* Red */
#define BOLDRED     "\033[1m\033[31m"   /* Bold Red */
#define LIGHTYELLOW "\033[93m"          /* Light Yellow */
#define LIGHTGREEN   "\033[92m"         /* Light Green */
#define BLINK   "\033[5m"               /* Blinking effect */

#define HORIZONTAL 0
#define VERTICAL 1
#define DIAG_UP 2
#define DIAG_DOWN 3


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
    // Unused
}

/*@requires pboard not null
  @assigns nothing
  @ensures prints board, shows possible moves if hint set to true */
void print_board(Board* pboard)
{
    // Unused
}

void add_line_to_board(Error err,Interface* interface)
{
    if (err == NO_ERR)
        gui_addLines(interface->gui,&line,1);
}


Coord select_move(void)
{
    // NOT IMPLEMENTED
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
            break;
    }
}

void print_help(Interface *interface)
{
    gui_error(interface->gui,"------- HELP -------\n\n"
                             "> The goal is to add points on the board.\n"
                             "> A point can be added to the board if it creates a line of 5 points vertically, horizontally or diagonally.\n"
                             "> Two lines can't have more than one point in common.\n\n");
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
    /* NOT IMPLEMENTED */
}


void display_logo(void){
    /* NOT IMPLEMENTED */
}

void clear_screen(void){
    /* NOT IMPLEMENTED */
}

void press_enter_to_continue(void){
    /* NOT IMPLEMENTED */
}

void print_error(Error err, Interface* interface) {
    switch (err) {
        case WRONG_INPUT_ERR:
            gui_error(interface->gui, "Wrong input.");
            break;
        case FILE_PTR_ERR:
            gui_error(interface->gui, "File could not be opened.");
            break;
        case FILE_DIMENSION_ERR:
            gui_error(interface->gui, "File error: board width must be equal for each line.");
            break;
        case FILE_UNKNOWN_CHAR_ERR:
            gui_error(interface->gui, "File error: unknown character.");
            break;
        case POINT_ALREADY_EXIST_ERR:
            gui_error(interface->gui, "This point already exists.");
            break;
        case INVALID_COORDINATES_ERR:
            gui_error(interface->gui, "Coordinates are invalid.");
            break;
        case ALIGNMENT_ERR:
            gui_error(interface->gui, "No valid alignment.");
            break;
        case CANCEL_ERR:
            gui_error(interface->gui, "Cannot cancel: no move to cancel.");
            break;
        case REPLAY_ERR:
            gui_error(interface->gui, "Cannot replay: no move has been cancelled.");
            break;
        default:
            gui_error(interface->gui, "Undefined error (requires implementation).");
            exit(EXIT_FAILURE);
            break;
    }
}

void print_game_over(void) {
    /* NOT IMPLEMENTED */
}

void print_score(Interface* interface) {
    gui_error(interface->gui, "Game over: score is %i", get_points_scored());
}

void redraw(Board* pboard,Interface* interface){
    char s[MAX_INPUT];
    sprintf(s , "%d" ,get_points_scored());
    changeLabelText(interface->gui,s);
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
                points->x = j;
                points->y = i;
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
                else{
                    if(abs(line.p2.x-line.p1.x)+1 != 5 &&
                        abs(line.p2.y-line.p1.y)+1 != 5 )
                    {
                        gui_error(interface->gui, "Line must be of length 5");
                        *error = ALIGNMENT_ERR;
                        return;
                    }
                    Tint2 segPoints[5];
                    gui_getPointsOfSegment(segPoints,5,line);
                    int i;
                    Coord coord;
                    for(i=0 ; i<5 ; ++i) {
                        coord.x = segPoints[i].x;
                        coord.y = segPoints[i].y;
                        coord.previous = NULL;
                        if(!is_move_exists_already(pboard, coord))
                        {
                            break;
                        }
                    }

                    /*
                    coord.x = line.p2.x;
                    coord.y = line.p2.y;
                    coord.previous = NULL;
                    if(is_move_exists_already(pboard, coord)) {
                        coord.x = line.p1.x;
                        coord.y = line.p1.y;
                        coord.previous = NULL;
                    }*/
                    play_move(pboard,coord,error);
                }
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
                *quit = true;
                break;
            default:
                fprintf(stderr,"unexpected action\n");
        }

    }

void free_interface(Interface* interface){
    free(interface);
}