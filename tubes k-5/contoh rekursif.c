#include <stdio.h>
void balik(const char*teks){
    if (*teks == '\0') {
        return;
    }

    balik(teks + 1);
    putchar(*teks);
}

int main() {
    char teks[100];
    printf("Masukkan kalimat: ");
    fgets(teks, sizeof(teks), stdin);
    printf("Kalimat terbalik: ");
    balik(teks);
    printf("\n");
    return 0;
}
