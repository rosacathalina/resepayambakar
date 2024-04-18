#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 5 // Maksimum item yang diizinkan
#define MAX_LEN 50  // Maksimum panjang string

void clearScreen() {
    // Cross-platform clear screen
	// Membersihkan layar lintas platform
    #ifdef _WIN32
    system("cls"); // Membersihkan layar pada Windows
    #else
    system("clear"); // Membersihkan layar pada sistem operasi lain
    #endif
}

struct Barang {
    char no[3];	// Nomor identifikasi barang
    char nama[20];	// Nama barang
    int harga;	// Harga barang
};

struct Pembelian {
    char no[3]; // Nomor identifikasi barang yang dibeli
    int jumlah;	// Jumlah barang yang dibeli
};

void intToString(int value, char* result) {
    sprintf(result, "%d", value); // Mengkonversi integer ke string
}

void tampilkanMenu(struct Barang items[], int maxItems) {
    clearScreen();
    printf("Selamat datang di Toko SKENSA\n");
    printf("Silahkan pilih barang yang Anda inginkan:\n");
    printf("-----------------------------------------\n");
    printf("| No | Barang          | Harga          |\n");
    printf("-----------------------------------------\n");
    int i;
    for (i = 0; i < maxItems; ++i) {
        printf("| %-2s | %-15s | Rp.%-10d |\n", items[i].no, items[i].nama, items[i].harga);
    }
    printf("-----------------------------------------\n");
    printf("\n");
    printf("11. Input Barang\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar\n");
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Inputkan pilihan yang anda inginkan: ");
}

// Fungsi untuk menukar dua elemen Pembelian
void swap(struct Pembelian *a, struct Pembelian *b) {
    struct Pembelian temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi untuk melakukan bubble sort
void bubbleSort(struct Pembelian arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++) {     //Loop ini mengontrol jumlah iterasi yang diperlukan untuk mengurutkan seluruh array
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++) { //Loop ini melakukan pemeriksaan dan penukaran elemen jika diperlukan.
            if (arr[j].jumlah < arr[j+1].jumlah) { //memeriksa elemen dan memastikan urutan yang benar (dari yang terbesar ke yang terkecil).
                swap(&arr[j], &arr[j+1]); //memastikan elemen yang lebih besar bergerak ke posisi yang benar dalam proses pengurutan.
            }
        }
    }
}

