#include <stddef.h>

char* getcvar(const char* key);
void setcvar(const char* key, const char* value);

int getivar(const char* key);
void setivar(const char* key, int value);

void initvars();
