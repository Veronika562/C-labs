#include "main.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	int dividend, divisor;
	while (1) {
		if (scanf("%d", &dividend) != 1 || scanf("%d", &divisor) != 1) {
			char c;
			do {
				scanf("%c", &c);
			} while (c != '\n');
			printf("Incorrect input. Try again\n");
			continue;
		}
		if (divisor == 0) {
			printf("Incorrect input: division by 0. Try again\n");
			continue;
		}
		else if (dividend % divisor != 0) {
			printf("Incorrect input: number %d is not divisible by %d\n", dividend, divisor);
			continue;
		}
		else {
			break;
		}
	}
	
	int quotient = dividend / divisor;
	int quotient_len = get_num_length(quotient);
	int dividend_len = get_num_length(dividend);
	int divisor_len = get_num_length(divisor);
	printf("_%d|%d", dividend, divisor);
	int remainder;
	int current_dividend = dividend / (int)pow(10, quotient_len - 1.0);
	int current_quotient_digit = (quotient % (int)pow(10, (double)quotient_len)) / (int)pow(10, quotient_len - 1.0);
	int next_dividend_digit = dividend % (current_dividend * (int)pow(10, quotient_len - 1.0));

	for (int i = 0; i < quotient_len; i++) {
		if (current_dividend / divisor == 0 && i != 0) {
			if (i == quotient_len - 1 || quotient % (int)pow(10, (double)quotient_len - i - 1) == 0) {
				for (int j = 0; j < dividend_len; j++) {
					printf(" ");
				}
				printf("0\n");
				break;
			}
			else {
				printf("%d", dividend % (int)pow(10, (double)quotient_len - i - 1) / (int)pow(10, (double)quotient_len - i - 2));
				next_dividend_digit = dividend % (int)pow(10, (double)quotient_len - i - 1) / (int)pow(10, (double)quotient_len - i - 2);
				current_dividend = current_dividend * 10 + next_dividend_digit;
				current_quotient_digit = quotient % (int)pow(10, (double)quotient_len - 1 - i) / (int)pow(10, (double)quotient_len - 2 - i);
				continue;
			}
		}
		printf("\n");

		int subtrahend = divisor * (int)((quotient % (int)pow(10, (double)quotient_len - i)) / 
			pow(10, (double)quotient_len - 1 - i));
		printf(" %*d", dividend_len - (quotient_len - 1) + i, subtrahend);
		remainder = current_dividend - subtrahend;
		for (int j = 0; j < quotient_len - 1; j++) {
			printf(" ");
		}
		if (i == 0) {
			printf("|");
			int width = (quotient_len > divisor_len) ? quotient_len : divisor_len;
			for (int j = 0; j < width; j++) {
				printf("-");
			}
		}
		printf("\n");

		printf(" ");
		for (int j = 0; j < dividend_len - (quotient_len - 1) + i - get_num_length(subtrahend); j++) {
			printf(" ");
		}
		for (int j = 0; j < get_num_length(subtrahend); j++) {
			printf("-");
		}
		if (i == 0) {
			for (int j = 0; j < quotient_len - 1; j++) {
				printf(" ");
			}
			printf("|%d", quotient);
		}
		printf("\n");

		if (remainder == 0) {
			if (i == quotient_len - 1 || quotient % (int)pow(10, (double)quotient_len - i - 1) == 0) {
				for (int j = 0; j < dividend_len; j++) {
					printf(" ");
				}
				printf("0\n");
				break;
			} 
			else {
				int width = dividend_len - quotient_len - 
					get_num_length((int)(dividend / pow(10, quotient_len - 1.0)) - 
						divisor * (int)(quotient / pow(10, quotient_len - 1.0))) + 1;
				for (int j = 0; j < width; j++) {
					printf(" ");
				}
				printf(" _");
			}
		}
		else {
			for (int j = 0; j < dividend_len - (quotient_len - i) - get_num_length(remainder) + 1; j++) {
				printf(" ");
			}
			printf("_%d", remainder);
		}
		current_quotient_digit = quotient % (int)pow(10, quotient_len - 1.0 - i) / (int)pow(10, quotient_len - 2.0 - i);
		next_dividend_digit = dividend % (int)pow(10, (double)quotient_len - i - 1) / (int)pow(10, (double)quotient_len - i - 2);
		printf("%d", next_dividend_digit);
		current_dividend = remainder * 10 + next_dividend_digit;
	}
	system ("pause");
	return 0;
}

int get_num_length(int num) {
	int len = 1;
	while (num > 9) {
		num /= 10;
		len++;
	}
	return len;
}
