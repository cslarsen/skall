#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "hash.h"

#define MAX_LOAD_FACTOR 0.5f

typedef struct element_t {
  struct element_t* next;
              char* key;
        const void* value;
} element_t;

static element_t* el_new(const char* key, const void* value)
{
  element_t *r = (element_t*) malloc(sizeof(element_t));
  r->key   = strdup(key);
  r->value = value;
  r->next  = NULL;
  return r;
}

static void el_free(element_t* p)
{
  free(p->key);
  free(p);
}

static void ht_check_load(hashtable_t* ht)
{
  float lf = (float) ht->elements / ht->capacity;

  /*
   * If load is too big, grow table by creating a new and copying all
   * elements over.
   */
  if ( lf >= MAX_LOAD_FACTOR ) {
    hashtable_t *htnew = ht_new(2*(1 + ht->capacity) - 1);

    for ( int n=0; n < ht->capacity; ++n ) {
      element_t *p = ht->table[n];

      while ( p ) {
        ht_set(htnew, p->key, p->value);
        p = p->next;
      }
    }

    ht_free(ht);
    ht = htnew;
  }
}

hashtable_t* ht_new(size_t initial_size)
{
  if ( initial_size == 0 )
    initial_size = 1;

  hashtable_t *r = (hashtable_t*) malloc(sizeof(hashtable_t));
  r->table = (element_t**) malloc(initial_size*sizeof(element_t*));
  r->elements = 0;
  r->capacity = initial_size;
  r->hash = hash; // use default hash function
  return r;
}

void ht_free(hashtable_t* ht)
{
  for ( size_t n=0; n<ht->capacity; ++n ) {
    if ( ht->table[n] ) {
      element_t *p = ht->table[n];

      while ( p ) {
        element_t *n = p->next;
        el_free(p);
        p = n;
      }
    }
  }
}

void ht_set(hashtable_t* ht, const char* key, const void* value)
{
  uint32_t k = ht->hash(key) % ht->capacity;
  element_t *p = ht->table[k];

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

const void* ht_get(hashtable_t* ht, const char* key)
{
  uint32_t k = ht->hash(key) % ht->capacity;
  element_t *p = ht->table[k];

  while ( p ) {
    if ( !strcmp(p->key, key) )
      break;
    p = p->next;
  }

  return p? p->value : NULL;
}
