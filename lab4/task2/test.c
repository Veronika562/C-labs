#include "main.h"
#include <assert.h>

void test(char* num, int size, long converted) {
	assert(convert(num, size) == converted);
}

#undef main

int main() {
	test("27345", SIZE, 12005);
	test("5644", SIZE, 2980);
	test("3666661", SIZE, 1011121);
	test("21417", SIZE, 8975);
	test("6", SIZE, 6);
	test("7447", SIZE, 3879);
	test("44441677", SIZE, 9585599);
	test("7777777777", SIZE, 1073741823);
	return 0;
}