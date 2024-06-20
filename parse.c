#include "shell.h"
//here i used strtok_r as the assignmnet want
int parse (char *buf, char **args)
{
    int cnt = 0;

    char* token;
    char* rest = buf;
    while ((token = strtok_r(rest, " \0 \t", &rest)))
    {
      //printf("%s\n", token);
      *args++ = token;
      cnt++;     
    }
 
  return cnt;
}
