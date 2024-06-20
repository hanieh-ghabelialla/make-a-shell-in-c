//execute.c module is one the most important part of our implementation
#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
int last(int *numargs, char **args)
{
  if (args[*numargs - 1][0] == '&')
  {
    *numargs = *numargs - 1;
    args[*numargs] = NULL;
    return BG;
  }
  return FG; //*return FG or BG defined not shell.h*/
}

//detect pipe symbol in array of Strings return its index or -1 if it does not exist
int containsPipe(int numArgs, char **args)
{
  int index;
  for (index = 0; index < numArgs; index++)
    if (args[index][0] == '|')
    {
      return index;
    }
  return -1;
}
// the work of below function is handeling signals
void sighandler(int signum)
{
   // if the users press control z do the following instruction
    signal(SIGTSTP, sighandler);
//here i tried to make a prompt just like the sample program that professor uploaded on d2l
    printf("job suspended. Type 'fg' to resume.\n");
    int sleep_pid = getpid();
    printf("my pid : %d \n",sleep_pid);
    //kill(getpid(),SIGINT);
}

void execute(int numargs, char **args)
{
  
  
  int pid, pidFilho, status, fd[2];
// determine foreground or background
  int code = last(&numargs, args);
 
  if ((pid = fork()) < 0)
  {                  
    perror("forks");
    exit(1);         
  }                  

  if (pid == 0) //child
  {
    printf(" will run ");
//if the user press control z go to sighandler
    signal(SIGTSTP, sighandler);
    int indice = containsPipe(numargs, args);
// if we do not have pipes
    if (indice == -1)
    {
      redirects(numargs, args);
      execvp(*args, args);
    }
//if we have pipes 
    if (indice > 0)
    {
//dividing the string into two parts before the pipe and after the pipe
      args[indice] = NULL;
      pipe(fd);
      pidFilho = fork();
      if (pidFilho == 0)
      { // write
        numargs = indice;
       
        redirects(numargs, args);
       
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
      }
      else
      { // read
        args = args + indice + 1;
        numargs = numargs - indice - 1;
        redirects(numargs, args);
        dup2(fd[0], STDIN_FILENO); 
        close(fd[1]);
        close(fd[0]); 
      }
      execvp(*args, args);
    }
    //     command1 | command2
//main parent ======time============>
    //    |
    //parent==========time=========>
    //   |
    //=======
    //  |   |
    //pid   pidFilho===========time===========>

    execvp(*args, args);
    perror(*args);
    exit(1);
  }

  

  if (FG == code)
    while (wait(&status) != pid);



  return;
}
