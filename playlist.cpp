#include <iostream>
#include <cstring>
using namespace std;

struct Lagu {
    char judul[50];
    char penyanyi[50];
    char genre[50];
    bool favorit;
};

struct Node  {
    Lagu data;
    Node* prev;
    Node* next;
};

struct Playlist {
    char nama[50];
    Node* head;
    Node* tail;
    Playlist* next;
};

Playlist* headPlaylist = nullptr;

// Fungsi cek cari playlist
Playlist* cariPlaylist(const char* nama) {
    Playlist* temp = headPlaylist;
    while (temp) {
        if (strcmp(temp->nama, nama) == 0)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi buat cek cari lagu
Node* cariLaguNode(Playlist* pl, const char* judul) {
    Node* temp = pl->head;
    while (temp) {
        if (strcmp(temp->data.judul, judul) == 0)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Menu 1 Buat Playlist
void buatPlaylist() {
    Playlist* baru = new Playlist;
    cout << "Masukkan nama playlist: ";
    cin.getline(baru->nama, 50);
    baru->head = baru->tail = nullptr;
    baru->next = nullptr;

    if (!headPlaylist)
        headPlaylist = baru;
    else {
        Playlist* temp = headPlaylist;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
    cout << "Playlist berhasil dibuat!\n";
}

// Menu 2 Tambah Lagu
void tambahLagu(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) {
        cout << "Playlist tidak ditemukan!\n";
        return;
    }

    int jumlah;
    cout << "Masukkan jumlah lagu yang ingin ditambahkan: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        Node* baru = new Node;
        cout << "Judul lagu     : "; cin.getline(baru->data.judul, 50);
        cout << "Penyanyi       : "; cin.getline(baru->data.penyanyi, 50);
        cout << "Genre          : "; cin.getline(baru->data.genre, 50);
        char fav;
        cout << "Favorit? (y/n) : "; cin >> fav; cin.ignore();
        baru->data.favorit = (fav == 'y' || fav == 'Y');
        baru->prev = baru->next = nullptr;
        
        if (!pl->head)
        pl->head = pl->tail = baru;
        else {
            pl->tail->next = baru;
            baru->prev = pl->tail;
            pl->tail = baru;

            cout << endl;
        }
    }
}

// Menu 3 cari Lagu
void cariLagu(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) {
        cout << "Playlist tidak ditemukan!\n";
        return;
    }

    char judul[50];
    cout << "Masukkan judul lagu yang dicari: ";
    cin.getline(judul, 50);

    Node* found = cariLaguNode(pl, judul);
    if (found) {
        cout << "Lagu ditemukan!\n";
        cout << "Judul Lagu : " << found->data.judul << "\n";
        cout << "Penyanyi   : " << found->data.penyanyi << "\n";
        cout << "Genre      : " << found->data.genre << "\n";
        cout << "Favorit    : " << (found->data.favorit ? "Ya" : "Tidak") << "\n";
    } else {
        cout << "Lagu tidak ditemukan.\n";
    }
}

// Menu 4 Tampil semua lagu
void tampilkanSemuaLagu() {
    Playlist* pl = headPlaylist;
    while (pl) {
        cout << "\nPlaylist: " << pl->nama << endl;
        Node* lagu = pl->head;
        int i = 1;
        while (lagu) {
            cout << "  Lagu ke-" << i++ << " : " << lagu->data.judul << " - " << lagu->data.penyanyi << " (" << lagu->data.genre << ")";
            cout << (lagu->data.favorit ? " (Favorit)" : "") << endl;
            lagu = lagu->next;
        }
        pl = pl->next;
    }
}

// Menu 4 Tampil lagu dari playlist
void tampilkanLagu(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) {
        cout << "Playlist tidak ditemukan!\n";
        return;
    }

    Node* lagu = pl->head;
    int i = 1;
    cout << "\nPlaylist: " << pl->nama << "\n";
    while (lagu) {
        cout << "  Lagu ke-" << i++ << " : " << lagu->data.judul << " - " << lagu->data.penyanyi<< " (" << lagu->data.genre << ")";
        cout << (lagu->data.favorit ? " (Favorit)" : "") << "\n";
        lagu = lagu->next;
    }
}

// Menu 4 Pilihan tampil lagu
void tampilkanLaguPilihan() {
    int pilihan;
    cout << "=================================================\n";
    cout << "||               TAMPILKAN LAGU                ||\n";
    cout << "=================================================\n";
    cout << "|| 1. Tampilkan semua lagu                     ||\n";
    cout << "|| 2. Tampilkan lagu dari playlist tertentu    ||\n";
    cout << "=================================================\n";
    cout << "Pilihan: ";
    cin >> pilihan; cin.ignore();

    if (pilihan == 1) {
        tampilkanSemuaLagu();
    } else if (pilihan == 2) {
        char nama[50];
        cout << "Masukkan nama playlist: ";
        cin.getline(nama, 50);
        tampilkanLagu(nama); // fungsi ini sekarang sudah ada
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// Menu 5 Lagu Favorit
void laguFavorit() {
    Playlist* pl = headPlaylist;
    while (pl) {
        Node* temp = pl->head;
        while (temp) {
            if (temp->data.favorit) {
                cout << "\n[Playlist    : " << pl->nama << "]\n";
                cout << "   Judul      : " << temp->data.judul << "\n";
                cout << "   Penyanyi   : " << temp->data.penyanyi << "\n";
                cout << "   Genre      : " << temp->data.genre << "\n";
            }
            temp = temp->next;
        }
        pl = pl->next;
    }
}

// Menu 6 Edit Lagu
void editLagu(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) return;

    char judul[50];
    cout << "Judul lagu yang ingin diedit: ";
    cin.getline(judul, 50);

    Node* node = cariLaguNode(pl, judul);
    if (!node) {
        cout << "Lagu tidak ditemukan!\n";
        return;
    }

    cout << "Judul baru     : "; cin.getline(node->data.judul, 50);
    cout << "Penyanyi baru  : "; cin.getline(node->data.penyanyi, 50);
    cout << "Genre baru     : "; cin.getline(node->data.genre, 50);
    char fav;
    cout << "Favorit (y/n)? "; cin >> fav; cin.ignore();
    node->data.favorit = (fav == 'y' || fav == 'Y');
    cout << "Lagu berhasil diedit!\n";
}

// Menu 7 hapus lagu
void hapusLagu(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) return;

    char judul[50];
    cout << "Masukkan judul lagu yang ingin dihapus: ";
    cin.getline(judul, 50);
    Node* del = cariLaguNode(pl, judul);
    if (!del) return;

    if (del == pl->head && del == pl->tail)
        pl->head = pl->tail = nullptr;
    else if (del == pl->head) {
        pl->head = del->next;
        pl->head->prev = nullptr;
    } else if (del == pl->tail) {
        pl->tail = del->prev;
        pl->tail->next = nullptr;
    } else {
        del->prev->next = del->next;
        del->next->prev = del->prev;
    }

    delete del;
    cout << "Lagu berhasil dihapus!\n";
}

// Menu 8 Hapus isi lagu di playlist
void kosongkanPlaylist(const char* namaPlaylist) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) return;

    Node* temp = pl->head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    pl->head = pl->tail = nullptr;
    cout << "Playlist berhasil dikosongkan!\n";
}

