#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "include/mylib_center.h"


int main() {
    clear();

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



    gotoxy(45,21);
    printf("    _     __  __   ___     _     _  _   _  __\n");
    gotoxy(45,22);
    printf("   /_\\   |  \\/  | | _ )   /_\\   | \\| | | |/ /\n");
    gotoxy(45,23);
    printf("  / _ \\  | |\\/| | | _ \\  / _ \\  | .` | | ' < \n");
    gotoxy(45,24);
    printf(" /_/ \\_\\ |_|  |_| |___/ /_/ \\_\\ |_|\\_| |_|\\_\\\n");

    getchar();
    Account* root = loadAccountsFromFile(); // Membaca akun dari file saat aplikasi dijalankan
    create(&root);
    return 0;
}
