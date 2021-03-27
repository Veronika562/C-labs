#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main() {
	FILE* input, * output;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	if (input == NULL || output == NULL) {
		exit(2);
	}
	char current_char = 0;
	char num[SIZE] = "";
	while (current_char != EOF) {
		current_char = getc(input);
		if ((int)current_char - (int)'0' < 0 || (int)current_char - (int)'0' > 7) {
			fprintf(output, "%c", current_char);
		}
		else {
			int index = 0;
			num[index++] = current_char;
			for (int i = 0; i < SIZE - 1; i++) {
				current_char = getc(input);
				if ((int)current_char - (int)'0' < 0 || (int)current_char - (int)'0' > 7) {
					num[index++] = '\0';
					if (index > 0) {
						fprintf(output, "%ld", convert(num, SIZE));
					}
					fprintf(output, "%c", current_char);
					break;
				}
				else {
					num[index++] = current_char;
				}
			}
		}
	}
	fclose(input);
	fclose(output);
	system("pause");
	return 0;
}

long convert(char* num, int size) {
	long decimal = 0;
	for (int i = 0; i < size; i++) {
		if (num[i] == '\0') {
			for (int j = i - 1; j >= 0; j--) {
				decimal += (int)pow(8.0, i - 1.0 - j) * ((int)num[j] - (int)'0');
			}
			return decimal;
		}
	}
	return decimal;
}