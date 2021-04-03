#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "main.h"

int main() {
	setlocale(LC_ALL, "");
	printf("������� ����������� �����\n");
	int num;
	while (1) {
		if (scanf("%d", &num) != 1) {
			char c;
			do {
				scanf("%c", &c);
			} while (c != '\n');
			printf("������. ������� �����\n");
		}
		else if (num <= 0) {
			printf("������. ����� ������ ���� �������������\n");
		}
		else if (num > 1000) {
			printf("������. ����� �� ������ ���� ������ 1000\n");
		}
		else {
			char c;
			scanf("%c", &c);
			break;
		}
	}
	printf("������� ����� ������:\n");
	printf("1.������������\n");
	printf("2.�����������\n");
	printf("3.�����������\n");
	printf("4.���������\n");
	printf("5.������������\n");
	printf("6.����������\n");
	int word_case;
	while(1) {
		if (scanf("%d", &word_case) != 1 || word_case < 0 || word_case > 6) {
			char c;
			do {
				scanf("%c", &c);
			} while (c != '\n');
			printf("�������� ����\n");
		}
		else {
			char result[SIZE];
			get_result(num, word_case, result);
			printf("%s", result);
			break;
		}
		char c;
		scanf("%c", &c);
	}
	printf("\n");
	system("pause");
	return 0;
}

void get_result(int num, int word_case, char* result) {
	result[0] = '\0';
	get_first_word(num, word_case, result);
	if (num % 1000 / 100 != 0) {
		get_second_word(num, word_case, result);
	}
	if (num % 100 / 10 != 0) {
		if (num % 1000 / 100 != 0) {
			result[len(result) + 1] = '\0';
			result[len(result)] = ' ';
		}
		get_third_word(num, word_case, result);
	}
	if (num % 100 / 10 != 1 && !(num > 0 && num % 10 == 0)) {
		if (num % 1000 / 10 != 0) {
			result[len(result) + 1] = '\0';
			result[len(result)] = ' ';
		}
		get_fourth_word(num, word_case, result);
	}
}

void get_first_word(int num, int word_case, char* result) {
	if (num == 1000) {
		char str[] = "�����a";
		// add
		copy(result, str);
		switch (word_case) {
		case 1:
			break;
		case 2:
			result[5] = '�';
			break;
		case 3:
			result[5] = '�';
			break;
		case 4:
		case 6:
			result[5] = '�';
			break;
		case 5:
			result[5] = '�';
			result[6] = '�';
			result[7] = '\0';
			break;
		}
	}
}

void get_second_word(int num, int word_case, char* result) {
	int digit = num % 1000 / 100;
	switch (word_case) {
	case 1:
	case 3:
		switch (digit) {
		case 0:
			break;
		case 1:
			copy(result, "���");
			break;
		case 2:
			copy(result, "������");
			break;
		case 3:
		case 4:
			get_fourth_word(digit, 1, result);
			copy(result, "���");
			break;
		default:
			get_fourth_word(digit, 1, result);
			copy(result, "���");
		}
		break;
	case 2:
		if (digit == 1) {
			copy(result, "���");
		}
		else {
			get_fourth_word(digit, word_case, result);
			copy(result, "���");
		}
		break;
	case 4:
		if (digit == 1) {
			copy(result, "���");
		}
		else {
			get_fourth_word(digit, word_case, result);
			copy(result, "����");
		}
		break;
	case 5:
		if (digit == 1) {
			copy(result, "���");
		}
		else {
			get_fourth_word(digit, word_case, result);
			copy(result, "�����");
		}
		break;
	case 6:
		if (digit == 1) {
			copy(result, "���");
		}
		else {
			get_fourth_word(digit, word_case, result);
			copy(result, "����");
		}
		break;
	}
}

