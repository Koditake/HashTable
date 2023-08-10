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


/*
    Prototypes
*/

ht_item* ht_new_item(const char* key, const char* value);
ht_hash_table* ht_new();
void ht_del_hash_table(ht_hash_table*);