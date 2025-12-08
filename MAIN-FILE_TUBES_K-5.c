// Tugas besar kelompok 5
// - Ghibran Sultan Alfarabi - 251402031
// - Andika Chairul Ilham - 251402047
// - Muhammad Fakhry Adrian Daulay - 251402053
// - Siti Naifah Batubara - 251402067
// - Syifa Nazira - 251402126

#include <stdio.h>
#include <stdlib.h> // <-- untuk abs()

// ==== WARNA OUTPUT TERMINAL ==== //
#define RESET "\033[0m"
#define FG_RED "\033[91m"
#define FG_GREEN "\033[92m"
#define FG_YELLOW "\033[93m"
#define FG_BLUE "\033[94m"
#define FG_WHITE "\033[97m"

#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"

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

void rekursif(int nums[], int index, int len,
              int matrix[2][2],
              char arr[],
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

    printf(FG_BLUE "\n--- Proses Enkripsi ---\n" RESET);

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
        printf(BG_RED FG_WHITE " Gagal membuat file output_enkripsi.txt! " RESET "\n");
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
        printf(FG_GREEN "\nFile 'output_enkripsi.txt' berhasil dibuat.\n" RESET);
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

    printf(FG_BLUE "\n--- Proses Dekripsi (Menggunakan Matriks Invers) ---\n" RESET);
    printf("[ %d %d ]\n", inv_key[0][0], inv_key[0][1]);
    printf("[ %d %d ]\n", inv_key[1][0], inv_key[1][1]);

    // Konversi ciphertext ke angka
    int nums[200];
    int len = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++)
        nums[len++] = karakter_ke_angka(ciphertext[i], arr);

    char decrypted[200];
    int dec_i = 0;

    // PANGGIL REKURSI pakai inverse key
    rekursif(nums, 0, len, inv_key, arr, decrypted, &dec_i);

    decrypted[dec_i] = '\0';

    printf("\nHasil dekripsi : %s\n", decrypted);

    FILE *fdec = fopen("decrypted.txt", "w");
    if (fdec == NULL)
    {
        printf(BG_RED FG_WHITE " Gagal membuat file decrypted.txt! " RESET "\n");
    }
    else
    {
        fprintf(fdec, "%s", decrypted);
        fclose(fdec);
        printf(FG_GREEN "\nFile 'decrypted.txt' berhasil dibuat.\n" RESET);
    }
}

int key_valid(int key[2][2])
{
    int a = key[0][0], b = key[0][1];
    int c = key[1][0], d = key[1][1];

    // cek semua elemen sama
    if (a == b && b == c && c == d)
    {
        return 0;
    }

    int det = a * d - b * c;

    det %= 27;
    if (det < 0)
        det += 27;

    // determinan tidak boleh 0
    if (det == 0)
        return 0;

    // determinan harus punya invers modulo 27
    if (mod_inverse(det) == -1)
        return 0;

    return 1; // valid
}

int main()
{
    void enkripsi(char plaintext[], int key[2][2], char arr[]);
    void dekripsi(char ciphertext[], int key[2][2], char arr[]);

    char arr[27];
    arr[0] = ' ';
    for (int i = 1; i <= 26; i++)
    {
        arr[i] = 'a' + (i - 1);
    }

    int b1k1, b1k2, b2k1, b2k2;
    char plaintext[200];

    // Input plaintext
    printf("Teks yang mau diubah: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (plaintext[i] == '\n')
        {
            plaintext[i] = '\0';
            break;
        }
    }

    // Input key
    int key[2][2];

    while (1)
    {
        printf("Input key baris pertama kolom pertama : ");
        scanf("%d", &key[0][0]);
        printf("Input key baris pertama kolom kedua   : ");
        scanf("%d", &key[0][1]);
        printf("Input key baris kedua kolom pertama   : ");
        scanf("%d", &key[1][0]);
        printf("Input key baris kedua kolom kedua     : ");
        scanf("%d", &key[1][1]);

        if (key_valid(key))
        {
            printf(FG_GREEN "\nKunci VALID. siap dijalankan.\n\n" RESET);
            break;
        }
        else
        {
            printf(BG_RED FG_WHITE "\n Kunci TIDAK VALID! \n" RESET);
            printf(FG_YELLOW "Pastikan:\n" RESET);
            printf(FG_YELLOW "- Determinan tidak sama dengan 0\n" RESET);
            printf(FG_YELLOW "- Determinan memiliki invers modulo 27\n" RESET);
            printf(FG_YELLOW "- Tidak semua elemen matriks sama\n" RESET);
            printf(FG_YELLOW "Silahkan input ulang.\n\n" RESET);
        }
    }

    // Pilih fungsi
    char pilihan;
    do
    {
        printf("1. Enkripsi\n2. Dekripsi\nPilih proses yang akan dijalankan: ");
        scanf(" %c", &pilihan); // spasi penting untuk mengabaikan newline sebelumnya

        if (pilihan == '1')
        {
            enkripsi(plaintext, key, arr);
        }
        else if (pilihan == '2')
        {
            dekripsi(plaintext, key, arr);
        }
        else
        {
            printf("Input tidak valid. Tidak ada fungsi yang dijalankan.\n");
            printf("Silahkan input karakter yang sesuai.\n");
        }
    } while (pilihan != '1' && pilihan != '2');
    return 0;
}


