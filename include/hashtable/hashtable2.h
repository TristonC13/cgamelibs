#ifndef HASHTABLE2_H
#define HASHTABLE2_H

#include "stddef.h"
#include "stdlib.h"

#define DEF_HASHTABLE(KEY_T, VAL_T, TNAME)                                                                             \
	typedef struct TNAME##_node {                                                                                      \
		KEY_T				 key;                                                                                      \
		VAL_T				 value;                                                                                    \
		size_t				 key_hash;                                                                                 \
		struct TNAME##_node *pnext;                                                                                    \
	} TNAME##_node;                                                                                                    \
                                                                                                                       \
	typedef struct {                                                                                                   \
		TNAME##_node **table;                                                                                          \
		size_t		   size;                                                                                           \
	} TNAME;                                                                                                           \
                                                                                                                       \
	void TNAME##_init(TNAME *ht, size_t size) {                                                                        \
		ht->size = size;                                                                                               \
		ht->table = calloc(size, sizeof(TNAME##_node *));                                                              \
	}                                                                                                                  \
                                                                                                                       \
	size_t TNAME##_hash_key(KEY_T key);                                                                                \
                                                                                                                       \
	void TNAME##_insert(TNAME *ht, KEY_T key, VAL_T value) {                                                           \
		size_t		  hashValue = TNAME##_hash_key(key);                                                               \
		size_t		  index = hashValue % ht->size;                                                                    \
		TNAME##_node *newNode = malloc(sizeof(TNAME##_node));                                                          \
		if (!newNode)                                                                                                  \
			return;                                                                                                    \
		newNode->key = key;                                                                                            \
		newNode->value = value;                                                                                        \
		newNode->key_hash = hashValue;                                                                                 \
		newNode->pnext = ht->table[index];                                                                             \
		ht->table[index] = newNode;                                                                                    \
	}                                                                                                                  \
	void TNAME##_delete(TNAME *ht, KEY_T key) {                                                                        \
		size_t		  hashValue = TNAME##_hash_key(key);                                                               \
		size_t		  index = hashValue % ht->size;                                                                    \
		TNAME##_node *current = ht->table[index];                                                                      \
		TNAME##_node *prev = NULL;                                                                                     \
		while (current != NULL) {                                                                                      \
			if (current->key_hash == hashValue && current->key == key) {                                               \
				if (prev) {                                                                                            \
					prev->pnext = current->pnext;                                                                      \
				} else {                                                                                               \
					ht->table[index] = current->pnext;                                                                 \
				}                                                                                                      \
				free(current);                                                                                         \
				return;                                                                                                \
			}                                                                                                          \
			prev = current;                                                                                            \
			current = current->pnext;                                                                                  \
		}                                                                                                              \
	}                                                                                                                  \
                                                                                                                       \
	VAL_T *TNAME##_get(TNAME *ht, KEY_T key) {                                                                         \
		size_t		  hashValue = TNAME##_hash_key(key);                                                               \
		size_t		  index = hashValue % ht->size;                                                                    \
		TNAME##_node *current = ht->table[index];                                                                      \
		while (current != NULL) {                                                                                      \
			if (current->key_hash == hashValue && current->key == key) {                                               \
				return &(current->value);                                                                              \
			}                                                                                                          \
			current = current->pnext;                                                                                  \
		}                                                                                                              \
		return NULL;                                                                                                   \
	}                                                                                                                  \
                                                                                                                       \
	void TNAME##_deinit(TNAME *ht) {                                                                                   \
		for (size_t i = 0; i < ht->size; i++) {                                                                        \
			TNAME##_node *current = ht->table[i];                                                                      \
			while (current != NULL) {                                                                                  \
				TNAME##_node *temp = current;                                                                          \
				current = current->pnext;                                                                              \
				free(temp);                                                                                            \
			}                                                                                                          \
		}                                                                                                              \
		free(ht->table);                                                                                               \
	}

#endif