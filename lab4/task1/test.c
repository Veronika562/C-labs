#include <assert.h>
#include "main.h"

void test(int num, int word_case, const char* correct);
int are_equal(const char* str1, const char* str2);

#undef main
int main() {
	test(743, 5, "���������� ������ �����");
	test(140, 1, "��� �����");
	test(11, 2, "�����������");
	test(997, 3, "��������� ��������� ����");
	test(1000, 4, "������");
	test(842, 6, "���������� ������ ����");
	test(0, 3, "����");
	test(54, 1, "��������� ������");
	test(101, 4, "��� ������");
	return 0;
}

void test(int num, int word_case, const char* correct) {
	char result[SIZE];
	get_result(num, word_case, result);
	assert(are_equal(result, correct));
}

int are_equal(const char* str1, const char* str2) {
	if (len(str1) != len(str2)) {
		return 0;
	}
	for (int i = 0; i < len(str1) && i < len(str2); i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}