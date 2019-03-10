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
    return 1;
  }
  Board* pboard=NULL;
  if (argc == 1){
    pboard = initialize_rand();
  }
  else{
    if ((strcmp(argv[1],"-r")!=0 && strcmp(argv[1],"-h")!=0)||(strcmp(argv[1],"-r")==0 && argc==2)){
      fprintf(stderr,"%s:FATAL: %s invalid args (none, -r FILE or -h expected) \n",argv[0],argv[1]);
      return 1;
      }
    if (strcmp(argv[1],"-h")==0){
      print_help();
      return 0;
    }
    else{
      if (!read_file(pboard,argv[2])){
	return 1;
      }
    }
  }
  int move_number=1;
  while(!is_game_over(pboard)){
    print_board(0,pboard);
    enum action playerAction = select_action(pboard, move_number);
    execute_action(pboard, playerAction);

    if (playerAction == PLAY_MOVE || playerAction == REPLAY_MOVE)
      move_number++;
    else if (playerAction == CANCEL_MOVE)
      move_number--;
  }
  return 0;
}
      
   
 
      
      
    
  
  
