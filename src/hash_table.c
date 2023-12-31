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
const int HT_PRIME_1 = 129;
const int HT_PRIME_2 = 257;

/*
    Constructor/Deconstructor
*/

static ht_item *
ht_new_item(const char *key, const char *value)
{
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

/*
    Collision resolve by Double Hashing
*/

static int ht_get_hash(const char *s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

/*
    Methods API: Insert, Search, Delete
*/

void ht_insert (ht_hash_table* ht, const char* key, const char* value) {

    ht_item* item = ht_new_item(key, value);

    int index = ht_get_hash(item->key, ht->size, 0);

    ht_item* cur_item = ht->items[index];

    int i = 1;

    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM)
    {
            // If key is already in the hash table, return value
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }

            index = ht_get_hash(item->key, ht->size, i);

        cur_item = ht->items[index];

        i++;
    }

    ht->items[index] = item;
    ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);

    ht_item* item = ht->items[index];

    int i = 1;

    while (item != NULL) {
        /* account for deleted item  */
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key)) {
                return item->value;
            }
        }

        index = ht_get_hash(key, ht->size, i);

        item = ht->items[index];

        i++;
    }

    return NULL;
}

static ht_item HT_DELETED_ITEM = {NULL, NULL};

void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);

    ht_item* item = ht->items[index];

    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(key, item->key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }

        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];       
    }

    ht->count--;
}