// Menu 9 Sorting lagu pake bubble sort
void sortingLagu(const char* namaPlaylist, bool ascending) {
    Playlist* pl = cariPlaylist(namaPlaylist);
    if (!pl) return;
    if (!pl->head || !pl->head->next) return;

    bool swapped;
    do {
        swapped = false;
        Node* curr = pl->head;
        while (curr->next) {
            bool kondisi = ascending ?
                strcmp(curr->data.judul, curr->next->data.judul) > 0 :
                strcmp(curr->data.judul, curr->next->data.judul) < 0;

            if (kondisi) {
                swap(curr->data, curr->next->data);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);

    cout << "Lagu berhasil diurutkan.\n";
}

// Menyimpan ke file
void simpanFile() {
    FILE* fp = fopen("playlist.dat", "wb");
    Playlist* pl = headPlaylist;

    while (pl) {
        fwrite(pl->nama, sizeof(pl->nama), 1, fp);

        Node* lagu = pl->head;
        while (lagu) {
            fwrite(&lagu->data, sizeof(Lagu), 1, fp);
            lagu = lagu->next;
        }

        // penanda akhir playlist
        Lagu penanda = { "#", "#", "#", false };
        fwrite(&penanda, sizeof(Lagu), 1, fp);
        pl = pl->next;
    }

    fclose(fp);
}

// Load dari file.dat
void loadFile() {
    FILE* fp = fopen("playlist.dat", "rb");
    if (!fp) return;

    while (!feof(fp)) {
        Playlist* baru = new Playlist;
        if (fread(baru->nama, sizeof(baru->nama), 1, fp) != 1) {
            delete baru;
            break;
        }

        baru->head = baru->tail = nullptr;
        baru->next = nullptr;

        Lagu temp;
        while (fread(&temp, sizeof(Lagu), 1, fp) == 1) {
            if (strcmp(temp.judul, "#") == 0) break;

            Node* lagu = new Node{ temp, nullptr, nullptr };
            if (!baru->head) baru->head = baru->tail = lagu;
            else {
                baru->tail->next = lagu;
                lagu->prev = baru->tail;
                baru->tail = lagu;
            }
        }

        if (!headPlaylist) headPlaylist = baru;
        else {
            Playlist* tmp = headPlaylist;
            while (tmp->next) tmp = tmp->next;
            tmp->next = baru;
        }
    }

    fclose(fp);
}

void menu() {
    int pil;
    char nama[50];
    loadFile();

    do {
        system("cls");
        cout << "=====================================\n";
        cout << "||               MENU              ||\n";
        cout << "=====================================\n";
        cout << "|| 1. Buat Playlist                ||\n";
        cout << "|| 2. Tambah Lagu                  ||\n";
        cout << "|| 3. Tampil Semua Lagu            ||\n";
        cout << "|| 4. Lagu Favorit                 ||\n";
        cout << "|| 5. Cari Lagu                    ||\n";
        cout << "|| 6. Sorting Lagu                 ||\n";
        cout << "|| 7. Edit Lagu                    ||\n";
        cout << "|| 8. Hapus Lagu                   ||\n";
        cout << "|| 9. Kosongkan Playlist           ||\n";
        cout << "|| 10. Keluar dan Simpan File      ||\n";
        cout << "=====================================\n";
        cout << "Pilihan: ";
        cin >> pil;
        cin.ignore();

        switch (pil) {
            case 1: buatPlaylist(); break;
            case 2: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50); tambahLagu(nama); break;
            case 3: tampilkanLaguPilihan(); break;
            case 4: laguFavorit(); break;
            case 5: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50); cariLagu(nama); break;
            case 6: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50);
                    char urut; cout << "Urutan (a/d): "; cin >> urut; cin.ignore();
                    sortingLagu(nama, urut == 'a'); break;
            case 7: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50); editLagu(nama); break;
            case 8: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50); hapusLagu(nama); break;
            case 9: cout << "Masukkan Nama Playlist: "; cin.getline(nama, 50); kosongkanPlaylist(nama); break;
            case 10: simpanFile(); cout << "Terima Kasih! Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

        cout << endl << endl;
        system("pause");

    } while (pil != 10);
}


int main(){
    menu();
    return 0;
}