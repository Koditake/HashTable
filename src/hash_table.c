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