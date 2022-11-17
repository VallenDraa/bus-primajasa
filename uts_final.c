/*
  Program ini berfungsi untuk melakukan pembelian tiket untuk bus primajasa
  
  CATATAN:
    - Jumlah kursi pada bus dirubah sedikit agar bisa mengikuti bentuk denah pada soal
*/ 


// DEKLARASI PUSTAKA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
// AKHIR DEKLARASI PUSTAKA

// DEKLARASI KONSTANTA
const int HARI_PADA_BULAN[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // berisi hari dalam bulan untuk validasi input tanggal
const int NILAI_KURSI_KOSONG = 9999;
const int JML_KURSI_EKONOMI = 61;
const int JML_KURSI_BISNIS = 53;
const int JML_KURSI_VIP = 40;
const int JML_TOTAL_BUS = 12;
// AKHIR DEKLARASI KONSTANTA

// DEKLARASI ENUM
typedef enum {
  ekonomi = 'e',
  bisnis = 'b',
  vip = 'v'
} Kelas_Bus;
// AKHIR DEKLARASI ENUM

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
	int no_bus;
	int no_kursi;
	Kelas_Bus kelas_tiket;
	char jam_berangkat[6];
	char jam_tiba[6];
	long harga;
} Tiket;

// Model Untuk Penumpang
typedef struct {
	char nik[11];
	char nama[120];
	char tgl_lahir[11];
	char tempat_lahir[120];
	char no_tel[11];
	char alamat[120];
	Tiket tiket_ekonomi[4]; 
	Tiket tiket_bisnis[4];
	Tiket tiket_vip[2];
  int total_qty_tiket; // total jumlah tiket yang dibeli
  long total_harga_tiket; // total harga semua tiket yang dibeli
} Penumpang;

// Model Untuk Bus
typedef struct {
	int idx_trayek; // berisi index untuk struct trayek
  int idx_jadwal; // berisi index jadwal untuk properti jam_berangkat dan jam_tiba struct trayek
	int kursi_ekonomi[61]; // kursi berisi index pada array penumpang
	int kursi_bisnis[53]; // kursi berisi index pada array penumpang
	int kursi_vip[40]; // kursi berisi index pada array penumpang
} Bus;

// Model untuk data penjualan
typedef struct {
  int qty_tiket_ekonomi_terjual; // total tiket ekonomi yang terjual
  int qty_tiket_bisnis_terjual; // total tiket bisnis yang terjual
  int qty_tiket_vip_terjual; // total tiket vip yang terjual
  int qty_tiket_all_terjual; // total semua tiket yang terjual
  long profit; // keuntungan penjualan tiket
} Penjualan;
// AKHIR DEKLARASI STRUCT

// DEKLARASI GLOBAL VARIABLE
Trayek db_trayek[4]; // database berisi data trayek
Bus db_bus[12]; // database berisi data bus
Penumpang db_penumpang[500]; // database berisi data penumpang 
Penjualan db_penjualan; // database berisi data penjualan tiket beserta profit 
int input_menu; // menampung input menu dari user
int idx_pembeli = 0; // untuk menghitung jumlah pembeli
int len_nama_terpanjang = 0; // untuk menampung panjang nama terpanjang penumpang
// AKHIR DEKLARASI GLOBAL VARIABLE

// DEKLARASI PROSEDUR VIEWS
// Deklarasi prosedur bertipe menu
void menu_router_utama();
void menu_router_db();
void menu_input_pemesanan();
void menu_db_pembeli();
void menu_db_riwayat_perjalanan();

// Deklarasi prosedur bertipe menu
void form_data_diri();
void form_qty_pembelian_tiket();
void form_data_tiket(Tiket *tiket, Kelas_Bus kelas_tiket);

// Deklarasi prosedur bertipe tabel
void tabel_kursi_ekonomi(int *arr_kursi);
void tabel_kursi_bisnis(int *arr_kursi);
void tabel_kursi_vip(int *arr_kursi);
void tabel_trayek(bool is_mode_bus);
void tabel_preview_pembeli();
void tabel_detail_pembeli(int idx_pembeli);
void tabel_data_penjualan();
// AKHIR DEKLARASI PROSEDUR VIEWS

