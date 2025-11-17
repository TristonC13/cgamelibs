#ifndef BTREE_H
#define BTREE_H

#include "vector/vector.h"
#include <stddef.h>
#include <string.h>

/*  Generic btree macro
 *
 *  Usage:
 *      DEF_BTREE(int, IntVec)
 *
 *  Generates:
 *      typedef struct { int *data; size_t capacity; size_t count; } IntVec;
 *      void IntVec_init(IntVec *btr, size_t initial_capacity);
 *      void IntVec_deinit(IntVec *btr);
 *      void IntVec_realloc(IntVec *btr, size_t new_capacity);
 *      void IntVec_push_back(IntVec *btr, int value);
 *      int  IntVec_pop_back(IntVec *btr, int *out);
 */

typedef enum IterDirection {
	BTREE_LEFT = 0,
	BTREE_RIGHT = 1,
} IterDirection;

#define DEF_BTREE(VAL_T, BTREE_T)                                                                                      \
                                                                                                                       \
	/* btree node struct */                                                                                            \
	typedef struct BTREE_T##_node {                                                                                    \
		struct BTREE_T##_node *pchildren[2];                                                                           \
		struct BTREE_T##_node *pparent;                                                                                \
		VAL_T				   value;                                                                                  \
	} BTREE_T##_node;                                                                                                  \
                                                                                                                       \
	DEF_VECTOR(struct BTREE_T##_node *, BTREE_T##_pnode_stack);                                                        \
                                                                                                                       \
	typedef struct BTREE_T##_iterator {                                                                                \
		BTREE_T##_pnode_stack stack;                                                                                   \
		BTREE_T##_node		 *current;                                                                                 \
	} BTREE_T##_iterator;                                                                                              \
                                                                                                                       \
	static inline void BTREE_T##_iterator_init(BTREE_T##_iterator *iter, BTREE_T##_node *start) {                      \
		BTREE_T##_pnode_stack_init(&iter->stack, 8);                                                                   \
		iter->current = start;                                                                                         \
	}                                                                                                                  \
                                                                                                                       \
	static inline void BTREE_T##_iterator_deinit(BTREE_T##_iterator *iter) {                                           \
		BTREE_T##_pnode_stack_deinit(&iter->stack);                                                                    \
		iter->current = NULL;                                                                                          \
	}                                                                                                                  \
                                                                                                                       \
	/* initialise */                                                                                                   \
	static inline void BTREE_T##_node_init(BTREE_T##_node *btr) {                                                      \
		btr->pchildren[0] = NULL;                                                                                      \
		btr->pchildren[1] = NULL;                                                                                      \
		btr->pparent = NULL;                                                                                           \
	}                                                                                                                  \
                                                                                                                       \
	static inline void BTREE_T##_node_parent_to(BTREE_T##_node *node, BTREE_T##_node *new_parent, IterDirection dir) { \
		node->pparent = new_parent;                                                                                    \
		new_parent->pchildren[dir] = node;                                                                             \
	}                                                                                                                  \
                                                                                                                       \
	/* initialise with value */                                                                                        \
	static inline void BTREE_T##_node_init_t(BTREE_T##_node *btr, VAL_T value) {                                       \
		btr->pchildren[0] = NULL;                                                                                      \
		btr->pchildren[1] = NULL;                                                                                      \
		btr->pparent = NULL;                                                                                           \
		btr->value = value;                                                                                            \
	}                                                                                                                  \
                                                                                                                       \
	/* user defined comparator */                                                                                      \
	/* if pnode_a < pnode_b, then the return value shall be negative */                                                \
	static int BTREE_T##_node_cmp(BTREE_T##_node *pnode_a, BTREE_T##_node *pnode_b);                                   \
                                                                                                                       \
	static int BTREE_T##_iter_parent(BTREE_T##_iterator *iter) {                                                       \
		struct BTREE_T##_node *p;                                                                                      \
		BTREE_T##_pnode_stack_pop_back(&iter->stack, &p);                                                              \
		if (p != NULL) {                                                                                               \
			iter->current = p;                                                                                         \
			return 1;                                                                                                  \
		}                                                                                                              \
		return 0;                                                                                                      \
	}                                                                                                                  \
                                                                                                                       \
	static int BTREE_T##_iter_child(BTREE_T##_iterator *iter, IterDirection direction) {                               \
		struct BTREE_T##_node *pnext = iter->current->pchildren[direction];                                            \
		if (pnext) {                                                                                                   \
			BTREE_T##_pnode_stack_push_back(&iter->stack, iter->current);                                              \
			iter->current = pnext;                                                                                     \
			return 1;                                                                                                  \
		} else {                                                                                                       \
			return 0;                                                                                                  \
		}                                                                                                              \
	}

#endif /* BTREE_H */