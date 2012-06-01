#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skall.h"
#include "prompt.h"
#include "trim.h"

#ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>

void init_readline()
{
  // for .inputrc customization
  rl_readline_name = strdup("skall");
}

char* readcmd(FILE* f)
{
  return trim(readline(getprompt(NULL)));
}

#else

char* readcmd(FILE* f)
{
  char buf[MAXLINE];
  fgets(buf, sizeof(buf), stdin);
  return strdup(trim(buf));
}

#endif
