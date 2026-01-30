#include "binary_trees.h"

/**
 * get_heap_size - Counts the number of nodes in a binary tree
 * @root: Pointer to the root node
 *
 * Return: Number of nodes in the tree
 */
size_t get_heap_size(heap_t *root)
{
	if (!root)
		return (0);
	return (1 + get_heap_size(root->left) + get_heap_size(root->right));
}

/**
 * get_last_node - Gets the last level-order node of the heap
 * @root: Pointer to the root node
 * @size: Size of the heap
 * @index: Current index (1-indexed)
 *
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t *root, size_t size, size_t index)
{
	heap_t *left, *right;

	if (!root)
		return (NULL);

	if (index == size)
		return (root);

	left = get_last_node(root->left, size, 2 * index);
	if (left)
		return (left);

	right = get_last_node(root->right, size, 2 * index + 1);
	return (right);
}

/**
 * heapify_down - Rebuilds the max heap after extraction
 * @root: Pointer to the root node to heapify
 */
void heapify_down(heap_t *root)
{
	heap_t *largest = root;
	int temp;

	while (1)
	{
		largest = root;

		if (root->left && root->left->n > largest->n)
			largest = root->left;

		if (root->right && root->right->n > largest->n)
			largest = root->right;

		if (largest == root)
			break;

		/* Swap values */
		temp = root->n;
		root->n = largest->n;
		largest->n = temp;

		root = largest;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: The value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	int extracted_value;
	heap_t *last_node, *heap_root;
	size_t size;

	if (!root || !*root)
		return (0);

	heap_root = *root;
	extracted_value = heap_root->n;
	size = get_heap_size(heap_root);

	if (size == 1)
	{
		free(heap_root);
		*root = NULL;
		return (extracted_value);
	}

	last_node = get_last_node(heap_root, size, 1);

	/* Replace root value with last node value */
	heap_root->n = last_node->n;

	/* Remove the last node */
	if (last_node->parent)
	{
		if (last_node->parent->right == last_node)
			last_node->parent->right = NULL;
		else
			last_node->parent->left = NULL;
	}

	free(last_node);

	/* Rebuild the heap */
	heapify_down(heap_root);

	return (extracted_value);
}
