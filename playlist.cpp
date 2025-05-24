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

int main(){
    //testcommit
    // nando commit
}