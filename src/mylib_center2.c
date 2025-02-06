#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "../include/mylib_center.h"



// Fungsi untuk membersihkan layar
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}



// Fungsi untuk membuat akun baru
Account* createAccount(int accountNumber, int pin, float balance) {
    Account* newAccount = (Account*)malloc(sizeof(Account));
    newAccount->accountNumber = accountNumber;
    newAccount->pin = pin;
    newAccount->balance = balance;
    newAccount->left = NULL;
    newAccount->right = NULL;
    return newAccount;
}


// Fungsi untuk menambahkan akun ke pohon
Account* addAccount(Account* root, int accountNumber, int pin, float balance) {
    if (root == NULL) {
        return createAccount(accountNumber, pin, balance);
    }
    if (accountNumber < root->accountNumber) {
        root->left = addAccount(root->left, accountNumber, pin, balance);
    } else if (accountNumber > root->accountNumber) {
        root->right = addAccount(root->right, accountNumber, pin, balance);
    }
    return root;
}



// Fungsi untuk membaca akun dari file
Account* loadAccountsFromFile() {
    FILE* file = fopen("database/bankutama.txt", "r");
    if (file == NULL) {
        return NULL;
    }

    Account* root = NULL;
    int accountNumber, pin;
    float balance;

    while (fscanf(file, "%d %d %f\n", &accountNumber, &pin, &balance) == 3) {
        root = addAccount(root, accountNumber, pin, balance);
    }

    fclose(file);
    return root;
}



// Fungsi untuk menyimpan akun ke file
void saveAccountsToFile(Account* root) {
    if (root == NULL) {
        return;
    }

    FILE* file = fopen("database/bankutama.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data akun.\n");
        return;
    }

    fprintf(file, "%d %d %.2f\n", root->accountNumber, root->pin, root->balance);
    fclose(file);

    saveAccountsToFile(root->left);
    saveAccountsToFile(root->right);
}


// Fungsi untuk membaca input PIN dan menggantinya dengan bintang (*)
void getMaskedInput(char* inputBuffer, int maxLength) {
    int index = 0;
    char ch;

    while (index < maxLength) {
        ch = getch(); // Membaca satu karakter tanpa menampilkan

        if (ch == '\r') { // Enter (mengakhiri input)
            inputBuffer[index] = '\0';
            break;
        } else if (ch == '\b') { // Backspace
            if (index > 0) {
                printf("\b \b"); // Hapus karakter di layar
                index--;
            }
        } else if (ch >= '0' && ch <= '9') { // Hanya angka yang diterima
            if (index < maxLength - 1) {
                inputBuffer[index++] = ch;
                printf("*"); // Tampilkan bintang
            }
        }
    }
}


// Fungsi untuk memeriksa apakah akun dengan nomor tertentu sudah ada di file
int isAccountExistInFile(const char* filename, int accountNumber) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // File tidak ditemukan, anggap akun belum ada
    }

    int accNumber, pin;
    float balance;
    
    // Membaca setiap baris untuk memeriksa nomor akun
    while (fscanf(file, "%d %d %f\n", &accNumber, &pin, &balance) == 3) {
        if (accNumber == accountNumber) {
            fclose(file);
            return 1; // Akun ditemukan
        }
    }

    fclose(file);
    return 0; // Akun tidak ditemukan
}


void create (Account **root){
    clear();
    int accountNumber;
    char pinInput[7]; // Buffer untuk PIN (6 digit + null terminator)
    float balance;

    do {
        clear();
        gotoxy(38, 13);
        printf("================================================================");
        gotoxy(38, 14);
        printf("                 Masukkan nomor akun baru:                      ");
        gotoxy(38, 15);
        printf("================================================================");
        gotoxy(81, 14);
        scanf("%d", &accountNumber);

        // Cek apakah nomor akun sudah ada di file
        if (isAccountExistInFile("database/bankutama.txt", accountNumber)) {
            clear();
            gotoxy(33, 13);
            printf("==========================================================================");
            gotoxy(33, 14);
            printf("        Nomor akun %d sudah ada. Coba lagi dengan nomor akun lain.        ", accountNumber);
            gotoxy(33, 15);
            printf("==========================================================================");
            getchar(); // Clear buffer
            getchar(); // Clear buffer
        }
    } while (isAccountExistInFile("database/bankutama.txt", accountNumber)); // Ulangi jika nomor akun sudah ada

    do {
        clear();

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("                   Masukkan PIN baru (6 digit):                 ");
        gotoxy(38,15);
        printf("================================================================");
        gotoxy(86,14);

        getMaskedInput(pinInput, 7);
        if (strlen(pinInput) != 6 || atoi(pinInput) < 0) {
            printf("\nPIN harus 6 digit angka. Coba lagi.\n");
        }
    } while (strlen(pinInput) != 6 || atoi(pinInput) < 0);

    int pin = atoi(pinInput); // Konversi string PIN ke integer

    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                      Masukkan saldo awal:                      ");
    gotoxy(38,15);
    printf("================================================================");
    gotoxy(81,14);

    scanf("%f", &balance);

    *root = addAccount(*root, accountNumber, pin, balance);
    saveAccountsToFile(*root); // Simpan akun yang baru dibuat ke file
    clear();

    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                      Akun berhasil dibuat!                     ");
    gotoxy(38,15);
    printf("================================================================");

    getchar();
    getchar();


    gotoxy(38,20);
    printf("================================================================");
    gotoxy(38,21);
    printf("            Terimakasih telah mempercayai BANK UTAMA            ");
    gotoxy(38,22);
    printf("================================================================");

    getchar();


}
