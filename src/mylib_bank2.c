#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "../include/mylib.h"




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


// // Fungsi untuk menambahkan akun ke pohon
// Account* addAccount(Account* root, int accountNumber, int pin, float balance) {
//     if (root == NULL) {
//         return createAccount(accountNumber, pin, balance);
//     }
//     if (accountNumber < root->accountNumber) {
//         root->left = addAccount(root->left, accountNumber, pin, balance);
//     } else if (accountNumber > root->accountNumber) {
//         root->right = addAccount(root->right, accountNumber, pin, balance);
//     }
//     return root;
// }

// Fungsi untuk menambahkan atau memperbarui akun di pohon
Account* addAccount(Account* root, int accountNumber, int pin, float balance) {
    if (root == NULL) {
        return createAccount(accountNumber, pin, balance); // Fungsi untuk membuat node baru
    }

    if (accountNumber < root->accountNumber) {
        root->left = addAccount(root->left, accountNumber, pin, balance);
    } else if (accountNumber > root->accountNumber) {
        root->right = addAccount(root->right, accountNumber, pin, balance);
    } else {
        // Jika `accountNumber` sudah ada, perbarui data akun
        root->pin = pin;
        root->balance = balance;
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

// Fungsi login akun dengan batas percobaan PIN 3 kali
Account* login(Account* root, int accountNumber) {
    clear();
    int percobaan = 0;
    char pinInput[7]; // Buffer untuk PIN (6 digit + null terminator)

    while (percobaan < 3) {



        gotoxy(40,13);
        printf("================================================================");
        gotoxy(40,14);
        printf("                         Masukkan PIN:                          ");
        gotoxy(40,15);
        printf("================================================================");
        gotoxy(79,14);


        getMaskedInput(pinInput, 7); // Baca PIN dengan bintang
        int pin = atoi(pinInput); // Konversi ke integer

        Account* account = root;
        while (account != NULL) {
            if (accountNumber == account->accountNumber) {
                if (pin == account->pin) {
                    clear();
                    printf("================================================================");
                    gotoxy(30,14);
                    printf("               PIN benar. Selamat datang, akun %d!              ", accountNumber);
                    gotoxy(30,15);
                    printf("================================================================");


                    return account;
                } else {
                    break;
                }
            }
            account = (accountNumber < account->accountNumber) ? account->left : account->right;
        }

        percobaan++;
        clear();
        printf("PIN salah! Percobaan %d dari 3.\n", percobaan);

        /*
        if (percobaan == 3) {
            printf("Anda telah salah memasukkan PIN sebanyak 3 kali. Login dibatalkan.\n");
            printf("Tekan Enter untuk kembali...");
            getchar();
            getchar();
            return NULL;
        }
        */
    }
    return NULL;
}



/*
// Fungsi untuk login akun dengan batas percobaan PIN 3 kali
Account* login(Account* root, int accountNumber) {
    int percobaan = 0;
    int pin;

    while (percobaan < 3) {
        printf("Masukkan PIN: ");
        scanf("%d", &pin);

        Account* account = root;
        while (account != NULL) {
            if (accountNumber == account->accountNumber) {
                if (pin == account->pin) {
                    clear();
                    printf("PIN benar. Selamat datang, akun %d!\n", accountNumber);
                    return account;
                } else {
                    break;
                }
            }
            account = (accountNumber < account->accountNumber) ? account->left : account->right;
        }

        percobaan++;
        clear();
        printf("PIN salah! Percobaan %d dari 3.\n", percobaan);

        if (percobaan == 3) {
            printf("Anda telah salah memasukkan PIN sebanyak 3 kali. Login dibatalkan.\n");
            printf("Tekan Enter untuk kembali...");
            getchar();
            getchar();
            return NULL;
        }
    }
    return NULL;
}
*/


// Fungsi untuk menambahkan riwayat transaksi ke stack
void addTransaction(Transaction** top, const char* description) {
    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    strcpy(newTransaction->description, description);
    newTransaction->next = *top;
    *top = newTransaction;
}

// Menampilkan riwayat transaksi
void displayTransactions(Transaction* top) {
    Transaction* temp = top;
    printf("Riwayat Transaksi:\n");
    while (temp != NULL) {
        printf("- %s\n", temp->description);
        temp = temp->next;
    }
}

void printTransactionsToFile(Transaction* transactionHistory, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk mencetak riwayat transaksi.\n", filename);
        return;
    }

    fprintf(file, "Riwayat Transaksi:\n");
    Transaction* temp = transactionHistory;
    while (temp != NULL) {
        fprintf(file, "- %s\n", temp->description);
        temp = temp->next;
    }

    fclose(file);
    printf("Riwayat transaksi telah dicetak ke file %s.\n", filename);
}



// Fungsi untuk mengatur posisi cursor (hanya untuk terminal yang mendukung VT100)
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}


