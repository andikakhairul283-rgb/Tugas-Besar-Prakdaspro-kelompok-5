#include <stdio.h>

// Konversi karakter ke angka 0–26
int char_to_num(char ch, char arr[]) {
    if (ch >= 'A' && ch <= 'Z') ch = ch - 'A' + 'a';
    for (int i = 0; i < 27; i++) {
        if (arr[i] == ch) return i;
    }
    return 0;
}

// Konversi angka ke karakter
char num_to_char(int num, char arr[]) {
    if (num >= 0 && num < 27) return arr[num];
    return ' ';
}

// gcd untuk cek apakah det bisa di-inverse
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// cari invers determinan mod 27
int mod_inverse(int det) {
    det %= 27;
    if (det < 0) det += 27;

    for (int x = 1; x < 27; x++) {
        if ((det * x) % 27 == 1) return x;
    }
    return -1;
}

// Fungsi rekursif membalik string
void reverse_rec(char str[], int start, int end) {
    if (start >= end) return;
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverse_rec(str, start + 1, end - 1);
}

// Fungsi menghitung panjang string manual
int str_len(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

// Fungsi dekripsi Hill Cipher
void hill_decrypt(char ciphertext[], int key[2][2], char arr[]) {
    int a = key[0][0], b = key[0][1];
    int c = key[1][0], d = key[1][1];

    int det = a * d - b * c;

    if (gcd(det, 27) != 1) {
        printf("\nKUNCI TIDAK BISA DIINVERSE (det tidak relatif prima dengan 27)\n");
        return;
    }

    int det_inv = mod_inverse(det);
    if (det_inv == -1) {
        printf("\nTIDAK MENEMUKAN INVERS MODULO 27 UNTUK DETERMINAN\n");
        return;
    }

    // Matriks invers
    int inv_key[2][2];
    inv_key[0][0] =  d; inv_key[0][1] = -b;
    inv_key[1][0] = -c; inv_key[1][1] =  a;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv_key[i][j] = (inv_key[i][j] * det_inv) % 27;
            if (inv_key[i][j] < 0) inv_key[i][j] += 27;
        }
    }

    // Konversi ciphertext ke angka
    int nums[200];
    int len = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        nums[len++] = char_to_num(ciphertext[i], arr);
    }

    // Dekripsi per pasangan
    char decrypted[200];
    int dec_i = 0;

    for (int i = 0; i < len; i += 2) {
        int c1 = nums[i];
        int c2 = nums[i+1];

        int x1 = (inv_key[0][0] * c1 + inv_key[0][1] * c2) % 27;
        int x2 = (inv_key[1][0] * c1 + inv_key[1][1] * c2) % 27;

        if (x1 < 0) x1 += 27;
        if (x2 < 0) x2 += 27;

        decrypted[dec_i++] = num_to_char(x1, arr);
        decrypted[dec_i++] = num_to_char(x2, arr);
    }

    decrypted[dec_i] = '\0';

    printf("\nHASIL DESKRIPSI: %s\n", decrypted);
}

int main() {
    char arr[27];
    arr[0] = ' ';
    for (int i = 1; i <= 26; i++) arr[i] = 'a' + (i - 1);

    int k11, k12, k21, k22;

    printf("Masukkan key 2x2 untuk DEKRIPSI:\n");
    printf("k11 = "); scanf("%d", &k11);
    printf("k12 = "); scanf("%d", &k12);
    printf("k21 = "); scanf("%d", &k21);
    printf("k22 = "); scanf("%d", &k22);

    int key[2][2] = {
        {k11, k12},
        {k21, k22}
    };

    getchar(); // bersihkan newline

    char ciphertext[200];
    printf("Masukkan ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // buang newline
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] == '\n') { ciphertext[i] = '\0'; break; }
    }

    // Rekursif: balik ciphertext
    reverse_rec(ciphertext, 0, str_len(ciphertext) - 1);

    hill_decrypt(ciphertext, key, arr);

    return 0;
}
