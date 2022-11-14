// Program ini berfungsi untuk melakukan pembelian tiker untuk bus primajasa

// DEKLARASI STRUCT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// DEKLARASI ENUM
typedef enum {
  ekonomi = 'e',
  bisnis = 'b',
  vip = 'v'
} Kelas_Bus;

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
	Kelas_Bus kelas_tiket;
	char jam_berangkat[6];
	char jam_tiba[6];
	long harga;
} Tiket;

// Model Untuk Penumpang
typedef struct {
	char nik[10];
	char nama[120];
	char tgl_lahir[12];
	char tempat_lahir[120];
	char no_tel[10];
	char alamat[120];
	Tiket tiket_ekonomi[4]; 
	Tiket tiket_bisnis[4];
	Tiket tiket_vip[4];
} Penumpang;

// Model Untuk Bus
typedef struct {
	Trayek trayek;
	int kursi_ekonomi[60]; // kursi berisi index pada array penumpang
	int kursi_bisnis[50]; // kursi berisi index pada array penumpang
	int kursi_vip[35]; // kursi berisi index pada array penumpang
} Bus;


// DEKLARASI KONSTANTA
const int HARI_PADA_BULAN[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // berisi hari dalam bulan untuk validasi input tanggal

// DEKLARASI GLOBAL VARIABLE
Trayek db_trayek[4]; // database berisi data terkait trayek
Bus db_bus[4]; // database berisi data terkait bus (no urut bus akan sesuai dengan no trayek)
Penumpang db_penumpang[200]; // database berisi data terkait 
long long total_profit; // menampung data keuangan perusahaan
int input_menu; // menampung input menu dari user
int x, y, z; // variable untuk index pada for loop
int idx_pembeli = 0; // untuk menghitung jumlah pembeli


// DEKLARASI PROSEDUR VIEWS
// Deklarasi prosedur bertipe menu
void menu_router_utama();
void menu_router_db();
void menu_input_data_penumpang();
// Deklarasi prosedur bertipe menu
void form_data_diri();
void form_qty_pembelian_tiket();
void form_data_tiket(Tiket *tiket, Kelas_Bus kelas_tiket);
// Deklarasi prosedur bertipe tabel
// void tabel_kelas_tiket();
void tabel_kursi(int *arr_kursi, int qty_kursi);
void tabel_trayek();
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

// DEKLRASI FUNGSI
bool util_is_date_valid(char *date);

// DEKLARASI ALGORITMA
int main() {
	// memanggil prosedur penginisialisasi database
	db_trayek_init();
	db_bus_init();

	// memanggil prosedur ini untuk memulai program
	menu_router_utama();
	
	// jika user keluar dari menu utama
	system("cls");
	printf("Terima Kasih Telah Menggunakan Jasa Bus Primajasa !");
	return 0;
}

// DEFINISI PROSEDUR
void menu_router_utama() {
	while (true) {
		system("cls");
    tabel_kursi(db_bus[0].kursi_ekonomi, 60);
		util_print_center("+", "BUS PRIMAJASA", "-", 24, "+\n");
		printf("| 1. Beli Tiket Bus  	 |\n");	
		printf("| 2. Lihat Database 	 |\n");	
		printf("| 3. Keluar Dari Program |\n");	
		util_print_repeat("+", "-", 24, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", &input_menu);
		
		// percabangan router menu utama ketika user sudah menginput pilihan menu
		if (input_menu == 1) {
			menu_input_data_penumpang();			
		} else if (input_menu == 2) {
			menu_router_db();
		} else if (input_menu == 3) {
			break;	
		} 
	}
}
void menu_router_db() {
	while (true) {
		system("cls");

		util_print_center("+", "DATABASE PRIMAJASA", "-", 28, "+\n");
		printf("| 1. List Trayek             |\n");	
		printf("| 2. Data Pembeli            |\n");	
		printf("| 3. Data Pemesanan          |\n");	
		printf("| 4. List Riwayat Perjalanan |\n");	
		printf("| 5. Kembali Ke Menu Utama   |\n");	
		util_print_repeat("+", "-", 28, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", &input_menu);

    system("cls");
		// percabangan router database ketika user sudah menginput pilihan menu
    if (input_menu == 1) {
			tabel_trayek();			
      util_back_to_menu();
		} else if (input_menu == 2) {
      tabel_pembeli();
      util_back_to_menu();
		} else if (input_menu == 3) {
      tabel_pemesanan();
      util_back_to_menu();
		} else if (input_menu == 4) {
			tabel_riwayat_perjalanan();
      util_back_to_menu();
		} else if (input_menu == 5) {
			break;
		} 
	}
}
void menu_input_data_penumpang() {
	form_data_diri();
	form_qty_pembelian_tiket();
	
	util_back_to_menu();
}

void form_data_diri() {
	system("cls");
	util_print_center("\n", "Form Data Diri", " ", 50, "\n");
	util_print_repeat("", "-", 50, "\n");	
	
	do {
		printf("1. Masukkan NIK Anda [10 Digit]: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].nik);
	} while (strlen(db_penumpang[idx_pembeli].nik) != 10);
	
	do {
		printf("2. Masukkan Nama Anda: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].nama);
	} while (strlen(db_penumpang[idx_pembeli].nama) == 0);
	
	do {
		printf("3. Masukkan Tempat Lahir Anda: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].tempat_lahir);
	} while (strlen(db_penumpang[idx_pembeli].tempat_lahir) == 0);
	
	do {
		printf("4. Masukkan Tanggal Lahir Anda [yyyy-mm-dd]: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].tgl_lahir);
	} while (strlen(db_penumpang[idx_pembeli].tgl_lahir) == 0 || !util_is_date_valid(db_penumpang[idx_pembeli].tgl_lahir));

	do {
		printf("5. Masukkan Alamat Anda: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].alamat);
	} while (strlen(db_penumpang[idx_pembeli].alamat) == 0);
	
	do {
		printf("6. Masukkan Nomor Telepon Anda [10 Digit]: ");
		fflush(stdin); gets(db_penumpang[idx_pembeli].no_tel);
	} while (strlen(db_penumpang[idx_pembeli].no_tel) != 10);
}
void form_qty_pembelian_tiket() {
	int qty_tiket_ekonomi = 0;
	int qty_tiket_bisnis = 0;
	int qty_tiket_vip = 0;
  	
  system("cls");

  // meminta jumlah tiket ekonomi yang ingin dibeli
  do {
    printf("Masukkan Jumlah Tiket Ekonomi Yang Ingin Dibeli [Maks. 4]: ");
		fflush(stdin); scanf("%i", &qty_tiket_ekonomi);
  } while (qty_tiket_ekonomi > 4 || qty_tiket_ekonomi <= 0);
  
  // meminta jumlah tiket bisnis yang ingin dibeli
  do {
    printf("Masukkan Jumlah Tiket Bisnis Yang Ingin Dibeli [Maks. 4]: ");
		fflush(stdin); scanf("%i", &qty_tiket_bisnis);
  } while (qty_tiket_bisnis > 4 || qty_tiket_bisnis <= 0);
  
  // meminta jumlah tiket vip yang ingin dibeli
  do {
    printf("Masukkan Jumlah Tiket VIP Yang Ingin Dibeli [Maks. 2]: ");
		fflush(stdin); scanf("%i", &qty_tiket_vip);
  } while (qty_tiket_vip > 2 || qty_tiket_vip <= 0);

  // pengisian data tiket
  for (x = 0; x < qty_tiket_ekonomi; x++) {
    printf("Tiket Ekonomi %i / %i", x + 1, qty_tiket_ekonomi);
    util_print_repeat("", "-", 50, "\n");	
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_ekonomi[x], ekonomi);
  }

  // pengisian data tiket
  for (x = 0; x < qty_tiket_bisnis; x++) {
    printf("Tiket Bisnis %i / %i", x + 1, qty_tiket_bisnis);
    util_print_repeat("", "-", 50, "\n");	
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_bisnis[x], bisnis);
  }

  // pengisian data tiket
  for (x = 0; x < qty_tiket_vip; x++) {
    printf("Tiket VIP %i / %i", x + 1, qty_tiket_vip);
    util_print_repeat("", "-", 50, "\n");	
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_vip[x], vip);
  }

}
void form_data_tiket(Tiket *tiket, Kelas_Bus kelas_tiket) {
  int temp_waktu_berangkat;

  // meminta input dari user
  do {
    system("cls");
    tabel_trayek();
    printf("\n1. Masukkan Trayek [No. Urut Pada Tabel]: ");
    fflush(stdin); scanf("%i", &tiket->no_trayek);
  } while (tiket->no_trayek <= 0 || tiket->no_trayek > 4);
  
  while (true) {
    system("cls");
    tabel_jadwal(tiket->no_trayek - 1); // -1 untuk menyesuaikan input dengan index pada database
    printf("2. Pilih Waktu Berangkat [1-3]: ");
    fflush(stdin); scanf("%i", &temp_waktu_berangkat);

    // mengecek nilai thruthy
    if (temp_waktu_berangkat >= 1 && temp_waktu_berangkat <= 3){
      strcpy(tiket->jam_berangkat, db_trayek[tiket->no_trayek - 1].jam_berangkat);      
      strcpy(tiket->jam_tiba, db_trayek[tiket->no_trayek - 1].jam_tiba);      
      break;
    }
  }
  
  do {
    if (kelas_tiket == ekonomi) {

    } else if (kelas_tiket == bisnis) {

    } else {

    }

    printf("3. Pilih Kursi Pada Bus !\n");
    printf("Jika berwarna HIJAU berarti Kursi Kosong dan Jika MERAH maka kursi sudah diisi");

    fflush(stdin); scanf("%i", &tiket->no_kursi);
  } while (tiket->no_trayek <= 0 || tiket->no_trayek > 4);


  // memasukkan nilai yang tidak perlu input dari user
  tiket->kelas_tiket = kelas_tiket;

}

void tabel_kursi(int *arr_kursi, int qty_kursi) {
  for (x = 0; x < qty_kursi; x++) {
    if (arr_kursi[x] != NULL) {
      printf("\033[0;31m"); // agar hasil print warna merah
      printf("%i ", x); // agar hasil print warna merah
    } else {
      printf("\033[0;32m"); // agar hasil print warna hijau
      printf("%i ", x); // agar hasil print warna merah
    }
  }
  
  printf("\033[0;37m"); // agar hasil print kembali putih
}
void tabel_trayek() {
  // untuk menampung nilai sementara konversi int ke string 
  char buffer_int_to_str[10]; 

  // cetak judul tabel  
  util_print_center("", "LIST TRAYEK", " ",  107, "\n");

	// header table atas jadwal
  util_print_repeat("+", "-", 107, "+\n");
	util_print_center("|", "No", " ", 5, "|");
	util_print_center("", "Trayek", " ", 26, "|");
	util_print_center("", "Waktu", " ", 29, "|");
	util_print_center("", "Harga Tiket Bus", " ", 44, "|\n");

	// header table bawah jadwal
	util_print_center("|", "", " ", 5, "|");
	util_print_repeat("", " ", 26, "|");
	util_print_center("", "Berangkat", " ", 14, "|");
	util_print_center("", "Kedatangan", " ", 14, "|");
	util_print_center("", "Ekonomi", " ", 14, "|");
	util_print_center("", "Bisnis", " ", 14, "|");
	util_print_center("", "VIP", " ", 14, "|\n");
  util_print_repeat("+", "-", 107, "+\n");

  // mencetak isi table
  for (x = 0; x < 4; x++) {
    for (y = 0; y < 3; y++) {
      // print no urut tabel
      if (y == floor(3/2)) {
        sprintf(buffer_int_to_str, "%i", x + 1);
        util_print_center("|", buffer_int_to_str, " ", 5, "|");
        strcpy(buffer_int_to_str, "");
      } else {
        util_print_center("|", "", " ", 5, "|");
      }


      // print nama trayek
      y == round(3/2) 
        ? util_print_center("", db_trayek[x].nama, " ", 26, "|")
        : util_print_center("", "", " ", 26, "|");


      // print waktu keberangkatan dan tiba
      util_print_center("", db_trayek[x].jam_berangkat[y], " ", 14, "|");      
      util_print_center("", db_trayek[x].jam_tiba[y], " ", 14, "|");      
      

      // print harga ekonomi
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[x].harga_ekonomi[x == 3 && y == 2 ? 1 : 0]);
      util_print_center("", buffer_int_to_str, " ", 14, "|"); 
      strcpy(buffer_int_to_str, "");
      // print harga bisnis
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[x].harga_bisnis[x == 3 && y == 2 ? 1 : 0]);
      util_print_center("", buffer_int_to_str, " ", 14, "|"); 
      strcpy(buffer_int_to_str, "");
      // print harga VIP
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[x].harga_vip[x == 3 && y == 2 ? 1 : 0]);
      util_print_center("", buffer_int_to_str, " ", 14, "|\n"); 
      strcpy(buffer_int_to_str, "");
    }

    // footer table
    util_print_repeat("+", "-", 107, "+\n");
  }
}
void tabel_jadwal(int idx_trayek) {
  // untuk menampung nilai sementara konversi int ke string 
  char buffer_int_to_str[50]; 

  // cetak judul tabel
  sprintf(buffer_int_to_str, "JADWAL %s", db_trayek[idx_trayek].nama);
  util_print_center("", buffer_int_to_str, " ", 50, "\n");
  strcpy(buffer_int_to_str, "");  

	// header table bagian atas jadwal
  util_print_repeat("+", "-", 50, "+\n");
	util_print_center("|", "No", " ", 5, "|");
	util_print_center("", "Waktu", " ", 44, "|\n");

	// header table bagian bawah jadwal
  util_print_center("|", "", " ", 5, "|");
	util_print_center("", "Berangkat", " ", 22, "|");
	util_print_center("", "Kedatangan", " ", 21, "|\n");
  util_print_repeat("+", "-", 50, "+\n");


  // mencetak isi table
  for (x = 0; x < 3; x++) {
    // pritn no urut jadwal pada tabel
    sprintf(buffer_int_to_str, "%i", x + 1);
    util_print_center("|", buffer_int_to_str, " ", 5, "|");
    strcpy(buffer_int_to_str, "");

    // print waktu keberangkatan dan tiba
    util_print_center("", db_trayek[idx_trayek].jam_berangkat[y], " ", 22, "|");      
    util_print_center("", db_trayek[idx_trayek].jam_tiba[y], " ", 21, "|\n");      
  }
  // footer table
  util_print_repeat("+", "-", 50, "+\n");
}
void tabel_pembeli() {
	printf("hello pembeli");
}
void tabel_pemesanan() {
	printf("hello pemesanan");
}
void tabel_riwayat_perjalanan() {
	printf("hello riwayat perjalanan");
}

void util_print_center(char *prefix, char *str, char *div, int len, char *suffix) {
  int margin = len - strlen(str);
  int margin_kiri = margin % 2 != 0 ? margin / 2 + 1 : margin / 2;
  int margin_kanan = margin / 2;

  // proses percetakan
	printf("%s", prefix); // mencetak karakter awalan
  for (z = 0; z < margin_kiri; z++) { // mencetak margin kiri
    printf("%s", div);
  }
  printf("%s", str); // mencetak string di posisi tengah
  for (z = 0; z < margin_kanan; z++) { // mencetak margin kanan
    printf("%s", div);
  }
	printf("%s", suffix); // mencetak karakter akhiran 
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
	db_trayek[0].harga_bisnis[0] = 150000;
	db_trayek[0].harga_vip[0] = 200000;
	
	// inisialisasi Harga trayek Kp. Rambutan - Pasteur
	db_trayek[1].harga_ekonomi[0] = 100000;
	db_trayek[1].harga_bisnis[0] = 125000;
	db_trayek[1].harga_vip[0] = 150000;

	// inisialisasi Harga standar trayek Kp. Melayu - Pasteur
	db_trayek[2].harga_ekonomi[0] = 100000;
	db_trayek[2].harga_bisnis[0] = 125000;
	db_trayek[2].harga_vip[0] = 150000;

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
bool util_is_date_valid(char *date) {
	bool is_valid = true;
  char date_str[9];
  strcpy(date_str, date);


  // jika panjang string tidak 10 maka tidak valid 
  if (strlen(date_str) != 10) return !is_valid;

	int tahun = atoi(strtok(date_str, "-"));
	int bulan = atoi(strtok(NULL, "-"));
	int hari = atoi(strtok(NULL, "-"));

	// Validasi Tahun
	if (!tahun) return !is_valid;
	
	// validasi Bulan
	if (bulan <= 0 || bulan > 12) return !is_valid;
	
	// Validasi Hari
	if (hari <= 0 || hari > HARI_PADA_BULAN[bulan - 1]) return !is_valid;
	 
	// Validasi hari pada tahun kabisat
	if (tahun % 4 == 0 && HARI_PADA_BULAN[bulan - 1] && hari > 29) return !is_valid;
	
	//	Jika tanggal berhasil melewati validasi
	return is_valid;
}