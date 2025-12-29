#include <iostream>
#include <string>
#include <stdlib.h> // Untuk system("cls")

using namespace std;

// Struct untuk data Unit PS
struct UnitPS {
    string kodeUnit;
    string jenisConsole; // PS3 atau PS4
    long hargaPerJam;
};

// Variabel Global (Sederhana array statis)
UnitPS daftarUnit[10];
int jumlahUnit = 0;

void clearScreen() {
    system("cls"); // Clear
}

int main() {
    int pilihanUtama, pilihanSub;
    char kembali;

    do {
        clearScreen();
        // Tampilan Menu Utama 
        cout << "========================================" << endl;
        cout << "    SISTEM RENTAL PLAYSTATION FAHRY" << endl;
        cout << "========================================" << endl;
        cout << "1. Pengelolaan Billing (Unit PS)" << endl;
        cout << "2. Sistem Pembayaran (Transaksi)" << endl;
        cout << "3. Keluar" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pilihanUtama;

        switch (pilihanUtama) {
            
            // --- BAGIAN A: PENGELOLAAN BILLING---
            case 1: 
                do {
                    clearScreen();
                    // Tampilan Sub-Menu Mengelola 
                    cout << "HALAMAN PENGELOLAAN BILLING" << endl;
                    cout << "===========================" << endl;
                    cout << "1. Tambah Unit PS" << endl;
                    cout << "2. Edit Tarif Unit" << endl;
                    cout << "3. Lihat Daftar Unit" << endl;
                    cout << "Masukkan Pilihan : ";
                    cin >> pilihanSub;

                    if (pilihanSub == 1) {
                        // Form Tambah Unit 
                        clearScreen();
                        cout << "FORM TAMBAH UNIT PS" << endl;
                        cout << "===================" << endl;
                        cout << "Input Kode Unit (cth: TV01) : ";
                        cin >> daftarUnit[jumlahUnit].kodeUnit;
                        cout << "Input Jenis Console (PS3/PS4): ";
                        cin >> daftarUnit[jumlahUnit].jenisConsole;
                        cout << "Input Harga Per Jam         : ";
                        cin >> daftarUnit[jumlahUnit].hargaPerJam;
                        
                        jumlahUnit++; // Tambah counter unit
                        cout << "\nData Berhasil Disimpan!" << endl;

                    } else if (pilihanSub == 2) {
                        // Form Edit (Sederhana)
                        clearScreen();
                        string kodeCari;
                        cout << "FORM EDIT TARIF UNIT" << endl;
                        cout << "Masukkan Kode Unit yg diedit: ";
                        cin >> kodeCari;
                        
                        bool found = false;
                        for(int i=0; i<jumlahUnit; i++) {
                            if(daftarUnit[i].kodeUnit == kodeCari) {
                                cout << "Harga Lama: " << daftarUnit[i].hargaPerJam << endl;
                                cout << "Input Harga Baru: ";
                                cin >> daftarUnit[i].hargaPerJam;
                                cout << "Data Berhasil Diupdate!" << endl;
                                found = true;
                                break;
                            }
                        }
                        if(!found) cout << "Unit tidak ditemukan!" << endl;

                    } else if (pilihanSub == 3) {
                        // Form Lihat Data
                        clearScreen();
                        cout << "DAFTAR UNIT PS TERDAFTAR" << endl;
                        cout << "========================" << endl;
                        for(int i=0; i<jumlahUnit; i++) {
                            cout << i+1 << ". Kode: " << daftarUnit[i].kodeUnit 
                                 << " | Jenis: " << daftarUnit[i].jenisConsole 
                                 << " | Harga: Rp " << daftarUnit[i].hargaPerJam << endl;
                        }
                    }

                    cout << "\nApakah ingin kembali ke halaman pengelolaan billing? (y/t): ";
                    cin >> kembali;
                } while (kembali == 'y' || kembali == 'Y');
                break;

            // --- BAGIAN B: SISTEM PEMBAYARAN ---
            case 2:
                do {
                    clearScreen();
                    // Tampilan Menu Transaksi (Menggabungkan Pendaftaran & Pembayaran)
                    cout << "HALAMAN SISTEM PEMBAYARAN" << endl;
                    cout << "=========================" << endl;
                    cout << "1. Paket Hemat (Prepaid - Bayar Awal)" << endl;
                    cout << "2. Open Time (Postpaid - Bayar Akhir)" << endl;
                    cout << "Masukkan Pilihan : ";
                    cin >> pilihanSub;

                    string namaPelanggan, kodeUnitPilih;
                    int durasi;
                    long totalBayar, bayar, kembaliUang;

                    if (pilihanSub == 1) {
                        // Logika PREPAID (Paket Hemat)
                        clearScreen();
                        cout << "TRANSAKSI PAKET HEMAT (PREPAID)" << endl;
                        cout << "===============================" << endl;
                        cout << "Input Kode Unit      : "; cin >> kodeUnitPilih;
                        cout << "Input Nama Pelanggan : "; cin.ignore(); getline(cin, namaPelanggan);
                        cout << "Pilih Durasi (jam)   : "; cin >> durasi;
                        
                        // Cari harga unit
                        long harga = 0;
                        for(int i=0; i<jumlahUnit; i++) {
                            if(daftarUnit[i].kodeUnit == kodeUnitPilih) {
                                harga = daftarUnit[i].hargaPerJam;
                            }
                        }
                        
                        if(harga > 0) {
                            totalBayar = harga * durasi;
                            cout << "Total Tagihan        : Rp " << totalBayar << endl;
                            cout << "Masukkan Pembayaran  : Rp "; cin >> bayar;
                            
                            if (bayar >= totalBayar) {
                                cout << "\n--- STRUK PEMBAYARAN ---" << endl;
                                cout << "Status: LUNAS (Prepaid)" << endl;
                                cout << "Unit  : " << kodeUnitPilih << endl;
                                cout << "Waktu : " << durasi << " Jam" << endl;
                                cout << "Kembali: Rp " << (bayar - totalBayar) << endl;
                                cout << "Timer Otomatis ON." << endl;
                            } else {
                                cout << "Uang tidak cukup!" << endl;
                            }
                        } else {
                            cout << "Kode Unit tidak valid!" << endl;
                        }

                    } else if (pilihanSub == 2) {
                        // Logika POSTPAID (Open Time)
                        clearScreen();
                        cout << "TRANSAKSI OPEN TIME (POSTPAID)" << endl;
                        cout << "==============================" << endl;
                        cout << "Input Kode Unit      : "; cin >> kodeUnitPilih;
                        cout << "Input Nama Pelanggan : "; cin.ignore(); getline(cin, namaPelanggan);
                        cout << "Input Deposit (Opsional): Rp "; cin >> bayar;
                        
                        cout << "\n--- STATUS BILLING ---" << endl;
                        cout << "Mode  : OPEN TIME" << endl;
                        cout << "Unit  : " << kodeUnitPilih << " (Aktif)" << endl;
                        cout << "Timer : 00:00:00 (Berjalan)" << endl;
                        cout << "Status: POSTPAID (Bayar Belakang)" << endl;
                    }

                    cout << "\nApakah ingin kembali ke menu pembayaran? (y/t): ";
                    cin >> kembali;
                } while (kembali == 'y' || kembali == 'Y');
                break;
                
            case 3:
                cout << "Terima kasih!" << endl;
                return 0;
        }
        
        // Loop untuk Menu Utama
        if (pilihanUtama != 1 && pilihanUtama != 2 && pilihanUtama != 3) {
             cout << "Pilihan salah, kembali ke menu utama..." << endl;
        }
        
    } while (pilihanUtama != 3);

    return 0;
}
