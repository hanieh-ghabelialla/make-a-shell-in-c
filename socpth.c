#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void *socpwrapper(void *args)
{
  copy_t *ptr = (copy_t *)args;
  socp(ptr->source, ptr->destiny);
  free(ptr);
  return NULL;
}