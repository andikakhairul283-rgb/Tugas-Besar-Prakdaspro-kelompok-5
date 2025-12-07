#include <stdio.h>

// Mengubah karakter menjadi angka 0-26
int char_to_num(char ch, char arr[]) {
    // ubah huruf besar ke kecil
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
    }

    for (int i = 0; i < 27; i++) {
        if (ch == arr[i]) return i;
    }

    return 0; // default ke spasi jika karakter tidak valid
}

// Mengubah angka 0-26 menjadi karakter
char num_to_char(int num, char arr[]) {
    if (num >= 0 && num < 27)
        return arr[num];
    return ' ';
}

// gcd digunakan untuk cek apakah det dapat di-invers
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Enkripsi Hill Cipher 2x2
void hill_encrypt(char plaintext[], int key[2][2], char arr[]) {

    int nums[200];
    int len = 0;

    // KONVERSI plaintext -> angka
    for (int i = 0; plaintext[i] != '\0'; i++) {
        nums[len++] = char_to_num(plaintext[i], arr);
    }

    // Jika panjang ganjil → tambah spasi (0)
    if (len % 2 == 1) {
        nums[len++] = 0;
    }

    printf("\n--- Proses Enkripsi ---\n");
    printf("Angka (pair):\n");

    char encrypted_text[200];
    int en_index = 0;

    for (int i = 0; i < len; i += 2) {
        int x1 = nums[i];
        int x2 = nums[i+1];

        printf("[%d %d]\n", x1, x2);

        // Perkalian matriks Hill: C = K * X
        int c1 = (key[0][0] * x1 + key[0][1] * x2) % 27;
        int c2 = (key[1][0] * x1 + key[1][1] * x2) % 27;

        if (c1 < 0) c1 += 27;
        if (c2 < 0) c2 += 27;

        // Convert ke huruf
        encrypted_text[en_index++] = num_to_char(c1, arr);
        encrypted_text[en_index++] = num_to_char(c2, arr);
    }

    encrypted_text[en_index] = '\0';

    printf("\nHasil enkripsi (huruf): %s\n", encrypted_text);
}

int main()
{
  printf("dika fk ui");

  return 0;
}







