#include <stddef.h>

#define SETVAR(name, value) setvar(name, (void*)value)

void setvar(const char* key, void* value);

char* cgetvar(const char* key);
void csetvar(const char* key, const char* value);

int ngetvar(const char* key);
void nsetvar(const char* key, int value);

void initvars();
