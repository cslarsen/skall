#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "hashtable.h"

static struct hashtable *vars = NULL;

void initvars()
{
  /*
   * 127 is a nice number, as well as the 4th Mersenne prime
   */
  vars = ht_new(127);
}

void setvar(const char* k, struct buffer* v)
{
  buffer_free(ht_get(vars, k));
  ht_set(vars, k, v);
}

void csetvar(const char* k, const char* v)
{
  buffer_free(ht_get(vars, k));
  ht_set(vars, k, make_buffer(v, 1+strlen(v)));
}

char* cgetvar(const char* k)
{
  return ht_get(vars, k)->ptr;
}

void nsetvar(const char* k, int v)
{
  buffer_free(ht_get(vars, k));

  // We're lazy; convert to string
  char s[32];
  sprintf(s, "%d", v);
  ht_set(vars, k, make_buffer(s, 1+strlen(s)));
}

int ngetvar(const char* k)
{
  return atoi(ht_get(vars, k)->ptr);
}

void* getvar(const char* k)
{
  return ht_get(vars, k);
}
