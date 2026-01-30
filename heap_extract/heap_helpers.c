#include "binary_trees.h"

/**
 * binary_tree_node - Creates a binary tree node
 * @parent: Pointer to the parent node
 * @value: Value to put in the new node
 *
 * Return: Pointer to the new node, or NULL on failure
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;

	new_node = malloc(sizeof(binary_tree_t));
	if (!new_node)
		return (NULL);

	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

/**
 * heapify_up - Maintains max heap property by bubbling up
 * @node: Node to heapify
 */
void heapify_up(heap_t *node)
{
	int temp;

	while (node->parent && node->n > node->parent->n)
	{
		temp = node->n;
		node->n = node->parent->n;
		node->parent->n = temp;
		node = node->parent;
	}
}

/**
 * count_nodes - Counts nodes in a binary tree using level-order
 * @root: Pointer to root node
 *
 * Return: Number of nodes
 */
size_t count_nodes(heap_t *root)
{
	heap_t *queue[1024];
	int front = 0, rear = 0;
	size_t count = 0;

	if (!root)
		return (0);

	queue[rear++] = root;
	while (front < rear)
	{
		heap_t *current = queue[front++];

		count++;
		if (current->left)
			queue[rear++] = current->left;
		if (current->right)
			queue[rear++] = current->right;
	}
	return (count);
}

/**
 * find_parent - Finds the parent node for insertion
 * @root: Pointer to root node
 * @index: Index of the new node
 *
 * Return: Pointer to parent node
 */
heap_t *find_parent(heap_t *root, size_t index)
{
	heap_t *queue[1024];
	int front = 0, rear = 0;
	size_t current_index = 1;

	if (!root)
		return (NULL);

	queue[rear++] = root;
	while (front < rear)
	{
		heap_t *current = queue[front++];

		if (current_index == index / 2)
			return (current);

		current_index++;
		if (current->left)
			queue[rear++] = current->left;
		if (current->right)
			queue[rear++] = current->right;
	}
	return (NULL);
}

/**
 * heap_insert - Inserts a value in Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	size_t size;

	if (!root)
		return (NULL);

	if (!*root)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = count_nodes(*root);
	parent = find_parent(*root, size + 1);

	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);

	if ((size + 1) % 2 == 0)
		parent->left = new_node;
	else
		parent->right = new_node;

	heapify_up(new_node);

	return (new_node);
}

/**
 * _array_to_heap - Builds a Max Binary Heap from an array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created Binary Heap, or NULL
 */
heap_t *_array_to_heap(int *array, size_t size)
{
	heap_t *root = NULL;
	size_t i;

	if (!array)
		return (NULL);

	for (i = 0; i < size; i++)
		heap_insert(&root, array[i]);

	return (root);
}

/**
 * _binary_tree_delete - Deletes an entire binary tree
 * @tree: Pointer to the root node of the tree to delete
 */
void _binary_tree_delete(binary_tree_t *tree)
{
	if (!tree)
		return;

	_binary_tree_delete(tree->left);
	_binary_tree_delete(tree->right);
	free(tree);
}
