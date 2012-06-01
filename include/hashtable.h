#include <stddef.h>
#include <inttypes.h>

typedef struct hashtable_t {
  struct element_t** table;
  size_t capacity;
  size_t elements;
  uint32_t (*hash)(const char* key);
} hashtable_t;

/*
 * Create a new hash table.
 */

hashtable_t* ht_new(size_t initial_size);

/*
 * Delete hash table.
 */
void ht_free(hashtable_t*);

/*
 * Add object into table.
 */
void ht_set(hashtable_t*, const char* key, const void* value);

/*
 * Retrieve object in table, or NULL if not found.
 */
const void* ht_get(hashtable_t*, const char* key);
