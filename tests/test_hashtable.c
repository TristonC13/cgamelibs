#include "hashtable/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_hashtable()
{
    // Initialize the hash table
    HtTable *map = malloc(sizeof(HtTable));
    assert(map != NULL);  // Ensure allocation was successful
    ht_init_table(map, 16);

    // Insert values
    assert(ht_insert(map, "Yogaholic", "Anjali"));
    assert(ht_insert(map, "pluto14", "Vartika"));
    assert(ht_insert(map, "elite_Programmer", "Manish"));
    assert(ht_insert(map, "GFG", "GeeksforGeeks"));
    assert(ht_insert(map, "decentBoy", "Mayank"));

    // Check insertions
    assert(strcmp((const char *)ht_search(map, "Yogaholic"), "Anjali") == 0);
    assert(strcmp((const char *)ht_search(map, "pluto14"), "Vartika") == 0);
    assert(strcmp((const char *)ht_search(map, "elite_Programmer"), "Manish") == 0);
    assert(strcmp((const char *)ht_search(map, "GFG"), "GeeksforGeeks") == 0);
    assert(strcmp((const char *)ht_search(map, "decentBoy"), "Mayank") == 0);

    // Test for a non-existent key
    assert(ht_search(map, "randomKey") == NULL); // Should return NULL

    // Test deletion
    assert(ht_delete(map, "decentBoy")); // Successful deletion
    assert(ht_search(map, "decentBoy") == NULL); // Should return NULL after deletion

    // Cleanup
    ht_deinit_table(map);
    free(map);
}

int main()
{
    test_hashtable(); // Call the test function
    return 0;
}
