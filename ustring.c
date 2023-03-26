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
    assert(sst);
    sst->data = (char*) realloc(sst->data, sst->size + 2);
    sst->data[sst->size] = p;
    sst->data[sst->size + 1] = '\0';
    sst->size++;
}

void ustr_append (struct ustr* sst, const char* a)
{
    assert(sst);
    assert(a);

    size_t ssz = strlen(a);
    sst->data = (char*) realloc(sst->data, sst->size + ssz + 1);
    sst->data = strcat(sst->data, a);
    sst->size += ssz;
}

void ustr_clear (struct ustr* sst)
{
    assert(sst);
    free(sst->data);
    sst->data = (char*) malloc(1);
    sst->size = 0;
    sst->data[0] = '\0';
}

void ustr_erase (struct ustr* sst, size_t b, size_t e)
{
    assert(sst);
    assert(b >= 0);
    assert(e >= 0);
    assert(b <= e);
    assert(e < sst->size);

    if ( !b && e == sst->size )
    {
        ustr_clear(sst);
        return;
    }

    /* Saves all character that are after 'e' position not
     * \0 including. */
    char* chrsleft = (char*) malloc(sst->size - e - 1);
    for (size_t i = e + 1, j = 0; i < sst->size; i++)
    {
        chrsleft[j++] = sst->data[i];
    }

    /* Since all characters after 'b' was removed
     * the new end is set to 'b' position and then
     * just add the 'chrsleft'. */
    sst->data[b] = '\0';
    sst->size = sst->size - (e - b) - 1;
    sst->data = (char*) realloc(sst->data, sst->size + 1);
    sst->data = strcat(sst->data, chrsleft);
}

int main ()
{
    return 0;
}
