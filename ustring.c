#include "ustring.h"
#include <stdio.h>

struct ustr* ustr_make ()
{
    struct ustr* sst = (struct ustr*) malloc(sizeof(struct ustr));
    sst->data = (char*) malloc(1);
    sst->size = 0;

    sst->data[0] = '\0';
    return sst;
}

void ustr_pushback (struct ustr* sst, const char p)
{
    sst->data = (char*) realloc(sst->data, sst->size + 2);
    sst->data[sst->size] = p;
    sst->data[sst->size + 1] = '\0';
    sst->size++;
}

void ustr_append (struct ustr* sst, const char* a)
{
    size_t ssz = strlen(a);
    sst->data = (char*) realloc(sst->data, sst->size + ssz + 1);
    sst->data = strcat(sst->data, a);
    sst->size += ssz;
}

int main ()
{
    return 0;
}