// AKHIR DEKLARASI PROSEDUR UTILITY
// util_print_center digunakan untuk mencetak sebuah string pada posisi tengah pada panjang 'len'
void util_print_center(char *prefix, char *str, char *div, int len, char *suffix);
// util_print_repeat digunakan untuk mencetak sebuah string sebanyak 'len' kali
void util_print_repeat(char *prefix, char *str, int len, char *suffix);
// util_transisi_menu digunakan untuk mencetak sebuah string sebanyak 'len' kali
void util_transisi_menu(char *msg);
// AKHIR DEKLARASI PROSEDUR UTILITY

// DEKLARASI PROSEDUR DB
void db_trayek_init();
void db_bus_init();
// AKHIR DEKLARASI PROSEDUR DB

// DEKLARASI FUNGSI
bool util_is_date_valid(char *date);
// AKHIR DEKLARASI FUNGSI

// DEKLARASI ALGORITMA
int main() {
	// memanggil prosedur penginisialisasi database
	db_trayek_init();
	db_bus_init();

	// memanggil prosedur ini untuk memulai program
	menu_router_utama();
	
	// jika user keluar dari menu utama
	system("cls");
  util_print_repeat("\n+", "-", 100, "+\n");
  util_print_center("|", "Terima Kasih Telah Berkendara Dengan Bus Primajasa :)", " ", 100, "|\n");
  util_print_repeat("+", "-", 100, "+\n");
	return 0;
}

