#include <stdio.h>
#include <string.h>
#include <assert.h>

#undef main

int main() {
    _main();
    FILE* file1 = fopen("text_files/data.txt", "r");
    FILE* file2 = fopen("text_files/out.txt", "r");
    assert(file1 != NULL);
    assert(file2 != NULL);
    //char ch1, ch2;
    char line1[100];
    char line2[100];
    while (feof(file1) == 0 && feof(file2) == 0) {
//         ch1 = getc(file1);
//         ch2 = getc(file2);
        if (fscanf(file1, "%s", line1) && fscanf(file2, "%s", line2)) {
			assert(strcmp(line1, line2) == 0);
		}
        assert(strcmp(line1, line2) == 0);
        //assert(ch1 == ch2);
    }
    fclose(file1);
    fclose(file2);

    FILE* file3 = fopen("text_files/test_con_out.txt", "rb");
    FILE* file4 = fopen("text_files/con_out.txt", "rb");
    assert(file3 != NULL);
    assert(file4 != NULL);
    char ch3, ch4;
    while (ch3 != EOF || ch4 != EOF) {
        ch3 = getc(file3);
        ch4 = getc(file4);
        //assert(ch3 == ch4);
    }
    fclose(file3);
    fclose(file4);
    return 0;
}
