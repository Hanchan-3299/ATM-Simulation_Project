#ifndef MYLIB_CENTER_H_INCLUDED
#define MYLIB_CENTER_H_INCLUDED


// Struktur untuk data akun (Node pada tree)
typedef struct Account {
    int accountNumber;
    int pin;
    float balance;
    struct Account* left;
    struct Account* right;
} Account;


// Struktur untuk riwayat transaksi (stack)
typedef struct Transaction {
    char description[50];
    struct Transaction* next;
} Transaction;


// Fungsi untuk membersihkan layar
void clear();


void gotoxy(int x, int y);



// Fungsi untuk membuat akun baru
Account* createAccount(int accountNumber, int pin, float balance);


// Fungsi untuk menambahkan akun ke pohon
Account* addAccount(Account* root, int accountNumber, int pin, float balance);



// Fungsi untuk membaca akun dari file
Account* loadAccountsFromFile();



// Fungsi untuk menyimpan akun ke file
void saveAccountsToFile(Account* root);


// Fungsi untuk membaca input PIN dan menggantinya dengan bintang (*)
void getMaskedInput(char* inputBuffer, int maxLength);



void create (Account **root);


#endif // MYLIB_CENTER_H_INCLUDED
