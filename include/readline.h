#ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>

void init_readline();

#endif

char* readprompt(FILE*, const char*);
