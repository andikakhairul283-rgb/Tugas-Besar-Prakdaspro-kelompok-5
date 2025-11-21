#include <stdio.h>

int main() {
    char arr[27]; // 0 sampai 26

    arr[0] = ' '; // index 0 adalah spasi

    // Mengisi index 1 sampai 26 dengan huruf a-z
    for (int i = 1; i <= 26; i++) {
        arr[i] = 'a' + (i - 1);
    }

    // Cetak untuk memastikan isinya benar
    for (int i = 0; i < 27; i++) {
        printf("arr[%d] = %c\n", i, arr[i]);
    }

    return 0;
}
