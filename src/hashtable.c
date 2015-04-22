/*
 * An implementation of a separate chaining hash table in C.
 *
 * Put in the public domain by the author, 2012-05-02, 2015
 *
 * Written by Christian Stigen Larsen,
 * http://csl.name
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "hash.h"
#include "buffer.h"

#define MAX_LOAD_FACTOR 0.770523f

struct element {
  struct element* next;
  char* key;
  struct buffer* value;
};

static struct element* el_new(const char* key, struct buffer* value)
{
  struct element *r = (struct element*)malloc(sizeof(struct element));
  r->key = strdup(key);
  r->value = value;
  r->next = NULL;
  return r;
}

static void el_free(struct element* p)
{
  free(p->key);
  buffer_free(p->value);
  free(p);
}

static void ht_check_load(struct hashtable* ht)
{
  float lf = (float) ht->elements / ht->capacity;

  /*
   * If load is too big, grow table by creating a new and copying all
   * elements over.
   */
  if ( lf >= MAX_LOAD_FACTOR ) {
    struct hashtable* htnew = ht_new(2*(1 + ht->capacity) - 1);

    for ( size_t n=0; n < ht->capacity; ++n ) {
      struct element* p = ht->table[n];

      while ( p ) {
        ht_set(htnew, p->key, p->value);
        p = p->next;
      }
    }

    ht_free(ht);
    ht = htnew;
  }
}

struct hashtable* ht_new(size_t initial_size)
{
  if ( initial_size == 0 )
    initial_size = 1;

  struct hashtable *r = (struct hashtable*) malloc(sizeof(struct hashtable));
  r->table = (struct element**) malloc(initial_size*sizeof(struct element*));
  r->elements = 0;
  r->capacity = initial_size;
  r->hash = hash; // use default hash function
  return r;
}

void ht_free(struct hashtable* ht)
{
  for ( size_t n=0; n<ht->capacity; ++n ) {
    if ( ht->table[n] ) {
      struct element *p = ht->table[n];

      while ( p ) {
        struct element *n = p->next;
        el_free(p);
        p = n;
      }
    }
  }
}

void ht_set(struct hashtable* ht, const char* key, struct buffer* value)
{
  uint32_t k = ht->hash(key) % ht->capacity;
  struct element *p = ht->table[k];

  /*
   * Key not in table?  Just add it.
   */
  if ( !p ) {
    ht->table[k] = el_new(key, value);
    ++ht->elements;
    return;
  }

  /*
   * Just do a linear scan for next vacant spot
   */
  for (;;) {

    /*
     * Find object, update count and point to new value.
     */
    if ( !strcmp(p->key, key) ) {
      if ( p->value && !value )
        --ht->elements;
      else if ( !p->value && value )
        ++ht->elements;

      p->value = value;
      return;
    }

    if ( !p->next )
      break;

    p = p->next;
  }

  // add to end of list
  p->next = el_new(key, value);
  ++ht->elements;

  ht_check_load(ht);
}

struct buffer* ht_get(struct hashtable* ht, const char* key)
{
  uint32_t k = ht->hash(key) % ht->capacity;
  struct element *p = ht->table[k];

  while ( p ) {
    if ( !strcmp(p->key, key) )
      break;
    p = p->next;
  }

  return p? p->value : NULL;
}
