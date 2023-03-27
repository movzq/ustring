#include "ustring.h"
#include <stdio.h>

struct ustr* ustr_make ()
{
    struct ustr* ust = (struct ustr*) malloc(sizeof(struct ustr));
    ust->data = (char*) malloc(1);
    ust->size = 0;

    ust->data[0] = '\0';
    return ust;
}

void ustr_pushBack (struct ustr* ust, const char p)
{
    assert(ust != NULL);
    ust->data = (char*) realloc(ust->data, ust->size + 2);
    ust->data[ust->size] = p;
    ust->data[ust->size + 1] = '\0';
    ust->size++;
}

void ustr_append (struct ustr* ust, const char* new)
{
    assert(ust != NULL);
    assert(new != NULL);

    size_t ssz = strlen(new);
    ust->data = (char*) realloc(ust->data, ust->size + ssz + 1);
    ust->data = strcat(ust->data, new);
    ust->size += ssz;
}

void ustr_clear (struct ustr* ust)
{
    assert(ust != NULL);

    free(ust->data);
    ust->data = (char*) malloc(1);
    ust->size = 0;
    ust->data[0] = '\0';
}

void ustr_erase (struct ustr* ust, size_t bgn, size_t end)
{
    assert(ust != NULL);
    assert(bgn >= 0);
    assert(end >= 0);
    assert(bgn <= end);
    assert(end < ust->size);

    if ( !bgn && end == ust->size )
    {
        ustr_clear(ust);
        return;
    }

    /* Saves all character that are after 'e' position not
     * \0 including. */
    char* chrsleft = (char*) malloc(ust->size - end - 1);
    for (size_t i = end + 1, j = 0; i < ust->size; i++)
    {
        chrsleft[j++] = ust->data[i];
    }

    /* Since all characters in range [b, e] was removed
     * the new end is set to 'b' position and then
     * just add the 'chrsleft'. */
    ust->data[bgn] = '\0';
    ust->size = ust->size - (end - bgn) - 1;
    ust->data = (char*) realloc(ust->data, ust->size + 1);
    ust->data = strcat(ust->data, chrsleft);
}

void ustr_popback (struct ustr* ust)
{
    assert(ust != NULL);
    assert(ust->size >= 1);

    ust->data[--ust->size] = '\0';
    ust->data = (char*) realloc(ust->data, ust->size);
}

bool ustr_isLike (struct ustr* ust, const char* with, const enum ustrPos type)
{
    assert(ust != NULL);
    assert(with != NULL);

    size_t nchrswith = strlen(with);
    if ( nchrswith >= ust->size ) { return false; }

    char* islike = (char*) malloc(nchrswith);
    size_t skipchrs = (type == USTR_BEGS) ? 0 : (ust->size - nchrswith);
    strncpy(islike, ust->data + skipchrs, nchrswith);

    bool same = (strcmp(islike, with)) ? false : true;
    free(islike);
    return same;
}

int main ()
{
    return 0;
}
