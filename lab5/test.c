#include "number.h"
#include <assert.h>

void test(const int pow, const char* result);
int equal(const char* str1, const char* str2);
int len(const char* str);

#undef main

int main() {
    test(100, "515377520732011331036461129765621272702107522001");
    test(170, "1290070078170102666248196035845070394933441741644993085810116441344597492642263849");
    test(153, "9989689095948428268966921126195809393034773710522520293009978943147202723");
    test(112, "273892744995340833777347939263771534786080723599733441");
    return 0;
}

void test(const int pow, const char* result) {
    number* num = create_number("3", 1);
    power(3, pow, num);
    assert(equal(to_string(num), result));
    delete_number(num);
}

int equal(const char* str1, const char* str2) {
	if (len(str1) != len(str2)) {
		return 0;
	}
	for (int i = 0; i < len(str1); i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}

int len(const char* str) {
	for (int i = 0; ; i++) {
		if (str[i] == '\0') {
			return i;
		}
	}
}