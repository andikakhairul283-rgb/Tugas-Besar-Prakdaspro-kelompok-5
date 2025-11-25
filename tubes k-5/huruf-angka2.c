#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    printf("Masukkan kata/kalimat: ");
    fgets(input, sizeof(input), stdin);

    // Hilangkan newline
    input[strcspn(input, "\n")] = '\0';

    printf("Hasil konversi terbalik: ");

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (c == ' ') {
            printf("0 ");
        } else if (c >= 'a' && c <= 'z') {
            // Huruf 'a' → 26, 'b' → 25, ..., 'z' → 1
            printf("%d ", 26 - (c - 'a'));
        } else {
            printf("? ");
        }
    }

    printf("\n");

    return 0;
}
