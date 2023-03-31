#ifndef _USTRING_H
#define _USTRING_H
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

enum ustrPos {
    USTR_ENDS,
    USTR_BEGS
};

struct ustr {
    char* data;
    size_t size;
};

struct ustr* ustr_make ();
void ustr_pushBack (struct ustr*, const char);
void ustr_append (struct ustr*, const char*);
void ustr_clear (struct ustr*);
void ustr_erase (struct ustr*, size_t, size_t);
void ustr_popBack (struct ustr*);
bool ustr_bewith (struct ustr*, const char*, const enum ustrPos);
bool ustr_contains (struct ustr*, const char*);
char* ustr_substring (struct ustr*, size_t, size_t, bool);
void ustr_overwrite (struct ustr*, const char*, size_t);
char ustr_at (struct ustr*, size_t);
void ustr_kill (struct ustr*);

#endif
