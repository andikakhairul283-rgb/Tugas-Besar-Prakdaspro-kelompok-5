#include <stdio.h>
#include <stdlib.h> // <-- untuk abs()

// Mengubah karakter menjadi angka 0-26
int karakter_ke_angka(char ch, char arr[])
{
    // ubah huruf besar ke kecil
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch - 'A' + 'a';
    }

    for (int i = 0; i < 27; i++)
    {
        if (ch == arr[i])
            return i;
    }

    return 0; // default ke spasi jika karakter tidak valid
}

// Mengubah angka 0-26 menjadi karakter
char angka_ke_karakter(int num, char arr[])
{
    if (num >= 0 && num < 27)
        return arr[num];
    return ' ';
}

// gcd digunakan untuk cek apakah det dapat di-invers
int gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while (b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// cari invers determinan mod 27 (extended Euclid sederhana)
int mod_inverse(int det)
{
    det %= 27;
    if (det < 0)
        det += 27;

    for (int x = 1; x < 27; x++)
    {
        if ((det * x) % 27 == 1)
            return x;
    }
    return -1; // tidak ada invers
}

void rekursif(int nums[], int index, int len, /blm/
              int matrix[2][2], char arr[],
              char output_text[], int *out_index)
{

    // BASE CASE: selesai
if (index >= len)
    {
        return;
    }

    int x1 = nums[index];
    int x2 = nums[index + 1];

    printf("[%d %d]\n", x1, x2);

    // Proses matematika matriks
    int r1 = (matrix[0][0] * x1 + matrix[0][1] * x2) % 27;
    int r2 = (matrix[1][0] * x1 + matrix[1][1] * x2) % 27;

    if (r1 < 0)
        r1 += 27;
    if (r2 < 0)
        r2 += 27;
  // Convert ke huruf (output huruf)
    output_text[(*out_index)++] = angka_ke_karakter(r1, arr);
    output_text[(*out_index)++] = angka_ke_karakter(r2, arr);

    // REKURSI → lanjut pasangan berikutnya
    rekursif(nums, index + 2, len, matrix, arr, output_text, out_index);
}

void enkripsi(char plaintext[], int key[2][2], char arr[])
{

    int nums[200];
    int len = 0;

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        nums[len++] = karakter_ke_angka(plaintext[i], arr);
    }

    if (len % 2 == 1)
        nums[len++] = 0;

    printf("\n--- Proses Enkripsi ---\n");

    char encrypted_text[200];
    int en_index = 0;
  // PANGGIL REKURSI (satu-satunya proses enkripsi)
    rekursif(nums, 0, len, key, arr, encrypted_text, &en_index);

    encrypted_text[en_index] = '\0';

    printf("\nHasil enkripsi : %s\n", encrypted_text);

    // ==========================
    // FILE HANDLING: SIMPAN SANDI + KUNCI DALAM SATU FILE
    // ==========================
    FILE *fout = fopen("output_enkripsi.txt", "w");
    if (fout == NULL)
    {
        printf("Gagal membuat file output_enkripsi.txt!\n");
    }
    else
    {
        fprintf(fout, "Ini adalah sandi dan enkripsi anda,\n");

fprintf(fout, "Terimakasih sudah menggunakan program ini.\n\n");

        fprintf(fout, "=== Hasil Enkripsi ===\n");
        fprintf(fout, "%s\n\n", encrypted_text);

        fprintf(fout, "=== Matriks Kunci (2x2) ===\n");
        fprintf(fout, "[ %d  %d ]\n", key[0][0], key[0][1]);
        fprintf(fout, "[ %d  %d ]\n\n", key[1][0], key[1][1]);

        fclose(fout);
        printf("\nFile 'output_enkripsi.txt' berhasil dibuat.\n");
    }
}

void dekripsi(char ciphertext[], int key[2][2], char arr[])
{
    int a = key[0][0], b = key[0][1];
    int c = key[1][0], d = key[1][1];

    int det = a * d - b * c;
// Normalisasi determinan ke modulo 27 (0..26)
    int det_mod = det % 27;
    if (det_mod < 0)
        det_mod += 27;

 // cek gcd pada det_mod dan 27
    if (gcd(det_mod, 27) != 1)
    {
        printf("\nKunci tidak bisa diinverse.\n");
        return;
    }

    // gunakan det_mod untuk mencari invers
    int det_inv = mod_inverse(det_mod);
// ... sisanya tetap sama, tapi gunakan det_inv yang didapat di atas
    int inv_key[2][2];
    inv_key[0][0] = d;
    inv_key[0][1] = -b;
    inv_key[1][0] = -c;
    inv_key[1][1] = a;

 for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            inv_key[i][j] = (inv_key[i][j] * det_inv) % 27;
            if (inv_key[i][j] < 0)
                inv_key[i][j] += 27;
        }
    }

 printf("\n--- Matriks Invers ---\n");
    printf("[ %d %d ]\n", inv_key[0][0], inv_key[0][1]);
    printf("[ %d %d ]\n", inv_key[1][0], inv_key[1][1]);

 // Konversi ciphertext ke angka
    int nums[200];
    int len = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++)
        nums[len++] = karakter_ke_angka(ciphertext[i], arr);

    char decrypted[200];



