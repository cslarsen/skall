#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "skall.h"
#include "builtins.h"

static const char* BUILTINS[] = {
  "$?",
  "cd",
  "exit",
  "help",
};

int isbuiltin(const char* s)
{
  for ( int n=0; n<sizeof(BUILTINS)/sizeof(char*); ++n )
    if ( !strcmp(BUILTINS[n], s) )
      return 1;
  return 0;
}

void exec_builtin(const char* cmd, char* const* argv)
{
  if ( !strcmp("cd", cmd) ) {
    const char *path = !argv[1]? getenv("HOME") : argv[1];
    fprintf(stderr, "chdir to '%s'\n", path);
    chdir(path);
  } else if ( !strcmp("help", cmd) ) {
    fprintf(stderr, "skall is a minimal, experimental unix shell\n\n");
    fprintf(stderr, "builtin commands:\n");

    for ( int n=0; n<sizeof(BUILTINS)/sizeof(char*); ++n )
      fprintf(stderr, "%s ", BUILTINS[n]);

    fprintf(stderr, "\n");
  } else if ( !strcmp("$?", cmd) ) {
    printf("%d\n", last_exit_status);
  } else if ( !strcmp("exit", cmd) ) {
    exit(0);
  }
}

