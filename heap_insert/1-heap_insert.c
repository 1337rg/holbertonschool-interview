#include "binary_trees.h"
#include <stdlib.h>

/**
 * swap_values - swap n values of two nodes
 * @a: first node
 * @b: second node
 */
static void swap_values(heap_t *a, heap_t *b)
{
    int tmp = a->n;
    a->n = b->n;
    b->n = tmp;
}

/**
 * find_parent - find first parent with missing child (BFS)
 * @root: root of the heap
 * Return: pointer to the parent node
 */
static heap_t *find_parent(heap_t *root)
{
    heap_t **queue;
    size_t front = 0, back = 0;
    heap_t *node;

    queue = malloc(sizeof(*queue) * 1024);
    if (!queue)
        return (NULL);

    queue[back++] = root;
    while (front < back)
    {
        node = queue[front++];
        if (!node->left || !node->right)
        {
            free(queue);
            return (node);
        }
        queue[back++] = node->left;
        queue[back++] = node->right;
    }
    free(queue);
    return (NULL);
}

/**
 * heap_insert - inserts value into a Max Binary Heap
 * @root: double pointer to root node
 * @value: value to insert
 * Return: pointer to inserted node or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new, *parent;

    if (!root)
        return (NULL);

    if (*root == NULL)
    {
        *root = binary_tree_node(NULL, value);
        return (*root);
    }

    parent = find_parent(*root);
    if (!parent)
        return (NULL);

    new = binary_tree_node(parent, value);
    if (!new)
        return (NULL);

    if (parent->left == NULL)
        parent->left = new;
    else
        parent->right = new;

    /* Bubble up */
    while (new->parent && new->n > new->parent->n)
    {
        swap_values(new, new->parent);
        new = new->parent;
    }
    return (new);
}
