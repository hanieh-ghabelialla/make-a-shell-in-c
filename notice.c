#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void  notice(char *mesg, int time)
{
  while (time > 0)
  {
    sleep(1);
    time--;
  }
  fprintf(stderr, " notice : %s\n", mesg);
}

void * noticewrapper(void *args)
{
   notice_t *ptr = ( notice_t *)args;
   notice(ptr->msg, ptr->time);
  free(ptr);
  return NULL;
}
