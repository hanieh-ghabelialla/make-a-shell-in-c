#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <signal.h>

#define SIGHUP  1   /* Hangup the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */





long int findSize(char file_name[]);

void  notice(char *mesg, int time);

void * noticewrapper(void *args);

void *socpwrapper(void *args);

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin(char **args, int numargs);

void socp(char *source, char *destiny);

void ioCopy(int IN, int OUT);

int redirects(int numargs, char *args[]);

void lists(char *pasta);

typedef struct
{
  char msg[100];
  int time;
}  notice_t;

typedef struct
{
  char source[100];
  char destiny[100];
} copy_t;

#define BG 0
#define FG 1
