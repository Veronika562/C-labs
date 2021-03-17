#include <assert.h>
#include "main.h"

void test(int num, int len) {
	assert(get_num_length(num) == len);
}

#undef main

int main() {
	test(2374918, 7);
	test(3, 1);
	test(7400, 4);
	test(58229308, 8);
	return 0;
}