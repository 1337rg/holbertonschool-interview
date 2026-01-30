#include <stdio.h>
#include "search_algos.h"

/**
 * print_array - Affiche un sous-tableau d'entiers
 * @array: Pointeur sur le tableau
 * @left: Index gauche du sous-tableau
 * @right: Index droit du sous-tableau
 */
void print_array(int *array, size_t left, size_t right)
{
	size_t i;

	printf("Searching in array: ");
	for (i = left; i <= right; i++)
	{
		printf("%d", array[i]);
		if (i < right)
			printf(", ");
	}
	printf("\n");
}

/**
 * advanced_binary_helper - Recherche binaire récursive
 *                           qui retourne la première occurrence
 * @array: Tableau trié d'entiers
 * @left: Bord gauche du sous-tableau courant
 * @right: Bord droit du sous-tableau courant
 * @value: Valeur à chercher
 *
 * Return: Index de la première occurrence, ou -1
 */
int advanced_binary_helper(int *array, size_t left, size_t right, int value)
{
	size_t mid;

	if (left > right)
		return (-1);

	print_array(array, left, right);

	mid = left + (right - left) / 2;

	if (array[mid] == value)
	{
		/* Vérifier si c'est la première occurrence dans ce segment */
		if (mid == left || array[mid - 1] != value)
			return ((int)mid);

		/* Sinon, il y a encore value à gauche : on garde mid dans la fenêtre */
		return (advanced_binary_helper(array, left, mid, value));
	}
	else if (array[mid] < value)
	{
		/* Chercher dans la moitié droite (mid exclu, car trop petit) */
		return (advanced_binary_helper(array, mid + 1, right, value));
	}
	else /* array[mid] > value */
	{
		/*
		 * Chercher dans moitié gauche en gardant mid (trop grand) dans la fenêtre
		 * pour obtenir des affichages comme "11, 21, 31, 33" puis "31, 33".
		 */
		return (advanced_binary_helper(array, left, mid, value));
	}
}

/**
 * advanced_binary - Recherche avancée dans un tableau trié
 * @array: Pointeur sur le premier élément du tableau
 * @size: Nombre d'éléments du tableau
 * @value: Valeur à chercher
 *
 * Return: Index de la première occurrence, ou -1
 */
int advanced_binary(int *array, size_t size, int value)
{
	if (array == NULL || size == 0)
		return (-1);

	return (advanced_binary_helper(array, 0, size - 1, value));
}
