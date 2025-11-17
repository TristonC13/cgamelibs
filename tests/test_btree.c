#include "btree/btree.h"
#include <assert.h>
#include <stdio.h>

DEF_BTREE(int, IntTree)

int main(void) {
	// Initialize nodes
	IntTree_node head;
	IntTree_node_init_t(&head, 5); // Create root node with value 5

	IntTree_node left_child;
	IntTree_node_init_t(&left_child, 3); // Create left child with value 3

	IntTree_node right_child;
	IntTree_node_init_t(&right_child, 8); // Create right child with value 8

	// Link the nodes and set parents
	head.pchildren[0] = &left_child;						  // Link left child
	head.pchildren[1] = &right_child;						  // Link right child
	IntTree_node_parent_to(&left_child, &head, BTREE_LEFT);	  // Set parent for left child
	IntTree_node_parent_to(&right_child, &head, BTREE_RIGHT); // Set parent for right child

	// Create more nodes and link them
	IntTree_node left_left_child;
	IntTree_node_init_t(&left_left_child, 1);						   // Create left-left child with value 1
	left_child.pchildren[0] = &left_left_child;						   // Link it to left child
	IntTree_node_parent_to(&left_left_child, &left_child, BTREE_LEFT); // Set parent for left-left child

	IntTree_node left_right_child;
	IntTree_node_init_t(&left_right_child, 4);							 // Create left-right child with value 4
	left_child.pchildren[1] = &left_right_child;						 // Link it to left child
	IntTree_node_parent_to(&left_right_child, &left_child, BTREE_RIGHT); // Set parent for left-right child

	IntTree_node right_left_child;
	IntTree_node_init_t(&right_left_child, 7);							 // Create right-left child with value 7
	right_child.pchildren[0] = &right_left_child;						 // Link it to right child
	IntTree_node_parent_to(&right_left_child, &right_child, BTREE_LEFT); // Set parent for right-left child

	IntTree_node right_right_child;
	IntTree_node_init_t(&right_right_child, 10);						   // Create right-right child with value 10
	right_child.pchildren[1] = &right_right_child;						   // Link it to right child
	IntTree_node_parent_to(&right_right_child, &right_child, BTREE_RIGHT); // Set parent for right-right child

	IntTree_iterator iter;
	IntTree_iterator_init(&iter, &head);

	// Example of accessing the values
	printf("Root: %d\n", head.value);
	printf("Left Child: %d\n", head.pchildren[0]->value);
	printf("Right Child: %d\n", head.pchildren[1]->value);
	printf("Left Left Child: %d\n", head.pchildren[0]->pchildren[0]->value);
	printf("Left Right Child: %d\n", head.pchildren[0]->pchildren[1]->value);
	printf("Right Left Child: %d\n", head.pchildren[1]->pchildren[0]->value);
	printf("Right Right Child: %d\n", head.pchildren[1]->pchildren[1]->value);

	int did_iter = IntTree_iter_child(&iter, BTREE_LEFT);
	assert(did_iter == 1);
	did_iter = IntTree_iter_child(&iter, BTREE_LEFT);
	assert(did_iter == 1);
	did_iter = IntTree_iter_child(&iter, BTREE_LEFT);
	assert(did_iter == 0); // Theres no node there

	did_iter = IntTree_iter_parent(&iter);
	assert(did_iter == 1);
	did_iter = IntTree_iter_parent(&iter);
	assert(did_iter == 1);
    did_iter = IntTree_iter_parent(&iter);
	assert(did_iter == 0); // Already at head

	IntTree_iterator_deinit(&iter);

	return 0;
}
