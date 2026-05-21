#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Deadline {
    string namaTugas;
    string kategori;

    int hari;
    int bulan;
    int tahun;

    int sisaHari;

    Deadline* next;
    Deadline* prev;
};

Deadline* head = NULL;
Deadline* tail = NULL;

int curDay, curMonth, curYear;

int totalHari(int d, int m, int y) {
    return (y * 365) + (m * 30) + d;
}

int hitungSisaHari(int d, int m, int y) {
    return totalHari(d, m, y) - totalHari(curDay, curMonth, curYear);
}

string formatTanggal(int d, int m, int y) {

    string dd;
    string mm;

    if (d < 10)
        dd = "0" + to_string(d);
    else
        dd = to_string(d);

    if (m < 10)
        mm = "0" + to_string(m);
    else
        mm = to_string(m);

    return dd + "-" + mm + "-" + to_string(y);
}

void tambahDeadline() {

    Deadline* baru = new Deadline;

    cin.ignore();

    cout << "\nNama Tugas : ";
    getline(cin, baru->namaTugas);

    cout << "Kategori   : ";
    getline(cin, baru->kategori);

    cout << "Deadline (DD MM YYYY): ";
    cin >> baru->hari >> baru->bulan >> baru->tahun;

    baru->sisaHari = hitungSisaHari(
        baru->hari,
        baru->bulan,
        baru->tahun
    );

    baru->next = NULL;
    baru->prev = NULL;
    
    if (head == NULL) {
		head = tail = baru;
	} else {
		tail->next = baru;
		baru->prev = tail;
		
		tail = baru;
	}

    cout << "\nDeadline berhasil ditambahkan!\n";
}

void tampilkanDeadline() {

    if (head == NULL) {
        cout << "\nBelum ada deadline.\n";
        return;
    }

    Deadline* curr = head;

    cout << "\n================================================================================\n";
    cout << "                              DAFTAR DEADLINE\n";
    cout << "================================================================================\n";

    cout << left
         << setw(5)  << "ID"
         << setw(25) << "Nama Tugas"
         << setw(20) << "Kategori"
         << setw(15) << "Deadline"
         << "Sisa\n";

    cout << "--------------------------------------------------------------------------------\n";

    int id = 1;

    while (curr != NULL) {

        cout << left
             << setw(5)  << id++
             << setw(25) << curr->namaTugas
             << setw(20) << curr->kategori
             << setw(15) << formatTanggal(
                                curr->hari,
                                curr->bulan,
                                curr->tahun)
             << curr->sisaHari << " Hari";

        if (curr->sisaHari <= 3) {
            cout << " [URGENT]";
        }

        cout << endl;

        curr = curr->next;
    }

    cout << "================================================================================\n";
}

void cariDeadline() {

    if (head == NULL) {
        cout << "\nData kosong.\n";
        return;
    }

    cin.ignore();

    string cari;
    cout << "\nMasukkan nama tugas : ";
    getline(cin, cari);

    Deadline* curr = head;
    bool ditemukan = false;

    while (curr != NULL) {

        if (curr->namaTugas == cari) {

            cout << "\nDeadline ditemukan!\n";

            cout << "Nama Tugas : " << curr->namaTugas << endl;
            cout << "Kategori   : " << curr->kategori << endl;
            cout << "Deadline   : "
                 << formatTanggal(
                        curr->hari,
                        curr->bulan,
                        curr->tahun)
                 << endl;

            cout << "Sisa Hari  : "
                 << curr->sisaHari
                 << " Hari\n";

            ditemukan = true;
            break;
        }

        curr = curr->next;
    }

    if (!ditemukan) {
        cout << "\nDeadline tidak ditemukan.\n";
    }
}

void sortTerdekat() {

    if (head == NULL || head->next == NULL)
        return;

    bool swapData;

    do {

        swapData = false;

        Deadline* curr = head;

        while (curr->next != NULL) {

            if (curr->sisaHari > curr->next->sisaHari) {

                swap(curr->namaTugas,
                     curr->next->namaTugas);

                swap(curr->kategori,
                     curr->next->kategori);

                swap(curr->hari,
                     curr->next->hari);

                swap(curr->bulan,
                     curr->next->bulan);

                swap(curr->tahun,
                     curr->next->tahun);

                swap(curr->sisaHari,
                     curr->next->sisaHari);

                swapData = true;
            }

            curr = curr->next;
        }

    } while (swapData);

    cout << "\nBerhasil diurutkan dari deadline terdekat.\n";
}

