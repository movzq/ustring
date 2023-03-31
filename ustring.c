#include "ustring.h"

struct ustr* ustr_make ()
{
    struct ustr* ust = (struct ustr*) malloc(sizeof(struct ustr));
    ust->data = (char*) malloc(1);
    ust->size = 0;

    ust->data[0] = '\0';
    return ust;
}

void ustr_pushBack (struct ustr* ust, const char push)
{
    assert(ust);
    ust->data = (char*) realloc(ust->data, ust->size + 2);
    ust->data[ust->size] = push;
    ust->data[++ust->size] = '\0';
}

void ustr_append (struct ustr* ust, const char* new)
{
    assert(ust);
    assert(new);

    size_t ssz = strlen(new);
    ust->data = (char*) realloc(ust->data, ust->size + ssz + 1);
    strcat(ust->data, new);
    ust->size += ssz;
}

void ustr_clear (struct ustr* ust)
{
    assert(ust);

    free(ust->data);
    ust->data = (char*) malloc(1);
    ust->size = 0;
    ust->data[0] = '\0';
}

void ustr_erase (struct ustr* ust, size_t bgn, size_t end)
{
    assert(ust);
    assert(bgn >= 0);
    assert(end >= 0);
    assert(bgn <= end);
    assert(end < ust->size);

    if (!bgn && end == ust->size) {
        ustr_clear(ust);
        return;
    }

    char* chrsleft = (char*) malloc(ust->size - end - 1);
    for (size_t i = end + 1, j = 0; i < ust->size; i++)
        chrsleft[j++] = ust->data[i];

    ust->data[bgn] = '\0';
    ust->size = ust->size - (end - bgn) - 1;
    ust->data = (char*) realloc(ust->data, ust->size + 1);
    strcat(ust->data, chrsleft);
}

void ustr_popback (struct ustr* ust)
{
    assert(ust);
    assert(ust->size >= 1);

    ust->data[--ust->size] = '\0';
    ust->data = (char*) realloc(ust->data, ust->size);
}

bool ustr_bewith (struct ustr* ust, const char* with, const enum ustrPos type)
{
    assert(ust);
    assert(with);

    size_t nchrswith = strlen(with);
    if (nchrswith > ust->size)
        return false;

    char* islike = (char*) malloc(nchrswith);
    size_t skipchrs = (type == USTR_BEGS) ? 0 : (ust->size - nchrswith);
    strncpy(islike, ust->data + skipchrs, nchrswith);

    bool same = (strcmp(islike, with)) ? false : true;
    free(islike);
    return same;
}

bool ustr_contains (struct ustr* ust, const char* str)
{
    assert(ust);
    assert(str);

    size_t sizestr = strlen(str);
    if (sizestr > ust->size)
        return false;

    char* sub = (char*) malloc(sizestr);
    for (unsigned i = 0; i < ust->size; i++) {
        while ( str[0] != ust->data[i] )
            i++;

        strncpy(sub, ust->data + i, sizestr);
        if ( !strcmp(sub, str) )
            return true;
    }
    return false;
}

char* ustr_substring (struct ustr* ust, size_t bgn, size_t end, bool cut)
{
    assert(ust);
    assert(bgn >= 0);
    assert(end >= 0);
    assert(bgn <= end);
    assert(end < ust->size);

    char* substr = (char*) malloc(end - bgn + 1);
    for (size_t i = bgn, j = 0; i <= end; i++)
        substr[j++] = ust->data[i];

    if (cut)
        ustr_erase(ust, bgn, end);
    return substr;
}

void ustr_overwrite (struct ustr* ust, const char* repfor, size_t idx)
{
    assert(ust);
    assert(repfor);
    assert(idx >= 0);
    assert(idx <= ust->size);

    size_t sizerep = strlen(repfor);
    size_t availablechrs = ust->size - idx;

    if (sizerep <= availablechrs) {
        strncpy(ust->data + idx, repfor, sizerep);
        return;
    }

    ust->size += sizerep - availablechrs;
    ust->data = (char*) realloc(ust->data, ust->size);
    strcpy(ust->data + idx, repfor);
}

char ustr_at (struct ustr* ust, size_t pos)
{
    if ( pos >= ust->size )
        return '\0';
    return ust->data[pos];;
}

void ustr_kill (struct ustr* ust)
{
    free(ust->data);
    free(ust);
}
