#ifndef LINKED_LIST_DOUBLE_H
#define LINKED_LIST_DOUBLE_H

#include "stdbool.h"
#include <assert.h>
#include <stdlib.h>

#ifdef DEBUG
#define DEBUG_ASSERT(expr)                                                                                             \
	do {                                                                                                               \
		assert(expr);                                                                                                  \
	} while (0)
#else
#define DEBUG_ASSERT(expr) ((void) 0)
#endif

#define DEF_LINKED_LIST_DOUBLE(ELEM_T, NODE_T)                                                                         \
                                                                                                                       \
	typedef struct NODE_T {                                                                                            \
		ELEM_T		   data;                                                                                           \
		struct NODE_T *pnext;                                                                                          \
		struct NODE_T *pprev;                                                                                          \
	} NODE_T;                                                                                                          \
                                                                                                                       \
	static void NODE_T##_insert_after(NODE_T *self, NODE_T *node) {                                                    \
		DEBUG_ASSERT(self != NULL && node != NULL);                                                                    \
		node->pnext = self->pnext;                                                                                     \
		node->pprev = self;                                                                                            \
		if (self->pnext != NULL) {                                                                                     \
			self->pnext->pprev = node;                                                                                 \
		}                                                                                                              \
		self->pnext = node;                                                                                            \
	}                                                                                                                  \
                                                                                                                       \
	static void NODE_T##_init(NODE_T *self, ELEM_T data) {                                                             \
		DEBUG_ASSERT(self != NULL);                                                                                    \
		self->data = data;                                                                                             \
		self->pnext = NULL;                                                                                            \
		self->pprev = NULL;                                                                                            \
	}                                                                                                                  \
                                                                                                                       \
	static NODE_T *NODE_T##_remove_next(NODE_T *self) {                                                                \
		DEBUG_ASSERT(self != NULL);                                                                                    \
		NODE_T *temp = self->pnext;                                                                                    \
		if (temp != NULL) {                                                                                            \
			self->pnext = temp->pnext;                                                                                 \
			if (temp->pnext != NULL) {                                                                                 \
				temp->pnext->pprev = self;                                                                             \
			}                                                                                                          \
		}                                                                                                              \
		return temp;                                                                                                   \
	}                                                                                                                  \
                                                                                                                       \
	static void NODE_T##_delete_next(NODE_T *self) {                                                                   \
		DEBUG_ASSERT(self != NULL);                                                                                    \
		NODE_T *temp = self->pnext;                                                                                    \
		if (temp != NULL) {                                                                                            \
			self->pnext = temp->pnext;                                                                                 \
			if (temp->pnext != NULL) {                                                                                 \
				temp->pnext->pprev = self;                                                                             \
			}                                                                                                          \
			free(temp);                                                                                                \
		}                                                                                                              \
	}                                                                                                                  \
                                                                                                                       \
	static bool NODE_T##_has_next(NODE_T *self) {                                                                      \
		DEBUG_ASSERT(self != NULL);                                                                                    \
		return self->pnext != NULL;                                                                                    \
	}

#endif