int main() {
    time_t y = time(0); //tipe data yang digunakan untuk menyimpan informasi waktu
    char tgl[30];
    strncpy(tgl, ctime(&y), 29);
    tgl[29] = '\0';

    struct Barang items[MAX_ITEMS] = {
        {"1", "Buku Tulis", 5000},
        {"2", "Pensil", 2000},
        {"3", "Penghapus", 1000},
        {"4", "Penggaris", 1000},
        {"5", "Bujur Sangkar", 500}
    };

    int pilihan;
    struct Pembelian keranjang[MAX_ITEMS];
    int jumlahItemDiKeranjang = 0;
    int totalHarga = 0, totalDiskon = 0, totalBayar = 0; //variabel-variabel ini digunakan untuk melacak total harga, total diskon, dan total yang harus dibayar oleh pengguna.
    int uangBayar, kembalian;
    time_t now = time(0);
    char strukId[MAX_LEN];
    intToString((int)now, strukId);
    
    char noBarang[3];
    int jumlah;
    char tambahLagi;

    while (1) {
        clearScreen();
        // Menampilkan Menu
        tampilkanMenu(items, MAX_ITEMS);
        scanf("%d", &pilihan);
        fflush(stdin); // Membersihkan buffer input


        switch (pilihan) {
            case 11:
                
			    do {
			        printf("\nMasukkan nomor barang: ");
			        fgets(noBarang, 3, stdin);
			        fflush(stdin); // Membersihkan buffer input
			        noBarang[strcspn(noBarang, "\n")] = 0; // Menghapus newline
			
			        printf("Masukkan jumlah: ");
			        scanf("%d", &jumlah);
			        fflush(stdin); // Membersihkan buffer input
			
			        // Mencari barang dan menambahkannya ke keranjang
			        int found = 0;
			        int i;
			        for (i = 0; i < jumlahItemDiKeranjang; i++) {
			            if (strcmp(keranjang[i].no, noBarang) == 0) {
			               keranjang [i].jumlah+=jumlah;
			                found = 1;
			                break;
			            }
			        }
			        if (!found) {
			            struct Pembelian pembelian;
						strcpy (pembelian.no, noBarang);
						pembelian.jumlah = jumlah;
						keranjang[jumlahItemDiKeranjang++] = pembelian; 
			        }
			
			        printf("Apakah Anda ingin memasukkan barang lagi? (Y/N): ");
			        tambahLagi = getchar();
			        fflush(stdin); // Membersihkan buffer input
			    } while (tambahLagi == 'Y' || tambahLagi == 'y');
			    break;
            case 99: 
			    clearScreen();
			    
			    totalHarga = 0; // Mengatur ulang nilai
			    totalDiskon = 0; // Mengatur ulang nilai
			    totalBayar = 0; // Mengatur ulang nilai
			    bubbleSort(keranjang, jumlahItemDiKeranjang);
			    //Fungsi bubbleSort dipanggil untuk mengurutkan keranjang pembelian berdasarkan jumlah barang yang dibeli.
			    //Buat ngurutin array
			    
			    printf("Toko SENS\n");
			    printf("Jl. HOS Cokroaminoto No. 84, Denpasar\n");
			    printf("Bali\n");
			    printf("Telp : 0816285791\n");
			    printf("ID Struk : %s\n", strukId);
			    printf("==============================================================================\n");
			    printf("%-25s%-20s%-20s%-20s\n", "Nama Barang", "Harga", "Total", "Diskon");
			    printf("==============================================================================\n");
			
				int i;
			    for (i = 0; i < jumlahItemDiKeranjang; i++) {
			    	//Ini adalah loop yang mencetak rincian setiap barang dalam keranjang pembelian.
					// Untuk setiap barang, harga total dan diskon dihitung, kemudian dicetak bersama dengan nama barang dan jumlahnya.
				    int hargaItem = 0, jumlahItem = keranjang[i].jumlah, diskonItem = 0;
				    char namaBarangDanJumlah[50]; // Membuat string untuk menyimpan nama barang dan jumlahnya
					int j;
				    for (j = 0; j < MAX_ITEMS; j++) {
				        if (strcmp(keranjang[i].no, items[j].no) == 0) {
				            hargaItem = items[j].harga * jumlahItem;
				            if (jumlahItem > 5) {
				                diskonItem = hargaItem * 15 / 100;
				            } else if (jumlahItem > 3) {
				                diskonItem = hargaItem * 10 / 100;
				            }
				
				            sprintf(namaBarangDanJumlah, "%d x %s", jumlahItem, items[j].nama); // Menggabungkan jumlah dengan nama barang
				            printf("%-25s%-20d%-20d%-20d\n", namaBarangDanJumlah, items[j].harga, hargaItem, diskonItem);
				            break;
				        }
				    }
				    totalHarga += hargaItem;
				    totalDiskon += diskonItem;
				}
			
			    totalBayar = totalHarga - totalDiskon;
			
			    printf("==============================================================================\n");
			    printf("Total Harga  = Rp.%d,-\n", totalHarga);
			    printf("Total Diskon = Rp.%d,-\n", totalDiskon);
			    printf("Total Bayar  = Rp.%d,-\n", totalBayar);
			    printf("==============================================================================\n");
			
			    // Menghitung kembalian
			    printf("Masukkan uang bayar: ");
			    scanf("%d", &uangBayar);
			    
			    if (uangBayar < totalBayar) {
    			printf("Maaf, uang yang Anda bayarkan kurang. Silakan bayar dengan nominal yang sesuai.\n");
    			getchar(); // Membuang karakter newline di stdin
    			getchar(); // Menunggu hingga user menekan tombol Enter
    			break; // Keluar dari switch statement
					}

			    kembalian = uangBayar - totalBayar;
			    printf("Kembalian   = Rp.%d,-\n", kembalian);
			    printf("==============================================================================\n");


			    char filename[50];
			    time_t now;
			    struct tm *tm_now;
			    
			    time(&now);
			    tm_now = localtime(&now);
			
			    // Membuat nama file berdasarkan tanggal dan waktu
			    strftime(filename, sizeof(filename), "struk_belanja_%Y%m%d_%H%M%S.txt", tm_now);
			    
			    FILE *fp = fopen(filename, "w"); 
				//Ini membuat nama file berdasarkan tanggal dan waktu, kemudian membuka file tersebut dalam mode menulis ("w"). 
				//File ini akan digunakan untuk menyimpan struk pembayaran.
			    if (fp == NULL) {
			        printf("Gagal membuat file struk.\n");
			        break;
			    }
			
			    
			
			    fprintf(fp, "Toko SKENSA\n");
			    fprintf(fp, "Jl. HOS Cokroaminoto No. 84, Denpasar\n");
			    fprintf(fp, "Bali\n");
			    fprintf(fp, "Telp : 0816285791\n");
			    fprintf(fp, "ID Struk : %s\n", strukId);
			    fprintf(fp, "==============================================================================\n");
			    fprintf(fp, "%-25s%-20s%-20s%-20s\n", "Nama Barang", "Harga", "Total", "Diskon");
			    fprintf(fp, "==============================================================================\n");
				
				int k;
			    for (k = 0; k < jumlahItemDiKeranjang; k++) {
			        int hargaItem = 0, jumlahItem = keranjang[k].jumlah, diskonItem = 0;
			        char namaBarangDanJumlah[50]; // Membuat string untuk menyimpan nama barang dan jumlahnya
			        int m;
			        for (m = 0; m < MAX_ITEMS; m++) {
			            if (strcmp(keranjang[k].no, items[m].no) == 0) {
			                hargaItem = items[m].harga * jumlahItem;
			                if (jumlahItem > 5) {
			                    diskonItem = hargaItem * 15 / 100;
			                } else if (jumlahItem > 3) {
			                    diskonItem = hargaItem * 10 / 100;
			                }
							sprintf(namaBarangDanJumlah, "%d x %s", jumlahItem, items[m].nama); // Menggabungkan jumlah dengan nama barang
			                fprintf(fp, "%-25s%-20d%-20d%-20d\n", namaBarangDanJumlah, items[m].harga, hargaItem, diskonItem);
			                break;
			            }
			        }
			        //totalHarga += hargaItem;
			        //totalDiskon += diskonItem;
			    }
			
			    //totalBayar = totalHarga - totalDiskon;
			
			    fprintf(fp, "==============================================================================\n");
			    fprintf(fp, "Total Harga  = Rp.%d,-\n", totalHarga);
			    fprintf(fp, "Total Diskon = Rp.%d,-\n", totalDiskon);
			    fprintf(fp, "Total Bayar  = Rp.%d,-\n", totalBayar);
			    fprintf(fp, "==============================================================================\n");
			
			    // Menghitung kembalian
			    kembalian = uangBayar - totalBayar;
			    fprintf(fp, "Uang Bayar   = Rp.%d,-\n", uangBayar);
			    fprintf(fp, "Kembalian   = Rp.%d,-\n", kembalian);
			    fprintf(fp, "==============================================================================\n");
			    fprintf(fp, "Waktu/Hari : %s\n", tgl);
			    fprintf(fp, "==============================================================================\n");
			
			    fclose(fp);
			    //File ditutup menggunakan fclose().
			
			    printf("Struk belanja telah disimpan sebagai '%s'\n", filename);
			    
			
			    getchar(); // Menangkap Enter
			    getchar(); // Untuk menangkap Enter kedua kali
			    //Dua kali getchar() digunakan untuk menangkap enter agar program menunggu pengguna menekan tombol enter sebelum melanjutkan.
			    break;
			    

			

            case 55:
                // Mengosongkan keranjang
                jumlahItemDiKeranjang = 0;
                totalHarga = 0;
                totalDiskon = 0;
                totalBayar = 0;

                printf("Keranjang pembelian telah direset.\n");
                getchar(); // Menangkap Enter
                break;
            case 00:
                printf("Keluar dari program.\n");
                return 0; //Fungsi return 0; digunakan untuk keluar dari program.
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                //Setelah menjalankan kasus yang sesuai dengan pilihan pengguna, program kembali ke awal loop while (1) untuk menampilkan menu lagi dan meminta pilihan pengguna selanjutnya.
				// Program terus berjalan hingga pengguna memilih untuk keluar dari program.
        }
    }

    return 0;
}

