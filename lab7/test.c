#include <stdio.h>
#include <string.h>
#include <assert.h>

#undef main

int main() {
    _main(2, "test", "./text_files/test.txt");
    FILE* file1 = fopen("./text_files/out.txt", "r");
    FILE* file2 = fopen("./text_files/test.txt", "r");
    assert(file1 != NULL);
    assert(file2 != NULL);
    char line1[100], line2[100];
    while (!feof(file1) || !feof(file2)) {
        fgets(line1, 100, file1);
        fgets(line2, 100, file2);
        assert(strcmp(line1, line2) == 0);
    }
    assert(feof(file1) == feof(file2));
    fclose(file1);
    fclose(file2);

    FILE* file3 = fopen("./text_files/con_out.txt", "r");
    FILE* file4 = fopen("./text_files/test_con_out.txt", "r");
    assert(file3 != NULL);
    assert(file4 != NULL);
    char line3[100], line4[100];
    while (!feof(file3) || !feof(file4)) {
        fgets(line3, 100, file3);
        fgets(line4, 100, file4);
        assert(strcmp(line3, line4) == 0);
    }
    assert(feof(file3) == feof(file4));
    fclose(file3);
    fclose(file4);
    return 0;
}