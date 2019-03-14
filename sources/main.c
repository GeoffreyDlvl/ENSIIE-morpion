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
                                                                                
int main(int argc,char* argv[]){                                                
  if (argc>3){
    fprintf(stderr,"%s:FATAL: %d invalid nber of args (no more than two expected)\n",argv[0],argc);
    return EXIT_FAILURE;
  }
  Board* pboard=NULL;
  if (argc == 1){
    pboard = initialize_rand();
  }
  else{
    if ((strcmp(argv[1],"-r")!=0 && strcmp(argv[1],"-h")!=0)||(strcmp(argv[1],"-r")==0 && argc==2)){
      fprintf(stderr,"%s:FATAL: %s invalid args (none, -r FILE or -h expected) \n",argv[0],argv[1]);
      return EXIT_FAILURE;
    }
    if (strcmp(argv[1],"-h")==0){
      print_help();
      return EXIT_SUCCESS;
    }
    else{
      if (!read_file(pboard,argv[2])){
        return EXIT_FAILURE;
      }
    }
  }
  bool hint = false;
  /*Loop termination : board size is finite therefore number of playable moves if finite*/
  while(!is_game_over(pboard))
  {
    /* Declare a new NULL pointer: it will be manipulated in functions */
    Pcoord pcoord = NULL;
    print_board(pboard, hint);
    enum action playerAction = select_action(pboard, pcoord, &hint);
    execute_action(pboard, playerAction, pcoord);

    /* If pointer is still NULL, i.e. a move has not been set,
    then free the pointer.*/
    if (pcoord == NULL)
      free (pcoord);
  }
  return EXIT_SUCCESS;
}
      
   
 
      
      
    
  
  
