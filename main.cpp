#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono> // Untuk pengukuran waktu

using namespace std;
using namespace chrono;

// ADT untuk Database Kendaraan
struct VehicleDatabase {
    vector<string> plates;

    // Tambahkan plat nomor ke database
    void addPlate(const string& plate) {
        plates.push_back(plate);
    }

    // Tampilkan seluruh plat nomor
    void display() const {
        if (plates.empty()) {
            cout << "Database kosong.\n";
        } else {
            cout << "Database Plat Nomor:\n";
            for (const auto& plate : plates)
                cout << "- " << plate << "\n";
        }
    }

    // Urutkan plat nomor (dibutuhkan untuk Binary Search)
    void sortDatabase() {
        sort(plates.begin(), plates.end());
    }
};

// Fungsi Linear Search
int linearSearch(const vector<string>& data, const string& target) {
    for (size_t i = 0; i < data.size(); ++i) { // Iterasi dari awal hingga akhir
        if (data[i] == target)
            return i; // Kembalikan indeks jika ditemukan
    }
    return -1; // Kembalikan -1 jika tidak ditemukan
}

// Fungsi Binary Search (rekursif)
int binarySearch(const vector<string>& data, const string& target, int low, int high) {
    if (low > high)
        return -1; // Basis: Jika low > high, data tidak ditemukan

    int mid = low + (high - low) / 2; // Tentukan titik tengah

    if (data[mid] == target)
        return mid; // Basis: Jika data ditemukan di mid, kembalikan indeks
    else if (data[mid] > target)
        return binarySearch(data, target, low, mid - 1); // Rekurens: Cari di kiri
    else
        return binarySearch(data, target, mid + 1, high); // Rekurens: Cari di kanan
}

// Fungsi Linear Search dengan pengukuran waktu
void testLinearSearch(const VehicleDatabase& db, const string& target) {
    const int iterations = 1000; // Jumlah pengulangan
    auto start = high_resolution_clock::now(); // Mulai waktu

    for (int i = 0; i < iterations; ++i) {
        linearSearch(db.plates, target);
    }

    auto end = high_resolution_clock::now(); // Akhiri waktu

    cout << "Linear Search dilakukan sebanyak " << iterations << " kali.\n";
    cout << "Waktu eksekusi total: "
         << duration_cast<microseconds>(end - start).count()
         << " mikrodetik\n";
    cout << "Rata-rata waktu eksekusi: "
         << duration_cast<microseconds>(end - start).count() / iterations
         << " mikrodetik\n";
}

// Fungsi Binary Search dengan pengukuran waktu
void testBinarySearch(VehicleDatabase& db, const string& target) {
    db.sortDatabase(); // Urutkan data terlebih dahulu
    const int iterations = 1000; // Jumlah pengulangan
    auto start = high_resolution_clock::now(); // Mulai waktu

    for (int i = 0; i < iterations; ++i) {
        binarySearch(db.plates, target, 0, db.plates.size() - 1);
    }

    auto end = high_resolution_clock::now(); // Akhiri waktu

    cout << "Binary Search dilakukan sebanyak " << iterations << " kali.\n";
    cout << "Waktu eksekusi total: "
         << duration_cast<microseconds>(end - start).count()
         << " mikrodetik\n";
    cout << "Rata-rata waktu eksekusi: "
         << duration_cast<microseconds>(end - start).count() / iterations
         << " mikrodetik\n";
}

// Fungsi untuk menampilkan menu
void displayMenu() {
    cout << "\n===========================\n";
    cout << "    Sistem Pencarian Plat\n";
    cout << "===========================\n";
    cout << "1. Tampilkan Database\n";
    cout << "2. Tambahkan Plat Nomor\n";
    cout << "3. Cari Plat Nomor (Linear Search)\n";
    cout << "4. Cari Plat Nomor (Binary Search)\n";
    cout << "5. Urutkan Database\n";
    cout << "6. Tambahkan Data Acak (10.000 Plat)\n";
    cout << "7. Keluar\n";
    cout << "Pilih opsi: ";
}

int main() {
    VehicleDatabase db;
    int choice;
    string plate;

    // Menu interaktif
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                db.display();
                break;

            case 2:
                cout << "Masukkan plat nomor yang ingin ditambahkan: ";
                cin >> plate;
                db.addPlate(plate);
                cout << "Plat nomor berhasil ditambahkan.\n";
                break;

            case 3:
                cout << "Masukkan plat nomor yang ingin dicari (Linear Search): ";
                cin >> plate;
                testLinearSearch(db, plate);
                break;

            case 4:
                cout << "Masukkan plat nomor yang ingin dicari (Binary Search): ";
                cin >> plate;
                testBinarySearch(db, plate);
                break;

            case 5:
                db.sortDatabase();
                cout << "Database berhasil diurutkan.\n";
                break;

            case 6:
                for (int i = 0; i < 10000; ++i) {
                    db.addPlate("P" + to_string(rand() % 10000));
                }
                cout << "10.000 plat nomor acak berhasil ditambahkan.\n";
                break;

            case 7:
                cout << "Keluar dari program. Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (choice != 7);

    return 0;
}
