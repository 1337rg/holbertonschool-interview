#include "sort.h"

/**
 * swap - Swaps two integers and prints the array
 * @array: The array being sorted
 * @size: Size of the array
 * @i: Index of first element
 * @j: Index of second element
 */
void swap(int *array, size_t size, size_t i, size_t j)
{
	int temp = array[i];

	array[i] = array[j];
	array[j] = temp;
	print_array(array, size);
}

/**
 * sift_down - Moves element down the heap
 * @array: The array representing the heap
 * @size: Size of the array
 * @root: Index of root element
 * @heap_size: Current size of the heap
 */
void sift_down(int *array, size_t size, size_t root, size_t heap_size)
{
	size_t largest = root;
	size_t left = 2 * root + 1;
	size_t right = 2 * root + 2;

	if (left < heap_size && array[left] > array[largest])
		largest = left;
	if (right < heap_size && array[right] > array[largest])
		largest = right;
	if (largest != root)
	{
		swap(array, size, root, largest);
		sift_down(array, size, largest, heap_size);
	}
}

/**
 * heap_sort - Sorts array using heap sort algorithm
 * @array: Array to sort
 * @size: Size of the array
 */
void heap_sort(int *array, size_t size)
{
	int i;

	if (size < 2)
		return;
	for (i = size / 2 - 1; i >= 0; i--)
		sift_down(array, size, i, size);
	for (i = size - 1; i > 0; i--)
	{
		swap(array, size, 0, i);
		sift_down(array, size, 0, i);
	}
}
