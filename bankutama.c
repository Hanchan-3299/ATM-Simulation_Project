#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "include/mylib.h"


int main (){
    clear();


    Account* root = loadAccountsFromFile(); // Membaca akun dari file saat aplikasi dijalankan


    gotoxy(18,8);
    printf("  ___   ___   _        _     __  __     _     _____        ___      _     _____     _     _  _    ___ \n");
    gotoxy(18,9);
    printf(" / __| | __| | |      /_\\   |  \\/  |   /_\\   |_   _|      |   \\    /_\\   |_   _|   /_\\   | \\| |  / __|\n");
    gotoxy(18,10);
    printf(" \\__ \\ | _|  | |__   / _ \\  | |\\/| |  / _ \\    | |        | |) |  / _ \\    | |    / _ \\  | .` | | (_ |\n");
    gotoxy(18,11);
    printf(" |___/ |___| |____| /_/ \\_\\ |_|  |_| /_/ \\_\\   |_|        |___/  /_/ \\_\\   |_|   /_/ \\_\\ |_|\\_|  \\___|\n");


    gotoxy(63,14);
    printf("  ___    ___ \n");
    gotoxy(63,15);
    printf(" |   \\  |_ _|\n");
    gotoxy(63,16);
    printf(" | |) |  | | \n");
    gotoxy(63,17);
    printf(" |___/  |___|\n");



    gotoxy(35,21);
    printf("  ___     _     _  _   _  __     _   _   _____     _     __  __     _   \n");
    gotoxy(35,22);
    printf(" | _ )   /_\\   | \\| | | |/ /    | | | | |_   _|   /_\\   |  \\/  |   /_\\  \n");
    gotoxy(35,23);
    printf(" | _ \\  / _ \\  | .` | | ' <     | |_| |   | |    / _ \\  | |\\/| |  / _ \\ \n");
    gotoxy(35,24);
    printf(" |___/ /_/ \\_\\ |_|\\_| |_|\\_\\     \\___/    |_|   /_/ \\_\\ |_|  |_| /_/ \\_\\\n");



    getchar();
    clear();

    int accountNumber;

    gotoxy(40,13);
    printf("================================================================");
    gotoxy(40,14);
    printf("                   Masukkan nomor akun Anda: ");
    gotoxy(40,15);
    printf("================================================================");
    gotoxy(85,14);



    scanf("%d", &accountNumber);

    Account* account = login(root, accountNumber);
    if (account != NULL) {
        atm(account); // Langsung ke ATM setelah login
    } else {
        clear();

        gotoxy(40,13);
        printf("================================================================");
        gotoxy(40,14);
        printf("                 Login gagal. Silakan coba lagi!                ");
        gotoxy(40,15);
        printf("================================================================");
        gotoxy(40, 25);
        printf("");
    }
    return 0;


}
