#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "hashtable.h"

static hashtable_t *vars = NULL;

void initvars()
{
  /*
   * 127 is a nice number, as well as the 4th Mersenne prime
   */
  vars = ht_new(127);
}

void setvar(const char* k, void* v)
{
  ht_set(vars, k, v);
}

void csetvar(const char* k, const char* v)
{
  ht_set(vars, k, (void*) v);
}

char* cgetvar(const char* k)
{
  return (char*) ht_get(vars, k);
}

void nsetvar(const char* k, int v)
{
  ht_set(vars, k, (void*) v);
}

int ngetvar(const char* k)
{
  return (int) ht_get(vars, k);
}
