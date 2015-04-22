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
  ht_set(vars, k, v);
}

void csetvar(const char* k, const char* v)
{
  ht_set(vars, k, make_buffer(v, 1+strlen(v)));
}

char* cgetvar(const char* k)
{
  return ht_get(vars, k)->ptr;
}

void nsetvar(const char* k, int v)
{
  ht_set(vars, k, make_buffer(&v, sizeof(v)));
}

int ngetvar(const char* k)
{
  struct buffer* b = ht_get(vars, k);

  int v;
  memcpy(&v, b->ptr, sizeof(v));
  return v;
}

void* getvar(const char* k)
{
  return ht_get(vars, k);
}
