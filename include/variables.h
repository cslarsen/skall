#include <stddef.h>

char* cgetvar(const char* key);
void csetvar(const char* key, const char* value);

int ngetvar(const char* key);
void nsetvar(const char* key, int value);

void initvars();