// Fungsi untuk membersihkan layar
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



// Fungsi untuk melanjutkan transaksi
int continueTransaction() {
    char choice;

    gotoxy(38,23);
    printf("================================================================");
    gotoxy(38,24);
    printf("         Apakah ingin melakukan transaksi lain? (y/n):          ");
    gotoxy(38,25);
    printf("================================================================");
    gotoxy(91,24);

    getchar();
    scanf("%c", &choice);


    return (choice == 'y' || choice == 'Y') ? 1 : 0;
}

// Fungsi setor (deposit)
void deposite(Account* currentAccount, Transaction** transactionHistory) {
    float amount;

    clear();

    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("        Masukkan jumlah setor (harus kelipatan 50.000):         ");
    gotoxy(38,15);
    printf("================================================================");
    getchar();
    gotoxy(94,14);

    if (scanf("%f", &amount) != 1 || amount <= 0 || (int)amount % 50000 != 0) {

        clear();
        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("              Setor Gagal! Pastikan jumlah valid!               ");
        gotoxy(38,15);
        printf("================================================================");
        return;
    }

    currentAccount->balance += amount;

    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("         Setoran berhasil! Saldo Anda sekarang: Rp. %.2f\n", currentAccount->balance);
    gotoxy(38,15);
    printf("================================================================");

    char description[50];
    sprintf(description, "Setoran: %.2f", amount);
    addTransaction(transactionHistory, description);

    updateAccountBalance("database/bankutama.txt", currentAccount->accountNumber, currentAccount->balance);
}

// Fungsi untuk penarikan uang
void withdrawal(Account* currentAccount, Transaction** transactionHistory) {
    float amount;

    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("     Masukkan jumlah penarikan (harus kelipatan 50.000):        ");
    gotoxy(38,15);
    printf("================================================================");
    getchar();
    gotoxy(95,14);


    if (scanf("%f", &amount) != 1 || amount <= 0 || (int)amount % 50000 != 0 || currentAccount->balance <= 50000) {
        clear();
        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("           Penarikan Gagal! Pastikan jumlah valid.              ");
        gotoxy(38,15);
        printf("================================================================");

        return;
    }

    if (amount > currentAccount->balance) {
        clear();
        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("                        Saldo tidak cukup!                      \n");
        gotoxy(38,15);
        printf("================================================================");

    } else {
        currentAccount->balance -= amount;
    clear();

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("       Penarikan berhasil! Saldo Anda sekarang: Rp. %.2f\n          ", currentAccount->balance);
        gotoxy(38,15);
        printf("================================================================");



        char description[50];
        sprintf(description, "Penarikan: %.2f", amount);
        addTransaction(transactionHistory, description);

        updateAccountBalance("database/bankutama.txt", currentAccount->accountNumber, currentAccount->balance);
    }
}


// Fungsi untuk mencari akun berdasarkan nomor akun di file tertentu
Account* searchAccountInFile(const char* filename, int accountNumber) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", filename);
        return NULL;
    }

    Account* account = NULL;
    int accNumber, pin;
    float balance;

    while (fscanf(file, "%d %d %f\n", &accNumber, &pin, &balance) == 3) {
        if (accNumber == accountNumber) {
            account = createAccount(accNumber, pin, balance);
            break;
        }
    }

    fclose(file);
    return account;
}

