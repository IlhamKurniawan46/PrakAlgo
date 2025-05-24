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

int main(){
    //testcommit
    // nando commit
}