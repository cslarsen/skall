#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "skall.h"
#include "prompt.h"

const char* prompt_fmt = "skall %s$ ";

char* getprompt(const char* fmt)
{
  static char s[MAXPROMPT];
  static char buf[MAXPROMPT];
  char *cwd = getcwd(buf, sizeof(buf));
  sprintf(s, fmt? fmt : prompt_fmt, cwd);
  return s;
}
