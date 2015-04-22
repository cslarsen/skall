#include "hash.h"

/*
 * Simple hash by Daniel J. Bernstein,
 * http://www.cse.yorku.ca/~oz/hash.html
 *
 * This is a simple and fast hash algorithm,
 * but not good on collisions.  It should suffice for
 * small hash table sizes, though.
 */
static uint32_t hash_djb2(const char* s)
{
  uint32_t r = 5381, c;

  while ( (c = *s++) != 0 )
    r += (r<<5) + c;

  return r;
}

uint32_t hash(const char* s)
{
  // Call the default hash algorithm
  return hash_djb2(s);
}