void sortTerlama() {

    if (head == NULL || head->next == NULL)
        return;

    bool swapData;

    do {

        swapData = false;

        Deadline* curr = head;

        while (curr->next != NULL) {

            if (curr->sisaHari < curr->next->sisaHari) {

                swap(curr->namaTugas,
                     curr->next->namaTugas);

                swap(curr->kategori,
                     curr->next->kategori);

                swap(curr->hari,
                     curr->next->hari);

                swap(curr->bulan,
                     curr->next->bulan);

                swap(curr->tahun,
                     curr->next->tahun);

                swap(curr->sisaHari,
                     curr->next->sisaHari);

                swapData = true;
            }

            curr = curr->next;
        }

    } while (swapData);

    cout << "\nBerhasil diurutkan dari deadline terlama.\n";
}

void hapusDeadline() {

    if (head == NULL) {
        cout << "\nData kosong.\n";
        return;
    }

    tampilkanDeadline();

    int id;
    cout << "\nMasukkan ID yang ingin dihapus : ";
    cin >> id;

    Deadline* curr = head;

    int posisi = 1;

    while (curr != NULL && posisi < id) {
        curr = curr->next;
        posisi++;
    }

    if (curr == NULL) {
        cout << "\nID tidak ditemukan.\n";
        return;
    }

    if (curr == head) {

        head = head->next;

        if (head != NULL)
            head->prev = NULL;
    }
    else if (curr == tail) {

        tail = tail->prev;
        tail->next = NULL;
    }
    else {

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete curr;

    cout << "\nDeadline berhasil dihapus.\n";
}

void statistik() {

    int total = 0;
    int urgent = 0;

    Deadline* curr = head;

    while (curr != NULL) {

        total++;

        if (curr->sisaHari <= 3) {
            urgent++;
        }

        curr = curr->next;
    }

    cout << "\n=========== STATISTIK ===========\n";
    cout << "Total Deadline : " << total << endl;
    cout << "Deadline Urgent: " << urgent << endl;
    cout << "=================================\n";
}

void simpanFile() {

    FILE* file = fopen("deadline.txt", "w");

    if (file == NULL) {
        return;
    }

    Deadline* curr = head;

    while (curr != NULL) {

        fprintf(file,
                "%s|%s|%d|%d|%d\n",

                curr->namaTugas.c_str(),
                curr->kategori.c_str(),

                curr->hari,
                curr->bulan,
                curr->tahun);

        curr = curr->next;
    }

    fclose(file);
}

void loadFile() {

    FILE* file = fopen("deadline.txt", "r");

    if (file == NULL) {
        return;
    }

    char nama[100];
    char kategori[100];

    int h, b, t;

    while (fscanf(file,
                  "%[^|]|%[^|]|%d|%d|%d\n",
                  nama,
                  kategori,
                  &h,
                  &b,
                  &t) != EOF) {

        Deadline* baru = new Deadline;

        baru->namaTugas = nama;
        baru->kategori = kategori;

        baru->hari = h;
        baru->bulan = b;
        baru->tahun = t;

        baru->sisaHari = hitungSisaHari(h, b, t);

        baru->next = NULL;
        baru->prev = NULL;

        if (head == NULL) {
            head = tail = baru;
        }
        else {
            tail->next = baru;
            baru->prev = tail;

            tail = baru;
        }
    }

    fclose(file);
}

void menu() {

    int pilih;

    do {
        system("CLS")

        cout << "\n==============================\n";
        cout << "      DEADLINE TRACKER\n";
        cout << "==============================\n";

        cout << "1. Lihat Semua Deadline\n";
        cout << "2. Tambah Deadline\n";
        cout << "3. Cari Deadline\n";
        cout << "4. Urutkan Deadline\n";
        cout << "5. Hapus Deadline\n";
        cout << "6. Statistik\n";
        cout << "0. Keluar\n";

        cout << "==============================\n";
        cout << "Pilih menu : ";
        cin >> pilih;

        switch (pilih) {

            case 1:
                tampilkanDeadline();
                break;

            case 2:
                tambahDeadline();
                simpanFile();
                break;

            case 3:
                cariDeadline();
                break;

            case 4: {

                int opsi;

                cout << "\n1. Deadline Terdekat\n";
                cout << "2. Deadline Terlama\n";
                cout << "Pilih : ";
                cin >> opsi;

                if (opsi == 1)
                    sortTerdekat();
                else
                    sortTerlama();

                tampilkanDeadline();

                break;
            }

            case 5:
                hapusDeadline();
                simpanFile();
                break;

            case 6:
                statistik();
                break;

            case 0:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nMenu tidak tersedia.\n";
        }
        
        system("pause");
    } while (pilih != 0);
}

int main() {

    cout << "Masukkan tanggal hari ini\n";
    cout << "(DD MM YYYY): ";

    cin >> curDay >> curMonth >> curYear;

    loadFile();

    menu();

    return 0;
}
