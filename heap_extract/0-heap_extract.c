#include "binary_trees.h"

/* Helper functions */
heap_t *get_last_node(heap_t *root);
void heapify_down(heap_t *tree);

/**
 * heap_extract - extracts the top value of binary heap
 * @root: pointer to root node of heap address
 * Return: top value (root node)
 */
int heap_extract(heap_t **root)
{
	int max;
	heap_t *last_node, *parent;

	if (!root || !*root)
		return (0);

	max = (*root)->n;

	/* Find the last inserted node */
	last_node = get_last_node(*root);
	if (!last_node)
		return (0);

	/* Swap last node value with root */
	(*root)->n = last_node->n;

	/* Remove last node from tree */
	parent = last_node->parent;
	if (parent)
	{
		if (parent->left == last_node)
			parent->left = NULL;
		else
			parent->right = NULL;
	}

	free(last_node);

	/* Heapify down */
	heapify_down(*root);

	return (max);
}

/**
 * get_last_node - finds the last node in level order traversal
 * @root: root of the heap
 * Return: last node in the heap
 */
heap_t *get_last_node(heap_t *root)
{
	/* Use a queue to perform level-order traversal */
	heap_t *queue[1024];
	int front = 0, rear = 0;

	if (!root)
		return (NULL);

	queue[rear++] = root;

	while (front < rear)
	{
		root = queue[front++];
		if (root->left)
			queue[rear++] = root->left;
		if (root->right)
			queue[rear++] = root->right;
	}

	return (root);
}

/**
 * heapify_down - restores max heap property by pushing the root down
 * @tree: root of heap
 */
void heapify_down(heap_t *tree)
{
	heap_t *largest, *left, *right;
	int temp;

	if (!tree)
		return;

	while (tree->left)
	{
		left = tree->left;
		right = tree->right;
		largest = tree;

		if (left && left->n > largest->n)
			largest = left;
		if (right && right->n > largest->n)
			largest = right;

		if (largest == tree)
			break;

		/* Swap values */
		temp = tree->n;
		tree->n = largest->n;
		largest->n = temp;

		/* Move down the tree */
		tree = largest;
	}
}

