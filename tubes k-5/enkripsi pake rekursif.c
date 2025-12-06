#include <stdio.h>

// Mengubah karakter menjadi angka 0-26
int char_to_num(char ch, char arr[]) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
    }
    for (int i = 0; i < 27; i++) {
        if (ch == arr[i]) return i;
    }
    return 0; // default ke spasi
}

// Mengubah angka 0-26 menjadi karakter
char num_to_char(int num, char arr[]) {
    if (num >= 0 && num < 27)
        return arr[num];
    return ' ';
}

// Fungsi rekursif untuk membalik string
void reverse_rec(char str[], int start, int end) {
    if (start >= end) return;
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverse_rec(str, start + 1, end - 1);
}

// Hitung panjang string manual
int str_len(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Enkripsi Hill Cipher 2x2
void hill_encrypt(char plaintext[], int key[2][2], char arr[]) {
    int nums[200];
    int len = 0;

    // KONVERSI plaintext ke angka
    for (int i = 0; plaintext[i] != '\0'; i++) {
        nums[len++] = char_to_num(plaintext[i], arr);
    }

    // Jika panjang ganjil → tambah spasi (0)
    if (len % 2 == 1) {
        nums[len++] = 0;
    }

    char encrypted_text[200];
    int en_index = 0;

    for (int i = 0; i < len; i += 2) {
        int x1 = nums[i];
        int x2 = nums[i+1];

        int c1 = (key[0][0] * x1 + key[0][1] * x2) % 27;
        int c2 = (key[1][0] * x1 + key[1][1] * x2) % 27;

        if (c1 < 0) c1 += 27;
        if (c2 < 0) c2 += 27;

        encrypted_text[en_index++] = num_to_char(c1, arr);
        encrypted_text[en_index++] = num_to_char(c2, arr);
    }

    encrypted_text[en_index] = '\0';

    // Rekursif: membalik hasil enkripsi
    reverse_rec(encrypted_text, 0, en_index - 1);

    printf("\nHasil enkripsi (huruf, rekursif): %s\n", encrypted_text);
}

int main() {
    int b1k1, b1k2, b2k1, b2k2;

    char arr[27];
    arr[0] = ' ';
    for (int i = 1; i <= 26; i++) {
        arr[i] = 'a' + (i - 1);
    }

    printf("Input key baris pertama kolom pertama : "); scanf("%d", &b1k1);
    printf("Input key baris pertama kolom kedua   : "); scanf("%d", &b1k2);
    printf("Input key baris kedua kolom pertama   : "); scanf("%d", &b2k1);
    printf("Input key baris kedua kolom kedua     : "); scanf("%d", &b2k2);

    int key[2][2] = {
        {b1k1, b1k2},
        {b2k1, b2k2}
    };

    getchar(); // bersihkan newline

    char plaintext[200];
    printf("Masukkan plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Hilangkan newline manual
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] == '\n') {
            plaintext[i] = '\0';
            break;
        }
    }

    hill_encrypt(plaintext, key, arr);

    return 0;
}