void get_third_word(int num, int word_case, char* result) {
	int digit = num % 100 / 10;
	if (digit == 1) {
		int last_digit = num % 10;
		switch (last_digit) {
		case 0:
			copy(result, "������");
			break;
		case 1:
			copy(result, "�����������");
			break;
		case 2:
			copy(result, "����������");
			break;
		case 3:
			copy(result, "����������");
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			get_fourth_word(last_digit, 1, result);
			result[len(result) - 1] = '\0';
			copy(result, "�������");
			break;
		}
		switch (word_case) {
		case 2:
		case 4:
		case 6:
			result[len(result) - 1] = '�';
			break;
		case 5:
			result[len(result) + 1] = '\0';
			result[len(result)] = '�';
			break;
		}
		return;
	}
	switch (word_case) {
	case 1:
	case 3:
		switch (digit) {
		case 2:
		case 3:
			get_fourth_word(digit, 1, result);
			copy(result, "�����");
			break;
		case 4:
			copy(result, "�����");
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			get_fourth_word(digit, 1, result);
			copy(result, "�����");
			break;
		case 9:
			copy(result, "���������");
			break;
		}
		break;
	case 5:
		switch (digit) {
		case 2:
		case 3:
			get_fourth_word(digit, 1, result);
			copy(result, "������");
			break;
		case 4:
			copy(result, "������");
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			get_fourth_word(digit, 5, result);
			copy(result, "�������");
			break;
		case 9:
			copy(result, "���������");
			break;
		}
		break;
	case 2:
	case 4:
	case 6:
		switch (digit) {
		case 2:
		case 3:
			get_fourth_word(digit, 1, result);
			copy(result, "�����");
			break;
		case 4:
			copy(result, "������");
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			get_fourth_word(digit, 2, result);
			copy(result, "������");
			break;
		case 9:
			copy(result, "���������");
			break;
		}
		break;
	}
}

void get_fourth_word(int num, int word_case, char* result) {
	int digit = num % 10;
	if (digit <= 2) {
		switch (word_case) {
		case 1:
		case 3:
			switch (digit) {
			case 0:
				copy(result, "����");
				break;
			case 1:
				copy(result, "����");
				break;
			case 2:
				copy(result, "���");
				break;
			}
			break;
		case 2:
			switch (digit) {
			case 0:
				copy(result, "����");
				break;
			case 1:
				copy(result, "������");
				break;
			case 2:
				copy(result, "����");
				break;
			}
			break;
		case 4:
			switch (digit) {
			case 0:
				copy(result, "����");
				break;
			case 1:
				copy(result, "������");
				break;
			case 2:
				copy(result, "����");
				break;
			}
			break;
		case 5:
			switch (digit) {
			case 0:
				copy(result, "����");
				break;
			case 1:
				copy(result, "�����");
				break;
			case 2:
				copy(result, "�����");
				break;
			}
			break;
		case 6:
			switch (digit) {
			case 0:
				copy(result, "����");
				break;
			case 1:
				copy(result, "�����");
				break;
			case 2:
				copy(result, "����");
				break;
			}
			break;
		}
	}
	else if (digit == 3 || digit == 4) {
		if (digit == 3) {
			copy(result, "���");
		}
		else {
			copy(result, "������");
		}
		switch (word_case) {
		case 2:
		case 6:
			result[len(result) - 1] = '\0';
			copy(result, "��");
			break;
		case 4:
			result[len(result) - 1] = '\0';
			copy(result, "��");
			break;
		case 5:
			result[len(result) - 1] = '\0';
			if (digit == 3) {
				copy(result, "���");
			}
			else {
				copy(result, "���");
			}
			break;
		}
	}
	else {
		switch (digit) {
		case 5:
			copy(result, "����");
			break;
		case 6:
			copy(result, "�����");
			break;
		case 7:
			copy(result, "����");
			break;
		case 8:
			copy(result, "������");
			break;
		case 9:
			copy(result, "������");
			break;
		}
		switch (word_case) {
		case 2:
		case 4:
		case 6:
			if (digit == 8) {
				result[len(result) - 3] = '�';
			}
			result[len(result) - 1] = '�';
			break;
		case 5:
			result[len(result) + 1] = '\0';
			result[len(result)] = '�';
			break;
		}
	}
}

int len(const char* str) {
	for (int i = 0; ; i++) {
		if (str[i] == '\0') {
			return i;
		}
	}
}

void copy(char* dest, const char* source) {
	int dest_len = len(dest);
	for (int i = 0; i <= len(source); i++) {
		dest[dest_len + i] = source[i];
	}
}
