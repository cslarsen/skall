#include <string.h>
#include <stdlib.h>
#include "buffer.h"

void buffer_free(struct buffer* b)
{
  if ( b != NULL ) {
    if ( b->ptr != NULL )
      free(b->ptr);
    free(b);
  }
}

struct buffer* make_buffer(const void* ptr, const size_t length)
{
  struct buffer* b = malloc(sizeof(b));
  b->length = length;
  b->ptr = malloc(b->length);
  memcpy(b->ptr, ptr, b->length);
  return b;
}