// Fungsi untuk memperbarui akun di file tertentu
void updateAccountInFile(const char* filename, Account* account) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk pembaruan.\n", filename);
        return;
    }

    int accNumber;
    long pos;
    while (fscanf(file, "%d", &accNumber) != EOF) {
        pos = ftell(file);
        if (accNumber == account->accountNumber) {
            fseek(file, pos + sizeof(int) + sizeof(int), SEEK_SET);
            fprintf(file, "%.2f\n", account->balance);
            break;
        }
        fseek(file, pos, SEEK_SET);
    }

    fclose(file);
}

// Fungsi transfer sesama
void transferSesama(Account* currentAccount, Transaction** transactionHistory) {
    int targetAccountNumber;
    float transferAmount;

    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                 Masukkan nomor akun tujuan:                    ");
    gotoxy(38,15);
    printf("================================================================");
    gotoxy(83,14);

    scanf("%d", &targetAccountNumber);

    // Validasi nomor akun tujuan tidak sama dengan akun sekarang
    if (targetAccountNumber == currentAccount->accountNumber) {

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("         Transfer ke akun sendiri tidak diperbolehkan!          ");
        gotoxy(38,15);
        printf("================================================================");
        return;
    }

    // Mencari akun tujuan di file txt
    Account* targetAccount = searchAccountInFile("database/bankutama.txt", targetAccountNumber);
    if (targetAccount == NULL) {

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("                  Akun tujuan tidak ditemukan!                  ");
        gotoxy(38,15);
        printf("================================================================");
        return;
    }


    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                  Masukkan jumlah transfer:                     ");
    gotoxy(38,15);
    printf("================================================================");
    gotoxy(83,14);


    if (scanf("%f", &transferAmount) != 1 || transferAmount <= 0 || transferAmount > currentAccount->balance || currentAccount->balance <= 50000) {

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("    Transfer gagal! Pastikan jumlah valid dan saldo mencukupi   ");
        gotoxy(38,15);
        printf("================================================================");
        free(targetAccount);
        return;
    }

    // Melakukan transfer
    currentAccount->balance -= transferAmount;
    targetAccount->balance += transferAmount;

    // Perbarui saldo di file txt
    updateAccountBalance("database/bankutama.txt", currentAccount->accountNumber, currentAccount->balance);
    updateAccountBalance("database/bankutama.txt", targetAccount->accountNumber, targetAccount->balance);

    clear();

    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("       Transfer berhasil! Saldo Anda sekarang: Rp. %.2f        ", currentAccount->balance);
    gotoxy(38,15);
    printf("================================================================");

    // Tambahkan riwayat transaksi
    char description[100];
    sprintf(description, "Transfer ke akun %d: %.2f", targetAccountNumber, transferAmount);
    addTransaction(transactionHistory, description);

    free(targetAccount);
}


