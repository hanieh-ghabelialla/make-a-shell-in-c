#include "shell.h"
#include <sys/stat.h>
char prompt[100];

int main()
{
  int len;
  char  line[1024];
//show array of characters
  char *args[64]; 

  while (1)
  {
   char cwd[1024]; // showing the curent working directory
//getcwd is an internal function in gcc that read current working directory and store it in cwd 
   if (getcwd(cwd, sizeof(cwd)) != NULL)
   {
      strcpy(prompt,cwd); //copy
//adding % sign to the last of our prompt
      strcat(prompt,"%"); 
   } 
   else {
       perror("getcwd() error");
       return 1;
   }
//showing our prompt
    printf("%s", prompt);
//receiving input and put it in line
    if (fgets( line, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }

    len = strlen( line); //len of line
    if (1 == len)
      continue; 

    if ( line[len - 1] == '\n')
       line[len - 1] = '\0';      // cd /tmp/.... \n ==> cd /tmp/.... \0
//spliting 
    int numargs = parse( line, args); 

//check whether the arguamns are in buitin functions or not

    if (!builtin(args, numargs))
        execute(numargs, args);
   
   
    strcpy(prompt, getenv("PWD"));
    strcat(prompt,"%");

  }
  return 0;
}

int builtin(char **args, int numargs)
{
  if (strcmp(args[0], "exit") == 0)
  {
    exit(0);
    return 1;
  }
  if (0 == strcmp(args[0], "info"))
  {
    printf("it is my simple shell\n");
    return 1; 
  }
  if (strlen(args[0]) > 4 && 0 == strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0] + 4);
    return 1; 
  }
  if (0 == strcmp(args[0], "whoami"))
  {
    system("id");
    return 1;  
  }
  if (0 == strcmp(args[0], "cd"))
  {
     int err;
    if (NULL == args[1] || strcmp(args[1], "~") == 0)
    {
      err = chdir(getenv("HOME") ) ;

    }
    else 
    {
      err = chdir( args[1] );

    }
    if(err<0) perror (args[1]);
    else
    {
        strcpy(prompt, getenv("PWD"));
        strcat(prompt,"%");
    }

    return 1;  
  }
 
  
  if (0 == strcmp(args[0], "socp"))
  {
    socp(args[1], args[2]);
    return 1;  
  }
  if (strcmp(args[0], " notice") == 0)
  {
    pthread_t th;
     notice_t *ptr = ( notice_t *)malloc(sizeof( notice_t));
    strcpy(ptr->msg, args[1]);
    ptr->time = atoi(args[2]);
    pthread_create(&th, NULL,  noticewrapper, (void *)ptr);
    return 1;
  }
  if (strcmp(args[0], "socpth") == 0)
  {
    pthread_t th;
    copy_t *ptr = (copy_t *)malloc(sizeof(copy_t));
    strcpy(ptr->source, args[1]);
    strcpy(ptr->destiny, args[2]);
    pthread_create(&th, NULL, socpwrapper, (void *)ptr);
    return 1;
  }
  
  if (strcmp(args[0], "setx") == 0)
  {
    char command[50] = "chmod u=rxw ";
    strcat(command, args[1]);
    system(command);

    return 1;
  }
  if (strcmp(args[0], "removerl") == 0)
  {
    char command[50] = "chmod go-r ";
    strcat(command, args[1]);
    system(command);

    return 1;
  }
  if (strcmp(args[0], "list") == 0)
  {
     lists(args[1]);

    return 1;
  }
  if (strcmp(args[0], "fg") == 0)
  {
      //kill(sleep_pid,SIGABRT);
    return 1;
  }
  return 0;
}
