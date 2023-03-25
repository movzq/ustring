#ifndef _USTRING_H
#define _USTRING_H
#include <stdlib.h>
#include <string.h>

struct ustr {
    char* data;
    size_t size;
};

struct ustr* ustr_make ();
void ustr_pushback (struct ustr*, const char);
void ustr_append (struct ustr*, const char*);

#endif
