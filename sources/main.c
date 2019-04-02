#include "../headers/board.h"
#include "../headers/interface.h"
#include "../headers/history.h"
#include<stdio.h>                                                               
#include<stdlib.h>                                                              
#include<unistd.h>                                                              
#include<sys/types.h>                                                           
#include<sys/stat.h>                                                            
#include<fcntl.h>                                                               
#include<string.h>                                                              
#include<errno.h>  
#include <time.h>                                                             
                                                                                
int main(int argc, char* argv[]){   
  srand(time(NULL));
  /* If user gives more than 2 arguments */                                             
  if (argc>3){
    fprintf(stderr,"%s:FATAL: %d invalid nber of args (no more than two expected)\n",argv[0],argc-1);
    return EXIT_FAILURE;
  }
  Board board;
  /* If user does not give any argument */
  if (argc == 1){
    board = initialize_rand();
  }
  else{
    /* If first argument is neither option -r and -h  
    OR 
    first argument is option -r but is not followed by a parameter */
    if ((strcmp(argv[1],"-r")!=0 && strcmp(argv[1],"-h")!=0)||(strcmp(argv[1],"-r")==0 && argc==2)){
      fprintf(stderr,"%s:FATAL: %s invalid args (none, -r FILE or -h expected) \n",argv[0],argv[1]);
      return EXIT_FAILURE;
    }
    /* If first argument is option -h */
    if (strcmp(argv[1],"-h")==0){
      /*print_help();*/
      return EXIT_SUCCESS;
    }
    else{
      /* If file given as a parameter (following option -r) is invalid */
      if (0){ /*(!read_file(pboard,argv[2])){*/
        return EXIT_FAILURE;
      }
    }
  }
  bool hint = false;
  /* Loop termination : board size is finite therefore number of playable moves if finite */
  initialize_HistoryList();
  initialize_LinesList();
  /* Declare a new unallocated pointer: it will be allocated if required and manipulated in functions */
  enum action playerAction = PLAY_MOVE;
  int i=0;
  while(i<1)/*(!is_game_over(&board))  erreurs de segmentation résolus jusqu'ici */
  {
    print_board(&board, hint);
    playerAction = select_action();
    execute_action(&board, playerAction);
    i++;
  }
  /* Free all allocated pointers */
  free_history();
  remove_points(&board);
  free_board(&board);
  return EXIT_SUCCESS;
}
      
   
 
      
      
    
  
  
