typedef struct 
{
    char* key;
    char* value;
} ht_item;

typedef struct 
{
    /* data */
    int count;
    int size;
    ht_item** items;
} ht_hash_table;