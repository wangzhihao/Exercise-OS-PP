#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  FILE *file = fopen("./touch.txt", "r");

  pid_t cid = fork();
  
  if(cid == -1){
    perror("fork failed.");
    exit(EXIT_FAILURE);  
  }

  if(cid==0){
    printf("This is the child process.\n");
    int ret = unlink("./touch.txt");
    printf("the return value: %d\n", ret);
  }else{
     int status; 
     pid_t w = wait(&status); 
     printf("This is the parent process, who is waiting the child.\n");
     fprintf(file, "OK");
     sleep(5);
     printf("wake up\n");
     if(w == -1){
      perror("wait failed.");
      exit(EXIT_FAILURE);
     }
  }

  
}
