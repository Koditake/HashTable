/*
    Implemetations
*/

#include <string.h>
#include <stdlib.h>

#include "hash_table.h"

/*
    CONSTANT
*/

const int HT_MAX_SIZE = 53;

/*
    Constructor/Deconstructor
*/

static ht_item* ht_new_item (const char* key, const char* value) {
    ht_item* item = malloc(sizeof(ht_item));

    item->key = key;
    item->value = value;

    return item;
}

ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = HT_MAX_SIZE;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

    return ht;
}

void ht_del_hash_table (ht_hash_table* ht) {
    
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }

    free(ht->items);
    free(ht);
}

/*
    Hashing
*/

static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;

    const int len_s = strlen(s);

    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash %= m;
    }

    return (int)hash;
}