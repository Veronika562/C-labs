#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);

int main() {
	int rows, cols;
	while (1) {
		if (scanf("%d", &rows) != 1 || scanf("%d", &cols) != 1) {
			char c;
			do {
				scanf("%c", &c);
			} while (c != '\n');
			printf("Incorrect input. Try again\n");
		}	
		else if (rows <= 0 || cols <= 0) {
			printf("Numbers must be positive. Try again\n");
		}
		else {
			break;
		}
	}

	int** arr = (int**)malloc(rows * sizeof(int*));
	if (arr == NULL) {
		exit(2);
	}
	for (int i = 0; i < rows; i++) {
		arr[i] = (int*)malloc(cols * sizeof(int));
		if (arr[i] == NULL) {
			exit(2);
		}
	}
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			while (1) {
				if (scanf("%d", &arr[i][j]) != 1) {
					char c;
					do {
						scanf("%c", &c);
					} while (c != '\n');
					printf("Incorrect input. Try again\n");
				}
				else {
					break;
				}
			}
		}
	}

	int max_size = (rows > cols) ? rows : cols;
	int min_size = (rows < cols) ? rows : cols;
	for (int k = 0; k < max_size - 1; k++) {
		int count_i = (k <= abs(rows - cols)) ? min_size : max_size - k;
		for (int i = 0; i < count_i; i++) {
			int count_j = (k <= abs(rows - cols)) ? min_size - 1 : max_size - k - 1;
			if (rows > cols) {
				for (int j = 0; j < count_j; j++) {
					if (arr[j + k][j] > arr[j + k + 1][j + 1]) {
						swap(&arr[j + k][j], &arr[j + k + 1][j + 1]);
					}
				}
			}
			else {
				for (int j = 0; j < count_j; j++) {
					if (arr[j][j + k] > arr[j + 1][j + k + 1]) {
						swap(&arr[j][j + k], &arr[j + 1][j + 1 + k]);
					}
				}
			}
		}
	}
	for (int k = 1; k < min_size - 1; k++) {
		for (int i = 0; i < min_size - k; i++) {
			if (rows > cols) {
				for (int j = 0; j < cols - 1 - k; j++) {
					if (arr[j][j + k] > arr[j + 1][j + k + 1]) {
						swap(&arr[j][j + k], &arr[j + 1][j + k + 1]);
					}
				}
			}
			else {
				for (int j = 0; j < rows - 1 - k; j++) {
					if (arr[j + k][j] > arr[j + k + 1][j + 1]) {
						swap(&arr[j + k][j], &arr[j + k + 1][j + 1]);
					}
				}
			}
		}
	}

	printf("\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);
    system("pause");
	return 0;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}