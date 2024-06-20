#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h> 
#include <stdlib.h>
#include  <time.h>
#include "shell.h"
#define BUFFSIZE 128

//In this file, the input and output which are our files are written, 
//in fact, IO in our program is written  in this function, in this file, and in this library.

void socp(char *source, char *destiny){
  int fdIn = open(source, O_RDONLY);
  if(fdIn == -1){ 
    printf("Error Number % d\n", errno);  
    perror("open failed");                 
  }

  int fdOut = creat(destiny, S_IRUSR| S_IWUSR );
  if(fdOut == -1){
    printf("Error Number % d\n", errno);  
    perror("creat failed");  
  }

  ioCopy(fdIn, fdOut);
}

void ioCopy (int IN, int OUT) //no error reporting
{ 
 int n;
 char buf[BUFFSIZE];
 while ( ( n = read (IN, buf, BUFFSIZE)) > 0)
 { 
  if (write (OUT, buf, n) != n)
    perror("Typing error!\n");
 }
 if (n < 0)
  perror("Reading mistake!\n");
}
