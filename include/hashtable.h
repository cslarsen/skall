#include <stddef.h>
#include <inttypes.h>
#include "buffer.h"

struct hashtable {
  struct element** table;
  size_t capacity;
  size_t elements;
  uint32_t (*hash)(const char* key);
};

/*
 * Create a new hash table.
 */

struct hashtable* ht_new(size_t initial_size);

/*
 * Delete hash table.
 */
void ht_free(struct hashtable*);

/*
 * Add object into table.
 */
void ht_set(struct hashtable*, const char* key, struct buffer*);

/*
 * Retrieve object in table, or NULL if not found.
 */
struct buffer* ht_get(struct hashtable*, const char* key);
