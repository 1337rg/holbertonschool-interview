#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list of integers
 * @list: Pointer to the head of the skip list
 * @value: Value to search for
 *
 * Return: Pointer to the first node where value is located, or NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *express, *current;

	if (list == NULL)
		return (NULL);
	express = list;
	current = list;

	while (express->express && express->n < value)
	{
		current = express;
		express = express->express;
		printf("Value checked at index [%lu] = [%d]\n", express->index, express->n);
	}

	if (express->express == NULL && express->n < value)
	{
		current = express;
		while (express->next)
			express = express->next;
	}

	printf("Value found between indexes [%lu] and [%lu]\n",
current->index, express->index);

	while (current && current->index <= express->index)
	{
		printf("Value checked at index [%lu] = [%d]\n", current->index, current->n);
		if (current->n == value)
			return (current);
		current = current->next;
	}
	return (NULL);
}