// DEFINISI PROSEDUR
void menu_router_utama() {
	while (true) {
		system("cls");
		util_print_center("\n+", "BUS PRIMAJASA", "-", 24, "+\n");
		printf("| 1. Beli Tiket Bus  	 |\n");	
		printf("| 2. Lihat Database 	 |\n");	
		printf("| 3. Keluar Dari Program |\n");	
		util_print_repeat("+", "-", 24, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", &input_menu);
		
		// router menu utama ketika user sudah menginput pilihan menu
		if (input_menu == 1) {
			menu_input_pemesanan();			
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

		util_print_center("\n+", "DATABASE PRIMAJASA", "-", 28, "+\n");
		printf("| 1. List Trayek             |\n");	
		printf("| 2. List Riwayat Perjalanan |\n");	
		printf("| 3. Data Pembeli            |\n");	
		printf("| 4. Data Penjualan          |\n");	
		printf("| 5. Kembali Ke Menu Utama   |\n");	
		util_print_repeat("+", "-", 28, "+\n");
		printf("Input: "); fflush(stdin); scanf("%i", &input_menu);

    system("cls");
		// router database ketika user sudah menginput pilihan menu
    if (input_menu == 1) {
			tabel_trayek(false);			
      util_transisi_menu("");
		} else if (input_menu == 2) {
			menu_db_riwayat_perjalanan();
		} else if (input_menu == 3) {
      menu_db_pembeli();
		} else if (input_menu == 4) {
			tabel_data_penjualan(); 
      util_transisi_menu("");
		} else if (input_menu == 5) {
			break;
		} 
	}
}
void menu_input_pemesanan() {
	form_data_diri();
	form_qty_pembelian_tiket();
	
  system("cls");
  idx_pembeli += 1;
	util_transisi_menu("1 data penumpang baru berhasil ditambahkan !\nKlik apa saja untuk kembali ke menu utama !");
}
void menu_db_pembeli() {
  while (true) {
    system("cls");
    // mencetak tabel preview penumpang
    tabel_preview_pembeli();

    // perintah untuk user
    if (idx_pembeli > 0) {
      printf("Input No. urut pada tabel untuk melihat detail pembeli!\n");	
    }
    printf("Input 0 untuk kembali Ke Menu Database !\n\n");	
    
    // meminta input dari user
    printf("Input: "); fflush(stdin); scanf("%i", &input_menu);

    // router menu database
    if (input_menu == 0) {
      break;
    } else {
      // validasi untuk melihat detail
      if (idx_pembeli > 0 && input_menu <= idx_pembeli) {
        system("cls");
        tabel_detail_pembeli(input_menu - 1);
        util_transisi_menu("Tekan apa saja untuk kembali ke database pembeli !");
      }
    }
  } 
}
void menu_db_riwayat_perjalanan() {
  char kelas; // untuk mengarahkan user ke denah kelas yang tepat
  int i;
  int banyak_kursi;
  bool is_semua_kosong;

  while (true) {
    system("cls");
    is_semua_kosong = true; // indikator semua kursi kosong, nilai bisa berubah pada router menu database

    // mencetak tabel data bus untuk mempermudah user dalam memilih data
    // terkait bus yand ingin dilihat
    tabel_trayek(true);
    
    // perintah untuk user
    printf("Input No Bus [1-12]\n");	
    printf("Input 0 untuk kembali Ke Menu Database !\n\n");	
    
    // meminta input dari user
    printf("Input: "); fflush(stdin); scanf("%i", &input_menu);

    // router menu database
    if (input_menu == 0) {
      break;
    } else {
      // validasi untuk melihat detail
      if (input_menu >= 1 && input_menu <= 12) {
        system("cls");
        
        // meminta input kelas bus dari user
        do {
          printf("Masukkan kelas pada bus [e/b/v]: ");
          fflush(stdin); scanf("%c", &kelas);
          kelas = tolower(kelas);
        } while (kelas != ekonomi && kelas != bisnis && kelas != vip);

        // pengecekan denah bangku yang perlu dicetak berdasarkan kelas bus  
        system("cls");
        if (kelas == ekonomi) {
          tabel_kursi_ekonomi(db_bus[input_menu - 1].kursi_ekonomi);
          banyak_kursi = JML_KURSI_EKONOMI;
        } else if (kelas == bisnis) {
          tabel_kursi_bisnis(db_bus[input_menu - 1].kursi_bisnis);
          banyak_kursi = JML_KURSI_BISNIS;
        } else { 
          tabel_kursi_vip(db_bus[input_menu - 1].kursi_vip); 
          banyak_kursi = JML_KURSI_VIP;
        }

        // header list nama penumpang
        util_print_center("", "List Nama Penumpang", " ", 80, "\n");
        util_print_repeat("", "-", 80, "\n");

        // isi list nama penumpang
        for (i = 0; i < banyak_kursi; i++) {
          // pada loop ini nikai variable 'is_semua_kosong' bisa berubah
          // ketika salah satu kursi bernilai tidak sama dengan NILAI_KURSI_KOSONG 

          if (kelas == ekonomi) {
            if (db_bus[input_menu - 1].kursi_ekonomi[i] == NILAI_KURSI_KOSONG){
              continue;
            } else {
              if (is_semua_kosong) { 
                is_semua_kosong = false;
              }

              // mencetak nama penumpang jika ada
              printf("Kursi %i: ", i);
              printf("%s\n", db_penumpang[db_bus[input_menu - 1].kursi_ekonomi[i]].nama);
            }
          } else if (kelas == bisnis) {
            if (db_bus[input_menu - 1].kursi_bisnis[i] == NILAI_KURSI_KOSONG){
              continue;
            } else {
              if (is_semua_kosong) { 
                is_semua_kosong = false;
              }

              // mencetak nama penumpang jika ada
              printf("Kursi %i: ", i);
              printf("%s\n", db_penumpang[db_bus[input_menu - 1].kursi_bisnis[i]].nama);
            }
          } else {
            if (db_bus[input_menu - 1].kursi_vip[i] == NILAI_KURSI_KOSONG){
              continue;
            } else {
              if (is_semua_kosong) { 
                is_semua_kosong = false;
              }

              // mencetak nama penumpang jika ada
              printf("Kursi %i: ", i);
              printf("%s\n", db_penumpang[db_bus[input_menu - 1].kursi_vip[i]].nama);
            }
          }
        }
        
        // mencetak isi tabel menyatakan bahwa semua kursi masih kosong
        if (is_semua_kosong) {
          util_print_center("", "Bus Masih Kosong", " ", 80, "\n");
        }

        // footer list nama penumpang
        util_print_repeat("", "-", 80, "\n");
      }

      util_transisi_menu("");
    }
  } 
}

void form_data_diri() {
	system("cls");
	util_print_center("\n", "Form Data Diri", " ", 50, "\n");
	util_print_repeat("", "-", 50, "\n");	
  
	do {
		printf("1. Masukkan NIK Anda [10 digit]: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].nik);
	} while (strlen(db_penumpang[idx_pembeli].nik) != 10);

	do {
		printf("2. Masukkan Nama Anda: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].nama);
	} while (strlen(db_penumpang[idx_pembeli].nama) == 0);
	
	do {
		printf("3. Masukkan Tempat Lahir Anda: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].tempat_lahir);
	} while (strlen(db_penumpang[idx_pembeli].tempat_lahir) == 0);
	
	do {
    printf("4. Masukkan Tanggal Lahir Anda [yyyy-mm-dd]: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].tgl_lahir);
	} while (strlen(db_penumpang[idx_pembeli].tgl_lahir) == 0 || !util_is_date_valid(db_penumpang[idx_pembeli].tgl_lahir));

	do {
		printf("5. Masukkan Alamat Anda: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].alamat);
	} while (strlen(db_penumpang[idx_pembeli].alamat) == 0);
	
	do {
		printf("6. Masukkan Nomor Telepon Anda [10 Digit]: ");
		fflush(stdin); scanf("%[^\n]s", db_penumpang[idx_pembeli].no_tel);
	} while (strlen(db_penumpang[idx_pembeli].no_tel) != 10);
}
void form_qty_pembelian_tiket() {
	int qty_tiket_ekonomi = 0;
	int qty_tiket_bisnis = 0;
	int qty_tiket_vip = 0;
  int total_input_tiket;
  int i;

  // meminta masukan qty tiket per kelas
  do {
    system("cls");

    util_print_center("\n", "Form Input Quantity Tiket", " ", 65, "\n");
    util_print_repeat("", "-", 65, "\n");	
    // meminta jumlah tiket ekonomi yang ingin dibeli
    do {
      printf("1. Berapa Jumlah Tiket Ekonomi Yang Ingin Dibeli [Min. 0 - Maks. 4]: ");
      fflush(stdin); scanf("%i", &qty_tiket_ekonomi);
    } while (qty_tiket_ekonomi > 4 || qty_tiket_ekonomi < 0);
    
    // meminta jumlah tiket bisnis yang ingin dibeli
    do {
      printf("2. Berapa Jumlah Tiket Bisnis Yang Ingin Dibeli [Min. 0 - Maks. 4]: ");
      fflush(stdin); scanf("%i", &qty_tiket_bisnis);
    } while (qty_tiket_bisnis > 4 || qty_tiket_bisnis < 0);
    
    // meminta jumlah tiket vip yang ingin dibeli
    do {
      printf("3. Berapa Jumlah Tiket VIP Yang Ingin Dibeli [Min. 0 - Maks. 2]: ");
      fflush(stdin); scanf("%i", &qty_tiket_vip);
    } while (qty_tiket_vip > 2 || qty_tiket_vip < 0);
  } while (qty_tiket_bisnis == 0 && qty_tiket_ekonomi == 0 && qty_tiket_vip == 0);

  // pengisian data tiket (loopnya akan jalan ketika qty > 0)
  for (i = 0; i < qty_tiket_ekonomi; i++) {
    system("cls");
    printf("Tiket Ekonomi %i / %i\n", i + 1, qty_tiket_ekonomi);
    util_print_repeat("", "-", 50, "\n");
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_ekonomi[i], ekonomi);
  }
  for (i = 0; i < qty_tiket_bisnis; i++) {
    system("cls");
    printf("Tiket Bisnis %i / %i\n", i + 1, qty_tiket_bisnis);
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_bisnis[i], bisnis);
  }
  for (i = 0; i < qty_tiket_vip; i++) {
    system("cls");
    printf("Tiket VIP %i / %i\n", i + 1, qty_tiket_vip);
    form_data_tiket(&db_penumpang[idx_pembeli].tiket_vip[i], vip);
  }

  // menghitung total tiket yang dibeli dan menambahkan data ke database pembelian
  total_input_tiket = qty_tiket_ekonomi + qty_tiket_bisnis + qty_tiket_vip;
  db_penumpang[idx_pembeli].total_qty_tiket = total_input_tiket;

  // menambah total penjualan tiket ke database penjualan
  db_penjualan.qty_tiket_ekonomi_terjual += qty_tiket_ekonomi;
  db_penjualan.qty_tiket_bisnis_terjual += qty_tiket_bisnis;
  db_penjualan.qty_tiket_vip_terjual += qty_tiket_vip;
  db_penjualan.qty_tiket_all_terjual += total_input_tiket;
}
void form_data_tiket(Tiket *tiket, Kelas_Bus kelas_tiket) {
  int temp_waktu_berangkat;
  char success_msg[120];
  long harga_tiket;

  // menampilkan tabel bus beserta rute, jadwal, dan harga
  tabel_trayek(true);
  // meminta input bus tujuan dari user
  while (true) {
    printf("\n1. Pilih Bus Tujuan [No. Urut Pada Tabel]: ");
    fflush(stdin); scanf("%i", &tiket->no_bus);

    if (tiket->no_bus >= 1 && tiket->no_bus <= 12) {
      // -1 untuk menyesuaikan input dengan index pada database
      tiket->no_bus = tiket->no_bus - 1;

      // mengcopy jam berangkat dan tiba ke tiket penumpang
      strcpy(tiket->jam_berangkat, *db_trayek[db_bus[tiket->no_bus].idx_trayek].jam_berangkat);      
      strcpy(tiket->jam_tiba, *db_trayek[db_bus[tiket->no_bus].idx_trayek].jam_tiba);      
      break;
    }  
  }
  
  // menampilkan denah kursi pada bus
  system("cls");
  if (kelas_tiket == ekonomi) {
    tabel_kursi_ekonomi(db_bus[tiket->no_bus].kursi_ekonomi);
  } else if (kelas_tiket == bisnis) {
    tabel_kursi_bisnis(db_bus[tiket->no_bus].kursi_bisnis);
  } else {
    tabel_kursi_vip(db_bus[tiket->no_bus].kursi_vip);
  }
  
  // meminta user untuk memilih kursi pada bus
  while (true) {
    printf("2. Pilih Kursi Pada Bus:");
    fflush(stdin); scanf("%i", &tiket->no_kursi);

    if (kelas_tiket == ekonomi) {
      if (db_bus[tiket->no_bus].kursi_ekonomi[tiket->no_kursi] == NILAI_KURSI_KOSONG) {
        db_bus[tiket->no_bus].kursi_ekonomi[tiket->no_kursi] = idx_pembeli;
        break;
      } 
    } else if (kelas_tiket == bisnis) {
      if (db_bus[tiket->no_bus].kursi_bisnis[tiket->no_kursi] == NILAI_KURSI_KOSONG) {
        db_bus[tiket->no_bus].kursi_bisnis[tiket->no_kursi] = idx_pembeli;
        break;
      } 
    } else {
      if (db_bus[tiket->no_bus].kursi_vip[tiket->no_kursi] == NILAI_KURSI_KOSONG) {
        db_bus[tiket->no_bus].kursi_vip[tiket->no_kursi] = idx_pembeli;
        break;
      } 
    }
  }

  // memasukkan nilai yang tidak perlu input dari user
  tiket->kelas_tiket = kelas_tiket;
  
  // menginput harga tiket ke tiket dan total pembelian
  if (kelas_tiket == ekonomi) {
    harga_tiket = db_trayek[db_bus[tiket->no_bus].idx_trayek].harga_ekonomi[0];
  } else if (kelas_tiket == bisnis) {
    harga_tiket = db_trayek[db_bus[tiket->no_bus].idx_trayek].harga_bisnis[0];
  } else {
    if (db_bus[tiket->no_bus].idx_jadwal == 2) {
      harga_tiket = db_trayek[db_bus[tiket->no_bus].idx_trayek].harga_vip[1];
    } else {
      harga_tiket = db_trayek[db_bus[tiket->no_bus].idx_trayek].harga_vip[0];
    }
  }
  
  // menginput total harga tiket kepada database penumpang
  tiket->harga = harga_tiket;
  db_penumpang[idx_pembeli].total_harga_tiket += harga_tiket;

  // menambahkan profit penjulan ke database penjualan
  db_penjualan.profit += harga_tiket;
}

void tabel_kursi_ekonomi(int *arr_kursi) {
  int i;
  int curr_horizontal_idx = 1;
  char buffer[3];
  int idx_spasi = 2; // index untuk mencetak " "
  int idx_endl = 5; // index untuk mencetak \n

  util_print_center("\n", "DENAH KURSI KELAS EKONOMI", " ", 30, "\n");
  util_print_repeat("", "-", 30, "\n");

  for (i = 0; i < JML_KURSI_EKONOMI; i++) {
    arr_kursi[i] == NILAI_KURSI_KOSONG
      ? printf("\033[0;32m") // agar hasil print warna hijau
      : printf("\033[0;31m"); // agar hasil print warna merah

    // mencetak angka
    sprintf(buffer, "%i", i);
    util_print_center("", buffer, " ", 3, "  ");

    if (curr_horizontal_idx == idx_spasi && i <= JML_KURSI_EKONOMI - 6) {
      util_print_repeat("", " ", 5, "");
    } else if (curr_horizontal_idx == idx_endl && i <= JML_KURSI_EKONOMI - 6) {
      printf("\n");
      curr_horizontal_idx = 0;
    }
    curr_horizontal_idx += 1;
  }
  printf("\033[0;37m"); // agar hasil print kembali putih
  util_print_repeat("\n", "-", 30, "\n");
  printf("MERAH = Sudah diisi\n");
  printf("HIJAU = Kosong\n");
  util_print_repeat("", "-", 30, "\n\n");
}
void tabel_kursi_bisnis(int *arr_kursi) {
  int i;
  int curr_horizontal_idx = 1;
  char buffer[3];
  int idx_spasi = 2; // index untuk mencetak " "
  int idx_endl = 4; // index untuk mencetak \n

  util_print_center("\n", "DENAH KURSI KELAS BISNIS", " ", 25, "\n");
  util_print_repeat("", "-", 25, "\n");

  for (i = 0; i < JML_KURSI_BISNIS; i++) {
    arr_kursi[i] == NILAI_KURSI_KOSONG
      ? printf("\033[0;32m") // agar hasil print warna hijau
      : printf("\033[0;31m"); // agar hasil print warna merah

    // mencetak angka
    sprintf(buffer, "%i", i);
    util_print_center("", buffer, " ", 3, "  ");

    if (curr_horizontal_idx == idx_spasi && i <= JML_KURSI_BISNIS - 5) {
      util_print_repeat("", " ", 5, "");
    } else if (curr_horizontal_idx == idx_endl && i <= JML_KURSI_BISNIS - 5) {
      printf("\n");
      curr_horizontal_idx = 0;
    }

    curr_horizontal_idx += 1;
  }
  
  printf("\033[0;37m"); // agar hasil print kembali putih
  util_print_repeat("\n", "-", 25, "\n");
  printf("MERAH = Sudah diisi\n");
  printf("HIJAU = Kosong\n");
  util_print_repeat("", "-", 25, "\n\n");
}
void tabel_kursi_vip(int *arr_kursi) {
  int i;
  int curr_horizontal_idx = 1;
  char buffer[3];
  int idx_spasi = 1; // index untuk mencetak " "
  int idx_endl = 3; // index untuk mencetak \n

  util_print_center("\n", "DENAH KURSI KELAS VIP", " ", 23, "\n");
  util_print_repeat("", "-", 23, "\n");

  for (i = 0; i < JML_KURSI_VIP; i++) {
    arr_kursi[i] == NILAI_KURSI_KOSONG
      ? printf("\033[0;32m") // agar hasil print warna hijau
      : printf("\033[0;31m"); // agar hasil print warna merah

    // mencetak angka
    sprintf(buffer, "%i", i);
    util_print_center("", buffer, " ", 3, "  ");

    if (curr_horizontal_idx == idx_spasi && i <= JML_KURSI_VIP - 5) {
      util_print_repeat("", " ", 5, "");
    } else if (curr_horizontal_idx == idx_endl && i <= JML_KURSI_VIP - 5) {
      printf("\n");
      curr_horizontal_idx = 0;
    }

    curr_horizontal_idx += 1;
  }
  
  printf("\033[0;37m"); // agar hasil print kembali putih
  util_print_repeat("\n", "-", 23, "\n");
  printf("MERAH = Sudah diisi\n");
  printf("HIJAU = Kosong\n");
  util_print_repeat("", "-", 23, "\n\n");
}
void tabel_trayek(bool is_mode_bus) {
  // untuk menampung nilai sementara konversi int ke string 
  char buffer_int_to_str[10];
  int i, j;
  int idx_harga;
  int idx_bus = 0;

  // cetak judul tabel  
  util_print_center("\n", is_mode_bus ? "DAFTAR BUS" : "LIST TRAYEK", " ",  107, "\n");

	// header table atas jadwal
  util_print_repeat("+", "-", 107, "+\n");
	util_print_center("|", is_mode_bus ? "Bus" : "No", " ", 5, "|");
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
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      idx_harga = i == 3 && j == 2 ? 1 : 0;

      // print no urut tabel
      if (!is_mode_bus) {
        if (j == floor(3/2)) {
          sprintf(buffer_int_to_str, "%i", i + 1);
          util_print_center("|", buffer_int_to_str, " ", 5, "|");
        } else {
          util_print_center("|", "", " ", 5, "|");
        }
      } else {
        sprintf(buffer_int_to_str, "%i", i + 1 + idx_bus);
        util_print_center("|", buffer_int_to_str, " ", 5, "|");
        idx_bus += 1;
      }


      // print nama trayek
      if (!is_mode_bus) {
        j == round(3/2)
          ? util_print_center("", db_trayek[i].nama, " ", 26, "|")
          : util_print_center("", "", " ", 26, "|");
      } else {
        util_print_center("", db_trayek[i].nama, " ", 26, "|");
      }


      // print waktu keberangkatan dan tiba
      util_print_center("", db_trayek[i].jam_berangkat[j], " ", 14, "|");      
      util_print_center("", db_trayek[i].jam_tiba[j], " ", 14, "|");      
      

      // print harga ekonomi
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[i].harga_ekonomi[idx_harga]);
      util_print_center("", buffer_int_to_str, " ", 14, "|"); 

      // print harga bisnis
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[i].harga_bisnis[idx_harga]);
      util_print_center("", buffer_int_to_str, " ", 14, "|"); 

      // print harga VIP
      sprintf(buffer_int_to_str, "Rp. %li", db_trayek[i].harga_vip[idx_harga]);
      util_print_center("", buffer_int_to_str, " ", 14, "|\n"); 
    }

    // footer table
    util_print_repeat("+", "-", 107, "+\n");
    idx_bus -= 1;
  }
}
void tabel_preview_pembeli() {
  int i, j;
  int lebar_awal_tabel = 5 + 20 + 14 + 20;
  int lebar_dinamis = lebar_awal_tabel + len_nama_terpanjang;
  char buffer_int_to_str[50]; 

  // title tabel
  util_print_center("\n", "DATA PEMBELI", " ", lebar_dinamis, "\n");

  // header table
  util_print_repeat("+", "-", lebar_dinamis, "+\n");
	util_print_center("|", "No", " ", 5, "|");
	util_print_center("", "Nama Penumpang", " ", 19 + len_nama_terpanjang, "|");
	util_print_center("", "Qty Tiket", " ", 13, "|");
	util_print_center("", "Harga Total", " ", 19, "|\n");
  util_print_repeat("+", "-", lebar_dinamis, "+\n");

  // daftar preview pembeli
  if (idx_pembeli > 0) {
    for (i = 0; i < idx_pembeli; i++) {
      // mencetak urutan database
      sprintf(buffer_int_to_str, "%i", i + 1);
      util_print_center("|", buffer_int_to_str, " ", 5, "|");
      
      // mencetak nama penumpang
      util_print_center("", db_penumpang[i].nama, " ", 19 + len_nama_terpanjang, "|");

      // mencetak total qty tiket
      sprintf(buffer_int_to_str, "%i", db_penumpang[i].total_qty_tiket);
      util_print_center("", buffer_int_to_str, " ", 13, "|");
      
      // mencetak total harga tiket keseluruhan
      sprintf(buffer_int_to_str, "Rp. %li", db_penumpang[i].total_harga_tiket);
      util_print_center("", buffer_int_to_str, " ", 19, "|\n");
      
    }
  } else {
    util_print_center("|", "Belum Ada Pembeli", " ", lebar_dinamis, "|\n");
  }


  // footer table
  util_print_repeat("+", "-", lebar_dinamis, "+\n");
}
void tabel_detail_pembeli(int idx_pembeli) {
  int i;
  Tiket tiket_temp;
  
  // header tabel
  util_print_center("\n", "DATA PEMBELI", " ", 80, "\n");
  util_print_repeat("", "-", 80, "\n");

  // isi tabel
  printf("Nama Penumpang  : %s\n", db_penumpang[idx_pembeli].nama);
  printf("NIK             : %s\n", db_penumpang[idx_pembeli].nik);
  printf("No. Telepon     : %s\n", db_penumpang[idx_pembeli].no_tel);
  printf("Alamat          : %s\n", db_penumpang[idx_pembeli].alamat);
  printf("TTL             : %s, %s\n", db_penumpang[idx_pembeli].tempat_lahir, db_penumpang[idx_pembeli].tgl_lahir);
  printf("Tiket Ekonomi   \n");
  for (i = 0; i < 4; i++)  {
    tiket_temp = db_penumpang[idx_pembeli].tiket_ekonomi[i];
    if (strcmp(tiket_temp.jam_berangkat, "") == 0) break;

    printf("  - %s / %s-%s / Rp.%li\n", db_trayek[db_bus[tiket_temp.no_bus].idx_trayek].nama, 
          tiket_temp.jam_berangkat, tiket_temp.jam_tiba, tiket_temp.harga);
  }
  printf("\n");
  printf("Tiket Bisnis    \n");
  for (i = 0; i < 4; i++) {
    tiket_temp = db_penumpang[idx_pembeli].tiket_bisnis[i];
    if (strcmp(tiket_temp.jam_berangkat, "") == 0) break;

    printf("  - %s / %s-%s / Rp.%li\n", db_trayek[db_bus[tiket_temp.no_bus].idx_trayek].nama, 
          tiket_temp.jam_berangkat, tiket_temp.jam_tiba, tiket_temp.harga);
  }
  printf("\n");
  printf("Tiket VIP       \n");
  for (i = 0; i < 4; i++) {
    tiket_temp = db_penumpang[idx_pembeli].tiket_vip[i];
    if (strcmp(tiket_temp.jam_berangkat, "") == 0) break;

    printf("  - %s / %s-%s / Rp.%li\n", db_trayek[db_bus[tiket_temp.no_bus].idx_trayek].nama, 
          tiket_temp.jam_berangkat, tiket_temp.jam_tiba, tiket_temp.harga);
  }

  // footer tabel
  util_print_repeat("", "-", 80, "\n");
}
void tabel_data_penjualan() {
  // header tabel
  util_print_center("\n", "DATA PENJUALAN", " ", 80, "\n");
  util_print_repeat("", "-", 80, "\n");

  // isi tabel 
  printf("Penjualan Tiket\n");
  printf("  - Ekonomi  : %i\n", db_penjualan.qty_tiket_ekonomi_terjual);
  printf("  - Bisnis   : %i\n", db_penjualan.qty_tiket_bisnis_terjual);
  printf("  - VIP      : %i\n", db_penjualan.qty_tiket_vip_terjual);
  printf("  - Total    : %i\n\n", db_penjualan.qty_tiket_all_terjual);

  printf("Total Profit  : Rp.%li\n", db_penjualan.profit);

  // footet tabel
  util_print_repeat("", "-", 80, "\n");
}

void util_print_center(char *prefix, char *str, char *div, int len, char *suffix) {
  int i;
  int margin = len - strlen(str);
  int margin_kiri = margin % 2 != 0 ? margin / 2 + 1 : margin / 2;
  int margin_kanan = margin / 2;

  // proses percetakan
	printf("%s", prefix); // mencetak karakter awalan
  for (i = 0; i < margin_kiri; i++) { // mencetak margin kiri
    printf("%s", div);
  }
  printf("%s", str); // mencetak string di posisi tengah
  for (i = 0; i < margin_kanan; i++) { // mencetak margin kanan
    printf("%s", div);
  }
	printf("%s", suffix); // mencetak karakter akhiran 
}
void util_print_repeat(char *prefix, char *str, int len, char *suffix) {
	int i;
  printf("%s", prefix); // mencetak string awalan
	
	// mencetak margin kiri
	for (i = 0; i < len; i++) {
    printf("%s", str);
  } 
	
	printf("%s", suffix); // mencetak string akhiran
}
void util_transisi_menu(char *msg) {
  strcmp(msg, "") == 0
    ? printf("\nKlik apa saja untuk kembali ke menu sebelumnya")
    : printf("\n%s", msg);
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
  int i, j;
  int idx_trayek_bus = 0;
  int idx_jadwal = 0;

	// inisialisasi trayek pada database bus
  for (i = 0; i < JML_TOTAL_BUS; i++) {
    // menyalin index trayek ke bus
    if (idx_trayek_bus == 3) {
      idx_trayek_bus = 0;
    } else {
      idx_trayek_bus += 1;
    }
    db_bus[i].idx_trayek = idx_trayek_bus;

    // menyalin index jadwal pada trayek ke bus
    if (idx_jadwal == 2) {
      idx_jadwal = 0;
    } else {
      idx_jadwal += 1;
    }
    db_bus[i].idx_jadwal = j;

    // memberi indikator kosong pada kursi penumpang untuk kelas ekonomi
    for (j = 0; j < JML_KURSI_EKONOMI; j++) {
      db_bus[i].kursi_ekonomi[j] = NILAI_KURSI_KOSONG;
    }
    
    // memberi indikator kosong pada kursi penumpang untuk kelas bisnis
    for (j = 0; j < JML_KURSI_BISNIS; j++) {
      db_bus[i].kursi_bisnis[j] = NILAI_KURSI_KOSONG;
    }
    
    // memberi indikator kosong pada kursi penumpang untuk kelas vip
    for (j = 0; j < JML_KURSI_VIP; j++) {
      db_bus[i].kursi_vip[j] = NILAI_KURSI_KOSONG;
    }
  }
}
// AKHIR DEFINISI PROSEDUR

// DEFINISI FUNGSI
bool util_is_date_valid(char *date) {
	bool is_valid = true;
  char date_str[11];
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
// AKHIR DEFINISI FUNGSI