// Fungsi untuk melakukan transfer antar akun
void transfer(Account* currentAccount, Transaction** transactionHistory) {
    int targetAccountNumber;
    float transferAmount;

    clear();
    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                 Masukkan nomor akun tujuan:                    ");
    gotoxy(38,15);
    printf("================================================================");
    gotoxy(83,14);

    scanf("%d", &targetAccountNumber);

    // Mencari akun penerima di file txt bank kedua
    Account* targetAccount = searchAccountInFile("database/ambank.txt", targetAccountNumber);
    if (targetAccount == NULL) {

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("                   Akun penerima tidak ditemukan!               ");
        gotoxy(38,15);
        printf("================================================================");
        return;
    }


    clear();

    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("                  Masukkan jumlah transfer:                     ");
    gotoxy(38,15);
    printf("================================================================");
    gotoxy(83,14);


    if (scanf("%f", &transferAmount) != 1 || transferAmount <= 0 || transferAmount > currentAccount->balance || currentAccount->balance <= 50000) {

        clear();


        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("    Transfer gagal! Pastikan jumlah valid dan saldo mencukupi   ");
        gotoxy(38,15);
        printf("================================================================");
        return;
    }

    gotoxy(38,13);
    printf("================================================================");
    gotoxy(38,14);
    printf("       Detail Transfer :       Nominal     : Rp. %.2f           ", transferAmount);
    gotoxy(38,15);
    printf("                               Biaya Admin : Rp. 2500           ");
    gotoxy(38,16);
    printf("                               Total       : Rp. %.2f           ", transferAmount + 2500);
    gotoxy(38,17);
    printf("================================================================");
    
    gotoxy(33,23);
    printf("============================================================================");
    gotoxy(33,24);
    printf("          Apakah anda yakin ingin melakukan transaksi ? (y/n):              ");
    gotoxy(33,25);
    printf("============================================================================");


    getchar();
    gotoxy(100,24);

    char choice;
    scanf("%c", &choice);

    if (choice == 'y' || choice == 'Y') {
        // Melakukan transfer
        currentAccount->balance -= (transferAmount + 2500);
        targetAccount->balance += transferAmount;

        // Menyimpan saldo yang sudah diperbarui ke file
        updateAccountBalance("database/bankutama.txt", currentAccount->accountNumber, currentAccount->balance);
        updateAccountBalance("database/ambank.txt", targetAccount->accountNumber, targetAccount->balance);
        // updateAccountInFile("database/ambank.txt", targetAccount);  // Update akun penerima di txt bank kedua



        clear();

        gotoxy(38,13);
        printf("================================================================");
        gotoxy(38,14);
        printf("       Transfer berhasil! Saldo Anda sekarang: Rp. %.2f        ", currentAccount->balance);
        gotoxy(38,15);
        printf("================================================================");

        char description[100];
        sprintf(description, "Transfer ke akun %d: %.2f", targetAccountNumber, transferAmount);
        addTransaction(transactionHistory, description);

        free(targetAccount);  // Menghapus akun penerima dari memori setelah penggunaan
    } else if (choice == 'n' || choice == 'N'){
        clear();
        gotoxy(38,10);
        printf("================================================================");
        gotoxy(38,11);
        printf("                       Transaksi Dibatalkan                     ");
        gotoxy(38,12);
        printf("================================================================");   

    }
}





// Fungsi untuk memperbarui saldo di file txt
void updateAccountBalance(const char* filename, int accountNumber, float newBalance) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Gagal membuka file untuk pembaruan saldo.\n");
        return;
    }

    FILE* tempFile = fopen("database/temp_bankutama.txt", "w");
    if (tempFile == NULL) {
        printf("Gagal membuka file sementara.\n");
        fclose(file);
        return;
    }

    int accNumber, pin;
    float balance;
    while (fscanf(file, "%d %d %f\n", &accNumber, &pin, &balance) == 3) {
        if (accNumber == accountNumber) {
            balance = newBalance; // Update saldo
        }
        fprintf(tempFile, "%d %d %.2f\n", accNumber, pin, balance);
    }

    fclose(file);
    fclose(tempFile);
    remove(filename);
    rename("database/temp_bankutama.txt", filename);
}





