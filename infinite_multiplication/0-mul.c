#include "main.h"

/**
 * print_error_and_exit - Prints Error and exits with status 98
 */
void print_error_and_exit(void)
{
	char *error = "Error\n";
	int i = 0;

	while (error[i])
	{
		_putchar(error[i]);
		i++;
	}
	exit(98);
}

/**
 * is_digit - Checks if a string contains only digits
 * @str: String to check
 *
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - Returns the length of a string
 * @str: String to measure
 *
 * Return: Length of string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}

/**
 * perform_multiplication - Performs the multiplication algorithm
 * @num1: First number as string
 * @num2: Second number as string
 * @result: Array to store the result
 * @len1: Length of num1
 * @len2: Length of num2
 */
void perform_multiplication(char *num1, char *num2, int *result,
							int len1, int len2)
{
	int i, j, n1, n2, sum, carry;

	for (i = len1 - 1; i >= 0; i--)
	{
		n1 = num1[i] - '0';
		carry = 0;

		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = num2[j] - '0';
			sum = n1 * n2 + result[i + j + 1] + carry;
			carry = sum / 10;
			result[i + j + 1] = sum % 10;
		}

		result[i + j + 1] += carry;
	}
}

/**
 * print_result - Prints the result array
 * @result: Array containing the result
 * @len: Length of the result array
 */
void print_result(int *result, int len)
{
	int k, start_print;

	start_print = 0;
	for (k = 0; k < len; k++)
	{
		if (result[k] != 0)
			start_print = 1;
		if (start_print)
			_putchar(result[k] + '0');
	}

	if (!start_print)
		_putchar('0');

	_putchar('\n');
}

/**
 * multiply - Multiplies two positive numbers
 * @num1: First number as string
 * @num2: Second number as string
 */
void multiply(char *num1, char *num2)
{
	int len1, len2, len_result;
	int *result;

	len1 = _strlen(num1);
	len2 = _strlen(num2);
	len_result = len1 + len2;

	result = calloc(len_result, sizeof(int));
	if (!result)
		print_error_and_exit();

	perform_multiplication(num1, num2, result, len1, len2);
	print_result(result, len_result);

	free(result);
}

/**
 * main - Entry point for infinite multiplication program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
		print_error_and_exit();

	if (!is_digit(argv[1]) || !is_digit(argv[2]))
		print_error_and_exit();

	multiply(argv[1], argv[2]);

	return (0);
}
