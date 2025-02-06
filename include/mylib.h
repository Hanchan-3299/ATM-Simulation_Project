#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED


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



// Fungsi login akun dengan batas percobaan PIN 3 kali
Account* login(Account* root, int accountNumber);


// Fungsi untuk menambahkan riwayat transaksi ke stack
void addTransaction(Transaction** top, const char* description);


// Menampilkan riwayat transaksi
void displayTransactions(Transaction* top);


void printTransactionsToFile(Transaction* transactionHistory, const char* filename);


// Fungsi untuk mengatur posisi cursor (hanya untuk terminal yang mendukung VT100)
void gotoxy(int x, int y);


// Fungsi untuk membersihkan layar
void clear();


// Fungsi untuk melanjutkan transaksi
int continueTransaction();


// Fungsi setor (deposit)
void deposite(Account* currentAccount, Transaction** transactionHistory);


// Fungsi untuk penarikan uang
void withdrawal(Account* currentAccount, Transaction** transactionHistory);


// Fungsi untuk mencari akun berdasarkan nomor akun di file tertentu
Account* searchAccountInFile(const char* filename, int accountNumber);


// Fungsi untuk memperbarui akun di file tertentu
void updateAccountInFile(const char* filename, Account* account);


// Fungsi transfer sesama
void transferSesama(Account* currentAccount, Transaction** transactionHistory);


// Fungsi untuk melakukan transfer antar akun
void transfer(Account* currentAccount, Transaction** transactionHistory);


// Fungsi untuk memperbarui saldo di file ambank.txt
void updateAccountBalance(const char* filename, int accountNumber, float newBalance);

void atm(Account* currentAccount);

#endif // MYLIB_H_INCLUDED
