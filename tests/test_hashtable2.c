#include <stdio.h>
#include <assert.h>
#include "hashtable/hashtable2.h"

// Hash function for integers
size_t IntHashTable_hash_key(int key) {
    return (size_t) key; // Simple hash for demonstration purposes
}

// Define the hash table for integer key and value
DEF_HASHTABLE(int, int, IntHashTable)

int main() {
    IntHashTable ht;
    IntHashTable_init(&ht, 10);

    // Test insertion
    IntHashTable_insert(&ht, 1, 100);
    IntHashTable_insert(&ht, 2, 200);
    
    // Test retrieval
    int *val1 = IntHashTable_get(&ht, 1);
    assert(val1 != NULL && *val1 == 100);
    
    int *val2 = IntHashTable_get(&ht, 2);
    assert(val2 != NULL && *val2 == 200);

    // Test deletion
    IntHashTable_delete(&ht, 1);
    val1 = IntHashTable_get(&ht, 1);
    assert(val1 == NULL);  // 1 should be deleted

    // Test retrieval for remaining item
    val2 = IntHashTable_get(&ht, 2);
    assert(val2 != NULL && *val2 == 200);

    // Test deinitialization
    IntHashTable_deinit(&ht);

    printf("All tests passed!\n");
    
    return 0;
}
