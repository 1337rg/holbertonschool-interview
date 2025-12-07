#include "binary_trees.h"
#include <stdlib.h>

/**
 * create_node - Creates a binary tree node
 * @value: Value to be stored in node
 * Return: Pointer to new node or NULL on failure
 */
avl_t *create_node(int value)
{
	avl_t *new_node;

	new_node = malloc(sizeof(avl_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = value;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

/**
 * build_avl - Recursively builds an AVL tree from array
 * @array: Array to convert
 * @start: Start index
 * @end: End index
 * @parent: Parent node
 * Return: Pointer to root node of AVL tree or NULL on failure
 */
avl_t *build_avl(int *array, size_t start, size_t end, avl_t *parent)
{
	avl_t *root;
	size_t mid;

	if (start > end)
		return (NULL);

	mid = (start + end) / 2;

	root = create_node(array[mid]);
	if (root == NULL)
		return (NULL);

	root->parent = parent;

	if (start < mid)
		root->left = build_avl(array, start, mid - 1, root);

	if (mid < end)
		root->right = build_avl(array, mid + 1, end, root);

	return (root);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 * Return: Pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (array == NULL || size == 0)
		return (NULL);

	return (build_avl(array, 0, size - 1, NULL));
}
