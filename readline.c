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

char* readprompt(FILE* f, const char* promptfmt)
{
  return trim(readline(getprompt(promptfmt)));
}

#else

char* readprompt(FILE* f, const char* promptfmt)
{
  char buf[MAXLINE];
  printf("%s", getprompt(promptfmt));
  fgets(buf, sizeof(buf), stdin);
  return strdup(trim(buf));
}

#endif
