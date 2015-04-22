#ifndef INC_BUFFER_H_2015_04_20
#define INC_BUFFER_H_2015_04_20

#include <stddef.h>
#include <inttypes.h>

struct buffer {
  void* ptr;
  size_t length;
};

void buffer_free(struct buffer*);
struct buffer* make_buffer(const void* ptr, const size_t length);

#endif
