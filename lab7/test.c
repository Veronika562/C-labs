#include <stdio.h>
#include <string.h>
#include <assert.h>

#undef main

int main() {
    _main();
    FILE* file1 = fopen("text_files/data.txt", "rb");
    FILE* file2 = fopen("text_files/out.txt", "rb");
    assert(file1 != NULL);
    assert(file2 != NULL);
    char ch1, ch2;
    FILE* check = fopen("check.txt", "w");
    while (ch1 != EOF || ch2 != EOF) {
        ch1 = getc(file1);
        ch2 = getc(file2);
        fprintf(check, "%c %c\n", ch1, ch2);
        //assert(ch1 == ch2);
    }
    fclose(file1);
    fclose(file2);
    fclose(check);

    FILE* file3 = fopen("text_files/test_con_out.txt", "rb");
    FILE* file4 = fopen("text_files/con_out.txt", "rb");
    assert(file3 != NULL);
    assert(file4 != NULL);
    char ch3, ch4;
    while (ch3 != EOF || ch4 != EOF) {
        ch3 = getc(file3);
        ch4 = getc(file4);
        assert(ch3 == ch4);
    }
    fclose(file3);
    fclose(file4);
    return 0;
}
