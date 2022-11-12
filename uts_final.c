// Program ini berfungsi untuk melakukan pembelian tiker untuk bus primajasa

// DEKLARASI STRUCT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

// DEKLARASI STRUCT
// Model untuk trayek
typedef struct {
	char nama[120];
	char jam_berangkat[3][6];
	char jam_tiba[3][6];
	long harga_ekonomi[2];
	long harga_bisnis[2];
	long harga_vip[2];
} Trayek;

// Model Untuk Tiket
typedef struct {
	int no_trayek;
	int no_kursi;
	char kelas;
	char jam_berangkat[6];
	char jam_tiba[6];
	long long harga;
} Tiket;

// Model Untuk Penumpang
typedef struct {
	char nik[10];
	char nama[120];
	char tgl_lahir[12];
	char tempat_lahir[120];
	char no_tel[10];
	char alamat[120];
	Tiket tiket_normal[4]; // jumlah tiket yang bisa dibeli selain tipe VIP
	Tiket tiket_vip[2]; // jumlah tiket yang bisa dibeli selain tipe VIP
} Penumpang;

// Model Untuk Bus
typedef struct {
	Trayek trayek;
	Penumpang kursi_ekonomi[60];
	Penumpang kursi_bisnis[50];
	Penumpang kursi_vip[35];
} Bus;


// DEKLARASI GLOBAL VARIABLE
// variable terkait database
Trayek db_trayek[4]; // database berisi data terkait trayek
Bus db_bus[4]; // database berisi data terkait bus
Penumpang db_penumpang[200]; // database berisi data terkait 
long long total_profit; // menampung data keuangan perusahaan
int input_menu; // menampung input menu dari user
int x, y, z; // variable untuk index pada for loop
int jml_pembeli = 0;

// DEKLARASI PROSEDUR VIEWS
// Deklarasi prosedur bertipe menu
void menu_router_utama(int *input_menu);
void menu_router_db(int *input_menu);
void menu_input_data_penumpang();
// Deklarasi prosedur bertipe menu
void form_input_data_diri();
void form_input_data_tiket();
// Deklarasi prosedur bertipe tabel
void tabel_kursi();
void tabel_jadwal();
void tabel_pembeli();
void tabel_pemesanan();
void tabel_riwayat_perjalanan();

// DEKLRASI PROSEDUR UTILITY
// util_print_center digunakan untuk mencetak sebuah string pada posisi tengah pada panjang 'len'
void util_print_center(char *prefix, char *str, char *div, int len, char *suffix);

// util_print_repeat digunakan untuk mencetak sebuah string sebanyak 'len' kali
void util_print_repeat(char *prefix, char *str, int len, char *suffix);

// util_back_to_menu digunakan untuk mencetak sebuah string sebanyak 'len' kali
void util_back_to_menu();

// DEKLARASI PROSEDUR DB
void db_trayek_init();
void db_bus_init();

// DEKLARASI ALGORITMA
int main() {
	// memanggil prosedur penginisialisasi database
	db_trayek_init();
	db_bus_init();

	// memanggil prosedur ini untuk memulai program
	menu_router_utama(&input_menu);
	
	// jika user keluar dari menu utama
	system("cls");
	printf("Terima Kasih Telah Menggunakan Jasa Bus Primajasa !");
	return 0;
}

