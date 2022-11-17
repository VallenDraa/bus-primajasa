// PROGRAM Tiket Bus Primajasa

// {Program ini digunakan untuk memesan tiket bus primajasa}

// DEKLARASI Variabel
// DEKLARASI Pustaka
int menu;
int menu1;
int menu2;

int jmlhpenumpang;
// DEKLARASI Variabel
int tujuan;
int menu;
int pilihwaktu;
int menu1;
// DEKLARASI Struct
int menu2;
struct data {
  int jmlhpenumpang;
  // Data Pribadi
  int tujuan;
  char nik[10];
  int pilihwaktu;
  char nama[20];
  // DEKLARASI Struct
  char tempat_lahir[20];
    char tgl_lahir[10];
    // Data Pribadi
    char alamat[20];
    char nik[10];
    char no_telp[15];
    char nama[20];
    // data Pembelian tiket bus
    char tempat_lahir[20];
    char trayek[20];
    char tgl_lahir[10];
    char jam_brngkt_dan_plng[20];
    char alamat[20];
    int kelas, harga, no_kursi;
    char no_telp[15];
}penumpang[200];
  // data Pembelian tiket bus

char trayek[20];
// DEKLARASI Procedure dan Fungsi
char jam_brngkt_dan_plng[20];
void tabel();  // Procedur menampilkan tabel
int kelas, harga, no_kursi;
void inputdata(); // procdeure input data penumpang
void menua(int nomor);

void keberangkatan1();
// DEKLARASI Procedure dan Fungsi
void trayek_bus();
void tabel();  // Procedur menampilkan tabel

void inputdata(); // procdeure input data penumpang
// ALGORITMA
void menua(int nomor);

