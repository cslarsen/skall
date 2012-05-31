#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include "skall.h"
#include "prompt.h"

char* getprompt(const char* fmt)
{
  static char s[MAXPROMPT];
  char *cwd = getwd(NULL);
  sprintf(s, fmt, cwd);
  free(cwd);
  return s;
}
