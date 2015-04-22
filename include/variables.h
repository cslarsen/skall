#include <stddef.h>
#include "buffer.h"

void setvar(const char* key, struct buffer* value);

char* cgetvar(const char* key);
void csetvar(const char* key, const char* value);

int ngetvar(const char* key);
void nsetvar(const char* key, int value);

void* getvar(const char* key);
void initvars();