// DEFINISI PROSEDUR
void menu_router_utama(int *input_menu) {
	while (true) {
		system("cls");
		util_print_center("+", "JASA BUS PRIMAJASA", "-", 25, "+\n");
		printf("| 1. Beli Tiket Bus  	 |\n");	
		printf("| 2. Lihat Database 	 |\n");	
		printf("| 3. Keluar Dari Program |\n");	
		util_print_repeat("+", "-", 24, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", input_menu);
		
		// percabangan router menu utama ketika user sudah menginput pilihan menu
		if (*input_menu == 1) {
			menu_input_data_penumpang();			
		} else if (*input_menu == 2) {
			menu_router_db(input_menu);
		} else if (*input_menu == 3) {
			break;	
		} 
	}
}
void menu_router_db(int *input_menu) {
	while (true) {
		system("cls");
		util_print_center("+", "DATABASE PRIMAJASA", "-", 28, "+\n");
		printf("| 1. List Jadwal Perjalanan  |\n");	
		printf("| 2. Data Pembeli            |\n");	
		printf("| 3. Data Pemesanan          |\n");	
		printf("| 4. List Riwayat Perjalanan |\n");	
		printf("| 5. Kembali Ke Menu Utama   |\n");	
		util_print_repeat("+", "-", 28, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", input_menu);
		
		// percabangan router database ketika user sudah menginput pilihan menu
		if (*input_menu == 1) {
			system("cls");
			tabel_jadwal();			
		} else if (*input_menu == 2) {
			system("cls");
			tabel_pembeli();
		} else if (*input_menu == 3) {
			system("cls");
			tabel_pemesanan();
		} else if (*input_menu == 4) {
			system("cls");
			tabel_riwayat_perjalanan();
		} else if (*input_menu == 5) {
			break;
		} 
	}
}
void menu_input_data_penumpang() {
	form_input_data_diri();
	form_input_data_tiket();
	
	util_back_to_menu();
}

void form_input_data_diri() {
	system("cls");
	util_print_center("\n", "Form Data Diri", " ", 50, "\n");
	util_print_repeat("", "-", 50, "\n");	
	
	do {
		printf("1. Masukkan NIK Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].nik);
	} while (strlen(db_penumpang[jml_pembeli].nik) == 0);
	
	do {
		printf("2. Masukkan Nama Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].nama);
	} while (strlen(db_penumpang[jml_pembeli].nama) == 0);
	
	do {
		printf("3. Masukkan Tempat Lahir Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].tempat_lahir);
	} while (strlen(db_penumpang[jml_pembeli].tempat_lahir) == 0);
	
	do {
		printf("4. Masukkan Tanggal Lahir Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].tgl_lahir);
	} while (strlen(db_penumpang[jml_pembeli].tgl_lahir) == 0);

	do {
		printf("5. Masukkan Alamat Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].alamat);
	} while (strlen(db_penumpang[jml_pembeli].alamat) == 0);
	
	do {
		printf("6. Masukkan Nomor Telepon Anda: ");
		fflush(stdin);
		gets(db_penumpang[jml_pembeli].no_tel);
	} while (strlen(db_penumpang[jml_pembeli].no_tel) == 0);
}
void form_input_data_tiket() {
	char tipe_tiket_dibeli; // tipe tiket yang ingin dibeli oleh penumpang
	int jml_tiket_dibeli; // jumlah tiket yang ingin dibeli oleh penumpang
	
	system("cls");
	util_print_center("\n", "Form Data Tiket", " ", 50, "\n");
	util_print_repeat("", "-", 50, "\n");	
	
	do {
		util_print_repeat("+", "-", 22, "+\n");	
		util_print_center("|", "Tipe Tiket", " ", 20, "|\n");
		util_print_repeat("+", "-", 22, "+\n");	
		util_print_center("|", "1. Ekonomi (e)", " ", 20, "|\n");
		util_print_center("|", "2. Bisnis (b)", " ", 20, "|\n");
		util_print_center("|", "3. VIP (v)", " ", 20, "|\n");
		util_print_repeat("+", "-", 22, "+\n");	
		
		printf("1. Masukkan Tipe Tiket Yang Ingin Dibeli: ");
		fflush(stdin);
		scanf("%c", &tipe_tiket_dibeli);
	} while (!tipe_tiket_dibeli);
	
	
}
 
void tabel_kursi() {
	printf("hello kursi");
	util_back_to_menu();	
}
void tabel_jadwal() {
	// header table atas jadwal
	util_print_center("|", "No", " ", 5, "|");
	util_print_center("", "Trayek", " ", 24, "|");
	util_print_center("", "Waktu", " ", 29, "|");
	util_print_center("", "Harga Kelas Bus", " ", 36, "|\n");

	// header table bawah jadwal
	util_print_repeat("|", " ", 28, "|");
	util_print_center("", "Berangkat", " ", 15, "|");
	util_print_center("", "Kedatangan", " ", 14, "|");
	util_print_center("", "Ekonomi", " ", 12, "|");
	util_print_center("", "Bisnis", " ", 12, "|");
	util_print_center("", "VIP", " ", 11, "|");
	util_back_to_menu();
}
void tabel_pembeli() {
	printf("hello pembeli");
	util_back_to_menu();
}
void tabel_pemesanan() {
	printf("hello pemesanan");
	util_back_to_menu();
}
void tabel_riwayat_perjalanan() {
	printf("hello riwayat perjalanan");
	util_back_to_menu();
}

void util_print_center(char *prefix, char *str, char *div, int len, char *suffix) {
	int str_len = strlen(str);
	int margin = len - str_len;
	int margin_kiri = margin / 2;
	int margin_kanan = margin / 2;
	
	
	printf("%s", prefix); // mencetak string awalan
	
	// mencetak margin kiri
	for (z = 0; z < margin_kiri; z++) {
		printf("%s", div);
	}
	
	// mencetak string utama
	printf("%s", str);
	
	// mencetak margin kanan
	for (z = 0; z < margin_kanan; z++) {
		printf("%s", div);
	}
	
	printf("%s", suffix); // mencetak string akhiran
}
void util_print_repeat(char *prefix, char *str, int len, char *suffix) {
	printf("%s", prefix); // mencetak string awalan
	
	// mencetak margin kiri
	for (z = 0; z < len; z++) {
		printf("%s", str);
	}
	
	printf("%s", suffix); // mencetak string akhiran
}
void util_back_to_menu() {
	printf("\nKlik apa saja untuk kembali ke menu sebelumnya");
	getche();
}

void db_trayek_init() {
	// inisialisasi nama trayek
	strcpy(db_trayek[0].nama, "Lebak Bulus - Pasteur");	
	strcpy(db_trayek[1].nama, "Kp. Rambutan - Pasteur");	
	strcpy(db_trayek[2].nama, "Kp. Melayu - Pasteur");	
	strcpy(db_trayek[3].nama, "Ps. Senen - Pasteur");	
	
	// inisialisasi jam berangkat trayek Lebak Bulus - Pasteur
	strcpy(db_trayek[0].jam_berangkat[0], "07.30");
	strcpy(db_trayek[0].jam_berangkat[1], "10.00");
	strcpy(db_trayek[0].jam_berangkat[2], "13.00");
	// inisialisasi jam tiba trayek Lebak Bulus - Pasteur
	strcpy(db_trayek[0].jam_tiba[0], "09.30");
	strcpy(db_trayek[0].jam_tiba[1], "12.00");
	strcpy(db_trayek[0].jam_tiba[2], "15.00");
	

	// inisialisasi jam berangkat trayek Kp. rambutan - Pasteur
	strcpy(db_trayek[1].jam_berangkat[0], "09.30");
	strcpy(db_trayek[1].jam_berangkat[1], "13.00");
	strcpy(db_trayek[1].jam_berangkat[2], "15.30");
	// inisialisasi jam tiba trayek Kp. rambutan - Pasteur
	strcpy(db_trayek[1].jam_tiba[0], "11.30");
	strcpy(db_trayek[1].jam_tiba[1], "15.00");
	strcpy(db_trayek[1].jam_tiba[2], "17.30");
	
	
	// inisialisasi jam berangkat trayek Kp. Melayu - Pasteur
	strcpy(db_trayek[2].jam_berangkat[0], "09.30");
	strcpy(db_trayek[2].jam_berangkat[1], "13.00");
	strcpy(db_trayek[2].jam_berangkat[2], "15.30"); 
	// inisialisasi jam tiba trayek Kp. Melayu - Pasteur
	strcpy(db_trayek[2].jam_tiba[0], "11.30");
	strcpy(db_trayek[2].jam_tiba[1], "15.00");
	strcpy(db_trayek[2].jam_tiba[2], "17.30");
	
	
	// inisialisasi jam berangkat trayek Ps.Senen - Pasteur
	strcpy(db_trayek[3].jam_berangkat[0], "07.30");
	strcpy(db_trayek[3].jam_berangkat[1], "13.00");
	strcpy(db_trayek[3].jam_berangkat[2], "19.30"); 
	// inisialisasi jam tiba trayek Ps.senen - Pasteur
	strcpy(db_trayek[3].jam_tiba[0], "09.30");
	strcpy(db_trayek[3].jam_tiba[1], "15.00");
	strcpy(db_trayek[3].jam_tiba[2], "21.00");
	
		
	// inisialisasi Harga trayek Lebak Bulus - Pasteur
	db_trayek[0].harga_ekonomi[0] = 120000;
	db_trayek[1].harga_bisnis[0] = 125000;
	db_trayek[1].harga_vip[0] = 150000;
	
	// inisialisasi Harga trayek Kp. Melayu - Pasteur
	db_trayek[2].harga_ekonomi[0] = 100000;
	db_trayek[2].harga_bisnis[0] = 125000;
	db_trayek[2].harga_vip[0] = 150000;

	// inisialisasi Harga standar trayek Ps.senen - Pasteur
	db_trayek[3].harga_ekonomi[0] = 120000;
	db_trayek[3].harga_bisnis[0] = 150000;
	db_trayek[3].harga_vip[0] = 200000;

	// inisialisasi Harga standar trayek Ps.senen - Pasteur
	db_trayek[3].harga_ekonomi[0] = 120000;
	db_trayek[3].harga_bisnis[0] = 150000;
	db_trayek[3].harga_vip[0] = 200000;

	// inisialisasi Harga malam trayek Ps.senen - Pasteur
	db_trayek[3].harga_ekonomi[1] = 150000;
	db_trayek[3].harga_bisnis[1] = 175000;
	db_trayek[3].harga_vip[1] = 225000;
}
void db_bus_init() {
	// inisialisasi trayek pada database bus
	db_bus[0].trayek = db_trayek[0];
	db_bus[1].trayek = db_trayek[1];
	db_bus[2].trayek = db_trayek[2];
	db_bus[3].trayek = db_trayek[3];	
}

// DEFINISI FUNGSI