void keberangkatan1();
// main utama
void trayek_bus();
int main() {

  int awal;
  // ALGORITMA


  do {
    // main utama
    system("cls");
    int main() {
      printf("*~~~~~~~~*\n");
      int awal;
      printf("|SELAMAT DATANG di APLIKASI BUS PRIMAJASA|\n");

      printf("*~~~~~~~~*\n");
      do {

        system("cls");
        menua(1);
        printf("*~~~~~~~~*\n");
        switch (menu1) {
          printf("|SELAMAT DATANG di APLIKASI BUS PRIMAJASA|\n");
        case 1: {
          printf("*~~~~~~~~*\n");
          inputdata();

          break;
          menua(1);
        }
              switch (menu1) {
              case 2: {
              case 1: {

                inputdata();
                break;
                break;
              }
              }
              case 3: {
              case 2: {
                printf("Terimaksih sudah menggunakan jasa kami ^^");

                return 0;
                break;
                break;
              }
              }
              case 3: {

                printf("Terimaksih sudah menggunakan jasa kami ^^");
              }
                    return 0;
                    awal = 1;
                    break;

              }
        }while (awal == 1);

      }
    }
    // Akhiran main program
    awal = 1;


    // program input data
  } while (awal == 1);
  void inputdata() {
  }
  printf("Masukan Data Pembeli \n \n");
  // Akhiran main program
  // Input NIK

  do {
    // program input data
    printf("Masukan NIK (10 digit) : ");
    void inputdata() {
      fflush(stdin);
      printf("Masukan Data Pembeli \n \n");
      scanf("%s", &penumpang[jmlhpenumpang].nik);
      // Input NIK
    }while (!(strlen(penumpang[jmlhpenumpang].nik) == 10));
    do {
      // Input Nama 
      printf("Masukan NIK (10 digit) : ");
      do {
        fflush(stdin);
        printf("Masukan Nama : ");
        scanf("%s", &penumpang[jmlhpenumpang].nik);
        fflush(stdin);
      } while (!(strlen(penumpang[jmlhpenumpang].nik) == 10));
      scanf("%s", &penumpang[jmlhpenumpang].nama);
      // Input Nama 
    } while (strcmp(penumpang[jmlhpenumpang].nama, "") == 0);
    do {
      // Input tempat lahir
      printf("Masukan Nama : ");
      do {
        fflush(stdin);
        printf("Tempat lahir : ");
        scanf("%s", &penumpang[jmlhpenumpang].nama);
        fflush(stdin);
      } while (strcmp(penumpang[jmlhpenumpang].nama, "") == 0);
      scanf("%s", &penumpang[jmlhpenumpang].tempat_lahir);
      // Input tempat lahir
    } while (strcmp(penumpang[jmlhpenumpang].tempat_lahir, "") == 0);
    do {
      // Input tanggal lahir
      printf("Tempat lahir : ");
      do {
        fflush(stdin);
        printf("Tanggal Lahir (dd/mm/yyyy) : ");
        scanf("%s", &penumpang[jmlhpenumpang].tempat_lahir);
        fflush(stdin);
      } while (strcmp(penumpang[jmlhpenumpang].tempat_lahir, "") == 0);
      scanf("%s", &penumpang[jmlhpenumpang].tgl_lahir);
      // Input tanggal lahir
    } while (!(strlen(penumpang[jmlhpenumpang].tgl_lahir) == 10));
    do {
      // Input alamat
      printf("Tanggal Lahir (dd/mm/yyyy) : ");
      do {
        fflush(stdin);
        printf("Alamat : ");
        scanf("%s", &penumpang[jmlhpenumpang].tgl_lahir);
        fflush(stdin);
      } while (!(strlen(penumpang[jmlhpenumpang].tgl_lahir) == 10));
      scanf("%s", &penumpang[jmlhpenumpang].alamat);
      // Input alamat
    } while (strcmp(penumpang[jmlhpenumpang].alamat, "") == 0);
    do {
      // Input nomor Telepon
      printf("Alamat : ");
      do {
        fflush(stdin);
        printf("Nomor telepn (12 digit) : ");
        scanf("%s", &penumpang[jmlhpenumpang].alamat);
        fflush(stdin);
      } while (strcmp(penumpang[jmlhpenumpang].alamat, "") == 0);
      scanf("%s", &penumpang[jmlhpenumpang].tgl_lahir);
      // Input nomor Telepon
    } while (!(strlen(penumpang[jmlhpenumpang].tgl_lahir) == 12));
    do {

      printf("Nomor telepn (12 digit) : ");
      system("cls");
      fflush(stdin);
      tabel();
      scanf("%s", &penumpang[jmlhpenumpang].tgl_lahir);
      // pilihan trayek bus
    } while (!(strlen(penumpang[jmlhpenumpang].tgl_lahir) == 12));
    trayek_bus();


    system("cls");

    tabel();
  }
  // pilihan trayek bus

  trayek_bus();
  void menua(int nomor) {

    switch (nomor) {

    case 1: {
    }
          // menu pada layar utama

          printf("*~~~~~~~~*\n");
          void menua(int nomor) {
            printf("| MENU                                   |\n");
            switch (nomor) {
              printf("*~~~~~~~~*\n");
            case 1: {
              printf("| 1. | Pesan Tiket                       |\n");
              // menu pada layar utama
              printf("| 2. | Informasi Bus                     |\n");
              printf("*~~~~~~~~*\n");
              printf("| 3. | Keluar                            |\n");
              printf("| MENU                                   |\n");
              printf("*~~~~~~~~*\n");
              printf("*~~~~~~~~*\n");
              do {
                printf("| 1. | Pesan Tiket                       |\n");
                printf("Masukan Nomor Menu (1/2/3) : ");
                printf("| 2. | Informasi Bus                     |\n");
                fflush(stdin);
                printf("| 3. | Keluar                            |\n");
                scanf("%d", &menu1);
                printf("*~~~~~~~~*\n");

                do {
                } while ((menu1 > 3) || (menu1 < 1));
                printf("Masukan Nomor Menu (1/2/3) : ");
                break;
                fflush(stdin);
              }
              scanf("%d", &menu1);
            case 2: {

              // menu pada data laporan
            }while ((menu1 > 3) || (menu1 < 1));
            printf("+----+----------------------+\n");
            break;
            printf("| No |         Menu         |\n");
            }
                  printf("+----+----------------------+\n");
            case 2: {
              printf("| 1. | Home / Kembali       |\n");
              // menu pada data laporan
              printf("| 2. | Identitas Pembeli    |\n");
              printf("+----+----------------------+\n");
              printf("| 3. | Trayek BUS           |\n");
              printf("| No |         Menu         |\n");
              printf("+----+------------------+---+\n");
              printf("+----+----------------------+\n");
              do {
                printf("| 1. | Home / Kembali       |\n");
                printf("Masukan Nomor Menu (1/2) : ");
                printf("| 2. | Identitas Pembeli    |\n");
                fflush(stdin);
                printf("| 3. | Trayek BUS           |\n");
                scanf("%d", &menu2);
                printf("+----+------------------+---+\n");
              } while ((menu2 > 3) || (menu2 < 1));
              do {
                break;
                printf("Masukan Nomor Menu (1/2) : ");
              }
              fflush(stdin);
            }
                  scanf("%d", &menu2);
            }
          }while ((menu2 > 3) || (menu2 < 1));

          break;
          // Tampilan tabel
    }
    void tabel() {
    }
    printf("*~~~~~~~~~~~~~~~~~~~~~*\n");
  }
  printf("| No | Trayek                |            Waktu            |        Harga Kelas Bus           |\n");

  printf("*~~|~~~~~|~~~~~~~|~~~~~~~~|\n");
  // Tampilan tabel
  printf("|    |                       |  Berangakat  |  Kedatangan  |  Ekonomi  |  Bisnis  |    VIP    |\n");
  void tabel() {
    printf("|    |                       |    07:30     |   09:30      |  120.000  |  150.000 |  200.000  |\n");
    printf("*~~~~~~~~~~~~~~~~~~~~~*\n");
    printf("|  1 | Lebak Bulus - Pasteur |    10:00     |   12:00      |  120.000  |  150.000 |  200.000  |\n");
    printf("| No | Trayek                |            Waktu            |        Harga Kelas Bus           |\n");
    printf("|    |                       |    13:00     |   15:00      |  120.000  |  150.000 |  200.000  |\n");
    printf("*~~|~~~~~|~~~~~~~|~~~~~~~~|\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
    printf("|    |                       |  Berangakat  |  Kedatangan  |  Ekonomi  |  Bisnis  |    VIP    |\n");
    printf("|    |                       |    09:30     |   11:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    07:30     |   09:30      |  120.000  |  150.000 |  200.000  |\n");
    printf("|  2 | Kp Rambutan - Pasteur |    13:00     |   15:00      |  100.000  |  125.000 |  150.000  |\n");
    printf("|  1 | Lebak Bulus - Pasteur |    10:00     |   12:00      |  120.000  |  150.000 |  200.000  |\n");
    printf("|    |                       |    15:30     |   17:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    13:00     |   15:00      |  120.000  |  150.000 |  200.000  |\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
    printf("|    |                       |    09:30     |   11:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    09:30     |   11:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|  3 | Kp Melayu - Pasteur   |    13:00     |   15:00      |  100.000  |  125.000 |  150.000  |\n");
    printf("|  2 | Kp Rambutan - Pasteur |    13:00     |   15:00      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    15:30     |   17:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    15:30     |   17:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
    printf("|    |                       |    07:30     |   09:30      |  120.000  |  150.000 |  200.000  |\n");
    printf("|    |                       |    09:30     |   11:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("|  4 | Ps senen - Pasteur    |    13:00     |   15:00      |  120.000  |  150.000 |  200.000  |\n");
    printf("|  3 | Kp Melayu - Pasteur   |    13:00     |   15:00      |  100.000  |  125.000 |  150.000  |\n");
    printf("|    |                       |    19:00     |   21:00      |  150.000  |  175.000 |  225.000  |\n");
    printf("|    |                       |    15:30     |   17:30      |  100.000  |  125.000 |  150.000  |\n");
    printf("*~~~~~~~~~~~~~~~~~~~~~*\n");
    printf("|~~|~~~~~|~~~~|~~|~~~|~~|~~~~~|\n");
  }
  printf("|    |                       |    07:30     |   09:30      |  120.000  |  150.000 |  200.000  |\n");
  printf("|  4 | Ps senen - Pasteur    |    13:00     |   15:00      |  120.000  |  150.000 |  200.000  |\n");
  void trayek_bus(int tujuan) {
    printf("|    |                       |    19:00     |   21:00      |  150.000  |  175.000 |  225.000  |\n");

    printf("*~~~~~~~~~~~~~~~~~~~~~*\n");
    do {
    }
    printf("Pilih Trayek BUS (1,2,3,4) : ");

    scanf("%i", &tujuan);
    void trayek_bus(int tujuan) {
    } while ((tujuan > 5) || (tujuan < 0));


    do {
      switch (tujuan) {
        printf("Pilih Trayek BUS (1,2,3,4) : ");
      case 1: {
        scanf("%i", &tujuan);
        printf("\n \n ");
      } while ((tujuan > 5) || (tujuan < 0));
      strcpy(penumpang[jmlhpenumpang].trayek, "Lebak bulus - Pasteur");

      printf(" dengan Kota Tujuan : %s\n\n", penumpang[jmlhpenumpang].trayek);
      switch (tujuan) {
        keberangkatan1();
      case 1: {

        printf("\n \n ");
        break;
        strcpy(penumpang[jmlhpenumpang].trayek, "Lebak bulus - Pasteur");
      }
            printf(" dengan Kota Tujuan : %s\n\n", penumpang[jmlhpenumpang].trayek);
      }
      keberangkatan1();
      }


      break;
      void keberangkatan1() {
      }
      do {
      }
      printf("Pilih waktu keberangkatan (1,2,3) : ");
    }
    scanf("%i", &pilihwaktu);

    switch (pilihwaktu) {
      void keberangkatan1() {
    case 1: {
      do {
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 07:30 - 09:30");
        printf("Pilih waktu keberangkatan (1,2,3) : ");
        break;
        scanf("%i", &pilihwaktu);
      }
      switch (pilihwaktu) {
      case 2: {
      case 1: {
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 10:00 - 12:00");
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 07:30 - 09:30");
        break;
        break;
      }
      }
      case 3: {
      case 2: {
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 10:00 - 12:00");
        break;
        break;
      }
      }
      }
    case 3: {
    } while ((pilihwaktu > 4) || (pilihwaktu < 0));
    strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
    }
          break;

      }
      void keberangkatan2() {
      }
      int pilihwaktu2;
    } while ((pilihwaktu > 4) || (pilihwaktu < 0));
    do {
    }
    printf("Pilih waktu keberangkatan (1,2,3) : ");

    scanf("%i", &pilihwaktu2);
    void keberangkatan2() {

      int pilihwaktu2;
      switch (pilihwaktu2) {
        do {
      case 1: {
        printf("Pilih waktu keberangkatan (1,2,3) : ");
        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 09:30 - 11:30");
        scanf("%i", &pilihwaktu2);
        break;

      }
            switch (pilihwaktu2) {
            case 2: {
            case 1: {
              strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
              strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 09:30 - 11:30");
              break;
              break;
            }
            }
            case 3: {
            case 2: {
              strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 15:30 - 17:30");
              strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
              break;
              break;
            }
            }
            }
      case 3: {
      } while ((pilihwaktu2 > 4) || (pilihwaktu2 < 0));
      strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 15:30 - 17:30");
        }
        break;
        void keberangkatan3() {
        }
        int pilihwaktu3;
      }
      do {
      } while ((pilihwaktu2 > 4) || (pilihwaktu2 < 0));
      printf("Pilih waktu keberangkatan (1,2,3) : ");
    }
    scanf("%i", &pilihwaktu3);
    void keberangkatan3() {
      switch (pilihwaktu3) {
        int pilihwaktu3;
      case 1: {
        do {
          strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 07:30 - 09:30");
          printf("Pilih waktu keberangkatan (1,2,3) : ");
          break;
          scanf("%i", &pilihwaktu3);
        }
        switch (pilihwaktu3) {
        case 2: {
        case 1: {
          strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
          strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 07:30 - 09:30");
          break;
          break;
        }
        }
        case 3: {
        case 2: {
          strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 19:00 - 21:00");
          strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 13:00 - 15:00");
          break;
          break;
        }
        }
        }
      case 3: {

        strcpy(penumpang[jmlhpenumpang].jam_brngkt_dan_plng, "Waktu Perjalanan : 19:00 - 21:00");
      }while ((pilihwaktu3 > 4) || (pilihwaktu3 < 0));
      break;
      }
      }

    }



  }while ((pilihwaktu3 > 4) || (pilihwaktu3 < 0));

}


