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
