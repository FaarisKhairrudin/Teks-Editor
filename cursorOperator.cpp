#include <iostream>
#include "header.h"

using namespace std;

void moveRightCursor(List &L) { // memindahkan kursor ke kanan
    if (L.cursor.head != L.cursor.tail) {           // kondisi ketika kursor sedang memblok
        L.cursor.head = L.cursor.tail;
    } else if (L.cursor.head != nullptr){
        if (L.cursor.head != L.tail) {
            L.cursor.head = L.cursor.head->next;
        }
    } else { // kondisi ketika kursor di null (paling kiri)
        L.cursor.head = L.head;
    }
    L.cursor.tail = L.cursor.head;
}

void moveRightCursorHead(List &L) { // memindahkan kursor head ke kanan
    if (L.cursor.head != nullptr){
        if (L.cursor.head != L.tail) {
            L.cursor.head = L.cursor.head->next;
        }
    } else {
        L.cursor.head = L.head;
    }
}

void moveRightCursorTail(List &L) { // // memindahkan kursor tail ke kanan
    if (L.cursor.tail != nullptr){
        if (L.cursor.tail != L.tail) {
            L.cursor.tail = L.cursor.tail->next;
        }
    } else {
        L.cursor.tail = L.head;
    }
}

void moveLeftCursor(List &L) { // memindahkan kursor ke kiri
    if (L.cursor.head != L.cursor.tail) {
        L.cursor.tail = L.cursor.head;
    } else if (L.cursor.head != nullptr){
        L.cursor.head = L.cursor.head->prev;
        L.cursor.tail = L.cursor.head;
    }
}

void moveLeftCursorHead(List &L) { // memindahkan kursor head ke kiri
    if (L.cursor.head != nullptr){
        L.cursor.head = L.cursor.head->prev;
    }
}

void moveLeftCursorTail(List &L) { // memindahkan kursor tail ke kiri
    if (L.cursor.tail != nullptr){
        L.cursor.tail = L.cursor.tail->prev;
    }
}

void moveUpCursor(List &L) { // memindahkan kursor ke atas
    int jum = 0;
    adr p = L.cursor.head;
    if (p != nullptr){
        while ( p->prev != nullptr) { // mundur sampai ketemu null atau enter
            if (p->prev->info == 13) {
                break;
            }
            p = p->prev;
            jum += 1;
        }
        p = p->prev;
    }
    int i=1;
    if (p != nullptr) {
        p = p->prev;
        while (p->prev != nullptr) { // mundur lagi sampai ketemu null atau enter
            if (p->prev->info == 13) {
                break;
            }
            p = p->prev;
        }
        i=1;
        if (jum == 0 && p == L.head) {
            L.cursor.head = nullptr;
        } else {
            while (i <= jum && p->next != nullptr && p->next->info != 13) { // maju sebanya jarak kursor ke enter
                p = p->next;
                i++;
            }
            L.cursor.head = p;
        }
    }
    L.cursor.tail = L.cursor.head;
}

void moveUpCursorBlock(List &L, bool &up, bool &down) { // memindahkan kursor ke atas ketika memblok
    int jum = 0;
    adr p;

    if (L.cursor.head == L.cursor.tail) { // inisialisasi up ketika kursor tidak sedang memblok
        up = true;
        down = false;
    }

    if (up) { // ketika sedenga memblok ke atas
        p = L.cursor.head;
    } else if (down) { // ketika sedang memblok ke bawah
        p = L.cursor.tail;
    } else {
        p = L.cursor.head;
    }

    if (p != nullptr){ // sama seperti moveUpCursor
        while ( p->prev != nullptr) {
            if (p->prev->info == 13) {
                break;
            }
            p = p->prev;
            jum += 1;
        }
        p = p->prev;
    }
    int i=1;
    if (p != nullptr) {
        p = p->prev;
        while (p->prev != nullptr) {
            if (p->prev->info == 13) {
                break;
            }
            p = p->prev;
        }
        i=1;
        if (jum == 0 && p == L.head) {
            L.cursor.head = nullptr;
        } else {
            while (i <= jum && p->next != nullptr && p->next->info != 13) {
                p = p->next;
                i++;
            }


            if (up) { // sesuaikan dengan pergerakan blok kursor
                L.cursor.head = p;
            }else if (down) {
                L.cursor.tail = p;
            }
        }
    }
}

void moveDownCursor(List &L) { // memindahkan kursor ke bawah
    int jum = 0;
    adr p = L.cursor.head;
    while (p != nullptr) { // mundur untuk menghitung jarak cursor dari enter / null
        if (p->info == 13){
            break;
        }
        p = p->prev;
        jum += 1;
    }
    p = L.cursor.head; // kembalikan pointer ke cursor
    while (p != nullptr) { // maju sampe enter / null selanjutnya
        if (p->info == 13) {
            break;
        }
        p = p->next;
    }
    int i = 2;
    if (p!= nullptr) {
        p = p ->next;
        while (p->info != 13 && p ->next != nullptr && i <= jum) { // maju sebanyak jarak kursor ke enter/null
            p = p->next;
            i++;
        }
        if (p -> info == 13) {
            p = p->prev;
        }
        L.cursor.head = p;
    }
    L.cursor.tail = L.cursor.head;
}

void moveDownCursorBlock(List &L, bool &up, bool &down) { // memindahkan kursor ke bawah ketika memblok
    int jum = 0;
    adr p;

     if (L.cursor.head == L.cursor.tail) { // inisialisi down ketika kursor tidak memblok
        down = true;
        up = false;
    }

    if (up) { // pemilihan pointer sesuai dengan kondisi up / down
        p = L.cursor.head;
    } else if (down) {
        p = L.cursor.tail;
    } else {
        p = L.cursor.tail;
    }

    while (p != nullptr) {
        if (p->info == 13){
            break;
        }
        p = p->prev;
        jum += 1;
    }
    if (up) {
        p = L.cursor.head;
    } else if (down) {
        p = L.cursor.tail;
    }
    while (p != nullptr) {
        if (p->info == 13) {
            break;
        }
        p = p->next;
    }
    int i = 2;
    if (p!= nullptr) {
        p = p ->next;
        while (p->info != 13 && p ->next != nullptr && i <= jum) {
            p = p->next;
            i++;
        }
        if (p -> info == 13) {
            p = p->prev;
        }

        if (up) {
            L.cursor.head = p;
        } else if (down) {
            L.cursor.tail = p;
        }
    }
}
