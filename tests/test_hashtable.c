#include "hashtable/hashtable.h"
#include <stdlib.h>
#include <assert.h>

struct test_t {
    int a;
    int b;
};

void test_hashtable_basic_operations() {
    // Initialize the hash table
    HtTable *map = malloc(sizeof(HtTable));
    assert(map != NULL);
    ht_init_table(map, 4);

    struct test_t test1 = {1, 2};
    struct test_t test2 = {3, 4};

    // Insert elements
    ht_insert(map, "Test1", &test1);
    ht_insert(map, "Test2", &test2);

    // Verify elements were inserted
    assert(ht_search(map, "Test1") != NULL);
    assert(ht_search(map, "Test2") != NULL);
    
    // Validate that the pointers returned are the same as inserted
    assert(ht_search(map, "Test1") == &test1);
    assert(ht_search(map, "Test2") == &test2);
    
    // Verify the element count is correct
    assert(map->element_count == 2);
    
    // Clean up
    ht_deinit_table(map);
    free(map);
}

void test_hashtable_duplicate_insertions() {
    HtTable *map = malloc(sizeof(HtTable));
    assert(map != NULL);
    ht_init_table(map, 4);

    struct test_t test1 = {1, 2};
    
    // Insert element
    ht_insert_s(map, "Test1", 5, &test1);
    assert(map->element_count == 1);
    
    // Insert the same element again
    ht_insert_s(map, "Test1", 5, &test1);
    assert(map->element_count == 2); // Count should remain the same
    assert(ht_search(map,"Test1") == &test1); // Check data consistency

    ht_deinit_table(map);
    free(map);
}

void test_hashtable_deletion() {
    HtTable *map = malloc(sizeof(HtTable));
    assert(map != NULL);
    ht_init_table(map, 4);

    struct test_t test1 = {1, 2};
    
    // Insert the element
    ht_insert_s(map, "Test1", 5, &test1);
    assert(map->element_count == 1);
    
    // Now delete the inserted element
    ht_delete(map, "Test1");
    assert(ht_search(map, "Test1") == NULL); // Should not find the deleted element
    assert(map->element_count == 0); // Count should be 0

    ht_deinit_table(map);
    free(map);
}

void run_tests() {
    test_hashtable_basic_operations();
    test_hashtable_duplicate_insertions();
    test_hashtable_deletion();
}

int main() {
    run_tests();
    return 0;
}
