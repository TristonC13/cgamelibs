#include "hashtable/hashtable2.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

DEF_HASHTABLE(int, int, StrIntTab);

size_t StrIntTab_hash_key(int key) {
	return (size_t) key;
}

int main(void) {
	StrIntTab t;
	StrIntTab_init(&t, 16);
	StrIntTab_insert(&t, 0, 15);
	printf("%d\n", *StrIntTab_get(&t, 0));

	for (size_t i = 0; i < t.size; ++i) {
		StrIntTab_node *bucket_head = t.table[i];
		if (bucket_head) {
			printf("Bucket #%zu: %p\n", i, bucket_head);

			StrIntTab_node *c = bucket_head;
			while (c) {
				printf("%d = %d (%zu)\n", c->key, c->value, c->key_hash);
				c = c->pnext;
			}
		}
	}

	StrIntTab_delete(&t, 0);
	assert(StrIntTab_get(&t, 0) == NULL);

	StrIntTab_deinit(&t);
}
