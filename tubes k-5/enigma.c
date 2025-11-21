#include <stdio.h>
#include <string.h>

int main() {
    char arr[27];
    arr[0] = ' ';

    for (int i = 1; i <= 26; i++) {
        arr[i] = 'a' + (i - 1);
    }

    char input[100];
    printf("Masukkan kata/kalimat: ");
    fgets(input, sizeof(input), stdin);

    // Hilangkan newline
    input[strcspn(input, "\n")] = '\0';

    printf("Hasil konversi ke angka: ");

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (c == ' ') {
            printf("0 ");
        } else if (c >= 'a' && c <= 'z') {
            printf("%d ", (c - 'a') + 1);
        } else {
            printf("? "); // jika ada karakter selain a-z/spasi
        }
    }

    printf("\n");

    return 0;
}
