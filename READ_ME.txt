firstly, you have to create database folder. After that, 
create ambank_receipts.txt, ambank.txt, bankutama.txt, and bankutama_receipts.txt 
in database folder to save all transaction

Alur

1. pembuatan akun dengan pin dan saldo awal DILAKUKAN DI BANK_CENTER.C (gunakan exe)
2. penggunaan jasa ATM DILAKUKAN DI BANK.C (gunakan exe)
3. semua data akun disimpan di file BANK.txt di dalam FOLDER DATABASE
4. dan semua Riwayat transaksi disimpan di file RECEIPTS.txt di dalam FOLDER DATABASE




PENTING !!
jika ada file c yang diubah, maka, bila ingin men run program tidak bisa langsung di satu file yang terbuka codeblocks
2 file harus di compile sekaligus yaitu file "main" nya dan yang ada di "src".

ada 2 cara 
1. compile sekaligus di codeblocks dengan project tree
2. yang paling mudah gunakan cmd contoh : gcc bankutama.c src/mylib_bank2.c -o bankutama.exe
   begitu juga dengan file bank lain dan juga center.
   Untuk runnya gunakan .\namaprogram.exe contoh (bankutama.exe)



korelasi file c dengan src nya :
ambank.c dengan mylib_bank1.c
bankutama.c dengan mylib_bank2.c
ambank_center.c dengan mylib_center1.c
bankutama_center.c dengan mylib_center2.c


lainnya :
ambank.txt : penyimpanan ambank
bankutama.txt : penyimpanan bankutama
ambank_receipts.txt : penyimpanan transaksi ambank
bankutama_receipts.txt : penyimpanan transaksi bankutama





data akun

ambank : 
	1. no rek : 123, pw : 123123
	2. 
	3. 


bankutama : 
	1. no rek : 456, pw : 456456
	2. 
	3. 


bisa tambah akun baru, tinggal di buat saja di BANK_CENTER.exe dari masing masing bank yang diinginkan


