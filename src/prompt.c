#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif

#include "skall.h"
#include "prompt.h"

#ifndef MAXPATHLEN
# define MAXPATHLEN 1024
#endif

// TODO: Make an expand_prompt routine with params, let user set it.
const char* prompt_fmt = "skall %s$ ";

char* getprompt(const char* fmt)
{
  static char s[MAXPROMPT];
  static char buf[MAXPATHLEN];
  char *cwd = getcwd(buf, sizeof(buf));
  sprintf(s, fmt? fmt : prompt_fmt, cwd);
  return s;
}
