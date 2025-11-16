#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stddef.h"  // Standard definitions (e.g., size_t)
#include "stdlib.h"  // Memory allocation functions (malloc, free)
#include "string.h"  // String manipulation functions (strcpy)
#include "stdbool.h" // bool type

// Include hash function definition
#include "hashtable/hash.h"

// Memory management macros for simplified allocation and deallocation
#define htmalloc(size) malloc(size)
#define htfree(p) free(p)

// Struct definition for a node in the hash table's linked list
typedef struct HtNode
{
    unsigned char *key;   // Key for the hash table entry
    void *value;          // Value associated with the key
    struct HtNode *pnext; // Pointer to the next node for handling collisions
} HtNode;

// Struct definition for the hash table itself
typedef struct HtTable
{
    HtNode **buckets;       // Array of pointers to linked list heads, representing hash table buckets
    unsigned bucket_count;  // Number of buckets in the hash table
    unsigned element_count; // Current number of elements in the hash table
} HtTable;

// Function prototypes for hash table operations

/**
 * Initializes a hash table with a specified number of buckets.
 *
 * @param tab Pointer to the hash table to be initialized.
 * @param bucket_count Number of buckets to create in the hash table.
 */
void ht_init_table(HtTable *tab, unsigned bucket_count);

/**
 * Inserts a key-value pair into the hash table.
 *
 * @param tab Pointer to the hash table.
 * @param key The key to insert (must be null-terminated).
 * @param value The value associated with the key.
 * @return True if the insertion is successful, false otherwise.
 */
bool ht_insert(HtTable *tab, const unsigned char *key, void *value);

/**
 * Inserts a key-value pair into the hash table, with a given key size
 *
 * @param tab Pointer to the hash table.
 * @param key The key to insert (must be null-terminated).
 * @param keylen The length in bytes of the key (not counting the null terminator).
 * @param value The value associated with the key.
 * @return True if the insertion is successful, false otherwise.
 */
bool ht_insert_s(HtTable *tab, const unsigned char *key, size_t keylen, void *value);

/**
 * Deletes a key-value pair from the hash table.
 *
 * @param tab Pointer to the hash table.
 * @param key The key to delete.
 * @return True if the deletion is successful, false if the key was not found.
 */
bool ht_delete(HtTable *tab, const unsigned char *key);

/**
 * Searches for a value by key in the hash table.
 *
 * @param tab Pointer to the hash table.
 * @param key The key to search for.
 * @return Pointer to the value associated with the key, or NULL if not found.
 */
void *ht_search(HtTable *tab, const unsigned char *key);

/**
 * Deinitializes a hash table and frees its resources.
 *
 * @param tab Pointer to the hash table to deinitialize.
 */
void ht_deinit_table(HtTable *tab);

#endif // HASHTABLE_H