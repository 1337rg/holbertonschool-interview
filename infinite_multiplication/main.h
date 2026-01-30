#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>

int _putchar(char c);
void print_error_and_exit(void);
int is_digit(char *str);
int _strlen(char *str);
void perform_multiplication(char *num1, char *num2, int *result,
							int len1, int len2);
void print_result(int *result, int len);
void multiply(char *num1, char *num2);

#endif
