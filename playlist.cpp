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
    cout << "Jumlah lagu yang ingin ditambahkan: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        Node* baru = new Node;
        cout << "Judul lagu: "; cin.getline(baru->data.judul, 50);
        cout << "Penyanyi: "; cin.getline(baru->data.penyanyi, 50);
        cout << "Genre: "; cin.getline(baru->data.genre, 50);
        char fav;
        cout << "Favorit? (y/n): "; cin >> fav; cin.ignore();
        baru->data.favorit = (fav == 'y' || fav == 'Y');
        baru->prev = baru->next = nullptr;

        if (!pl->head)
            pl->head = pl->tail = baru;
        else {
            pl->tail->next = baru;
            baru->prev = pl->tail;
            pl->tail = baru;
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
    cout << "Judul lagu dicari: ";
    cin.getline(judul, 50);

    Node* found = cariLaguNode(pl, judul);
    if (found) {
        cout << "Lagu ditemukan!\n";
        cout << "Judul: " << found->data.judul << "\n";
        cout << "Penyanyi: " << found->data.penyanyi << "\n";
        cout << "Genre: " << found->data.genre << "\n";
        cout << "Favorit: " << (found->data.favorit ? "Ya" : "Tidak") << "\n";
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
            cout << (lagu->data.favorit ? " (❤︎)" : "") << endl;
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
        cout << (lagu->data.favorit ? " (❤︎)" : "") << "\n";
        lagu = lagu->next;
    }
}

// Menu 4 Pilihan tampil lagu
void tampilkanLaguPilihan() {
    int pilihan;
    cout << "1. Tampil semua lagu\n";
    cout << "2. Tampil lagu dari playlist tertentu\n";
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
                cout << "\n[Playlist: " << pl->nama << "]\n";
                cout << "Judul: " << temp->data.judul << "\n";
                cout << "Penyanyi: " << temp->data.penyanyi << "\n";
                cout << "Genre: " << temp->data.genre << "\n";
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

    cout << "Judul baru: "; cin.getline(node->data.judul, 50);
    cout << "Penyanyi baru: "; cin.getline(node->data.penyanyi, 50);
    cout << "Genre baru: "; cin.getline(node->data.genre, 50);
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
    cout << "Judul lagu yang ingin dihapus: ";
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
    cout << "Lagu dihapus!\n";
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
    cout << "Playlist dikosongkan!\n";
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

    cout << "Lagu berhasil disorting.\n";
}

int main(){
    //testcommit
    // nando commit
}