// Fungsi ATM
void atm(Account* currentAccount) {
    Transaction* transactionHistory = NULL;
    int choice;

    while (1) {
        clear();
        gotoxy(37,5);
        printf("================================================================\n");
        gotoxy(37,6);
        printf("=====                       ATM Menu                       =====\n");
        gotoxy(37,7);
        printf("================================================================\n");


        gotoxy(5,13);
        printf("==============================");
        gotoxy(5,14);
        printf("===   1    Cek Saldo       ===");
        gotoxy(5,15);
        printf("==============================");


        gotoxy(103,13);
        printf("==============================");
        gotoxy(103,14);
        printf("===     Penarikan Uang  2  ===");
        gotoxy(103,15);
        printf("==============================");

        gotoxy(5,18);
        printf("==============================");
        gotoxy(5,19);
        printf("===   3     Setor Uang     ===");
        gotoxy(5,20);
        printf("==============================");


        gotoxy(103,18);
        printf("==============================");
        gotoxy(103,19);
        printf("===        Transfer     4  ===");
        gotoxy(103,20);
        printf("==============================");



        gotoxy(53,23);
        printf("==============================");
        gotoxy(53,24);
        printf("===         Keluar         ===");
        gotoxy(53,25);
        printf("============   5   ===========");

        gotoxy(5,27);
        printf("===================");
        gotoxy(5,28);
        printf("    Pilih :  ");
        gotoxy(5,29);
        printf("===================");
        gotoxy(18,28);


        scanf("%d", &choice);




        switch (choice) {
            case 1:
                clear();
                gotoxy(54,13);
                printf("==============================");
                gotoxy(54,14);
                printf("   Saldo Anda: Rp. %.2f         ", currentAccount->balance);
                gotoxy(54,15);
                printf("==============================");
                addTransaction(&transactionHistory, "Cek saldo");


                break;

            case 2:
                clear();
                withdrawal(currentAccount, &transactionHistory);
                break;

            case 3:
                clear();
                deposite(currentAccount, &transactionHistory);
                break;


            case 4: {
                clear();
                int choice1;

                gotoxy(5,10);
                printf("===============================");
                gotoxy(5,11);
                printf("== (1) Transfer Sesama Bank  ==\n");
                gotoxy(5,12);
                printf("===============================");



                gotoxy(103,10);
                printf("===============================");
                gotoxy(103,11);
                printf("==   Transfer Antar Bank (2) ==\n");
                gotoxy(103,12);
                printf("===============================");


                gotoxy(54,18);
                printf("==============================");
                gotoxy(54,19);
                printf("===         Kembali        ===\n");
                gotoxy(54,20);
                printf("============   3   ===========");


                gotoxy(5,22);
                printf("===================");
                gotoxy(5,23);
                printf("      Pilih :  ");
                gotoxy(5,24);
                printf("===================");
                gotoxy(19,23);


                scanf("%d", &choice1);
                switch (choice1) {
                    case 1:
                        transferSesama(currentAccount, &transactionHistory);
                        break;
                    case 2:
                        transfer(currentAccount, &transactionHistory);
                        break;
                    case 3 :
                        continue;

                    default:
                        printf("Pilihan tidak valid.\n");
                }
                break;
            }


            case 5:
                clear();



                char printChoice;

                gotoxy(33,16);
                printf("============================================================================");
                gotoxy(33,17);
                printf("             Apakah ingin mencetak riwayat transaksi ? (y/n):               ");
                gotoxy(33,18);
                printf("============================================================================");


                getchar();
                gotoxy(100,17);


                scanf("%c", &printChoice);

                if (printChoice == 'y' || printChoice == 'Y') {
                    printTransactionsToFile(transactionHistory, "database/bankutama-receipts.txt");
                }

                clear();
                getchar();
                gotoxy(33,16);
                printf("============================================================================");
                gotoxy(33,17);
                printf("             Terima kasih telah menggunakan layanan BANK UTAMA              ");
                gotoxy(33,18);
                printf("============================================================================");

                getchar();
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }

        if (!continueTransaction()) {
            clear();


            printf(".\n");
            char printChoice;

            gotoxy(33,16);
            printf("============================================================================");
            gotoxy(33,17);
            printf("             Apakah ingin mencetak riwayat transaksi ? (y/n):               ");
            gotoxy(33,18);
            printf("============================================================================");

            getchar();
            gotoxy(101,17);

            scanf("%c", &printChoice);

            if (printChoice == 'y' || printChoice == 'Y') {
                printTransactionsToFile(transactionHistory, "database/bankutama-receipts.txt");
            }

            clear();
            gotoxy(33,16);
            printf("============================================================================");
            gotoxy(33,17);
            printf("             Terima kasih telah menggunakan layanan BANK UTAMA              ");
            gotoxy(33,18);
            printf("============================================================================");

            return;
        }
    }
}

