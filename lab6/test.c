#include "tree.h"
#include <assert.h>
#undef main

void test(char input_f[11], char output_f[11], char expected_f[14]);

int main() {
    test("input1.txt", "output.txt", "expected1.txt");
    test("input2.txt", "output.txt", "expected2.txt");
    return 0;
}

void test(char input_f[11], char output_f[11], char expected_f[14]) {
    get_result(input_f, output_f);
    FILE* output = fopen(output_f, "r");
    FILE* expected = fopen(expected_f, "r");
    char out, exp;
    while (!feof(output) && !feof(expected)) {
        fscanf(output, "%c", &out);
        fscanf(expected, "%c", &exp);
        assert(out == exp);
    }
    fclose(output);
    fclose(expected);
}