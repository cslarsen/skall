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

void csetvar(const char* key, const char* value)
{
  ht_set(vars, key, (void*) value);
}

char* cgetvar(const char* key)
{
  return (char*) ht_get(vars, key);
}

void nsetvar(const char* key, int value)
{
  ht_set(vars, key, (void*) value);
}

int ngetvar(const char* key)
{
  return (int) ht_get(vars, key);
}
