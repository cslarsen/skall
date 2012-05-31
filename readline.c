#ifdef USE_READLINE
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

void init_readline()
{
  // for .inputrc customization
  rl_readline_name = strdup("skall");
}

#endif
