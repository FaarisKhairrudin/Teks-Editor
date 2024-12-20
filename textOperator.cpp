#include <iostream>
#include "header.h"
#include <string>

using namespace std;

void saveState(Stack &S, List &L);

void addText(List &L, char x, Stack &undoS, Stack &redoS) { // fungsi untuk menambahkan text ke list beserta operasi kursor


    createStack(redoS); // reset redo

    if (x == ' ') {
        saveState(undoS, L); // push ke stack undo (save)
    }

    adr p = createElement(x);

    if (L.cursor.head != L.cursor.tail) { // ketika posisi kursor sedang memblok
        deleteText(L,undoS);
    }
    if (L.cursor.head == nullptr) { // menambah elmList ke posisi kursor
        insertFirst(L, p);
        L.cursor.head = L.head;
        L.cursor.tail = L.head;
    } else if (L.cursor.head == L.tail) {
        insertLast(L, p);
        L.cursor.head = p;
        L.cursor.tail = p;
    } else {
        insertAfter(L, L.cursor.head, p);
        L.cursor.head = p;
        L.cursor.tail = p;
    }
}

void addTextLoad(List &L, char x) { // fungsi untuk menambahkan karakter ke list tanpa operasi undo dan redo
    adr p = createElement(x);

    if (L.cursor.head == nullptr) {
        insertFirst(L, p);
        L.cursor.head = L.head;
        L.cursor.tail = L.head;
    } else if (L.cursor.head == L.tail) {
        insertLast(L, p);
        L.cursor.head = p;
        L.cursor.tail = p;
    } else {
        insertAfter(L, L.cursor.head, p);
        L.cursor.head = p;
        L.cursor.tail = p;
    }
}

void deleteText(List &L, Stack &undoS) { // fungsi untuk menghapus char yang ditunjuk oleh kursor
    int jum = 0;
    if (L.cursor.head != nullptr && L.cursor.head == L.cursor.tail) { // kondisi ketika kursor tidak memblok
        if (L.cursor.head->info == ' ' || jum == 5) {
            saveState(undoS, L); //kondisi kursor->info adalah spasi, maka di push ke undo
            jum = 0;
        }
        jum++;
        adr p;
        if (L.cursor.head == L.head) {
            deleteFirst(L, p);
            L.cursor.head = nullptr;
            L.cursor.tail = nullptr;
        } else if (L.cursor.head == L.tail) {
            deleteLast(L, p);
            L.cursor.head = L.tail;
            L.cursor.tail = L.tail;
        } else {
            adr prec = L.cursor.head->prev;
            deleteAfter(L, prec, p);
            L.cursor.head = prec;
            L.cursor.tail = prec;
        }

    } else if (L.cursor.head != L.cursor.tail) { // kondisi ketika kursor sedang memblok beberapa character
        saveState(undoS, L);
        if (L.cursor.head != nullptr) {
            L.cursor.head->next->prev = nullptr;
            L.cursor.head ->next = L.cursor.tail -> next;
            if (L.cursor.tail->next != nullptr) {
                L.cursor.tail->next ->prev = L.cursor.head;
            }
            L.cursor.tail->next = nullptr;
        } else if (L.cursor.head == nullptr && L.cursor.tail == L.tail) {
            L.head = nullptr;
            L.tail = nullptr;
            L.cursor.head = nullptr;
            L.cursor.tail = nullptr;
        } else {
            if (L.cursor.tail->next != nullptr) {
                L.head = L.cursor.tail->next;
                L.cursor.tail->next->prev = nullptr;
            }
        }
        L.cursor.tail = L.cursor.head;
    }
}

void printTextWithCursor(List L) { // fungsi untuk mencetak isi dari List beserta kursor nya
    adr p = L.head;
    if (L.cursor.head == nullptr && L.cursor.head != L.cursor.tail){ // kursor dicetak di setelah pointer kursor
        cout << "|";
        setTextColor(30);
    } else if (L.cursor.head == nullptr) {
        cout << "|";
    }
    while (p != nullptr) {
        if (p->info == 13) {
            cout << endl;
        } else {
            cout << p->info;
        }
        if (p == L.cursor.head && L.cursor.head == L.cursor.tail) {
            cout << "|";
        } else if (p == L.cursor.head) {
            cout << "|";
            setTextColor(30);
        }
        if (L.cursor.head != L.cursor.tail && L.cursor.tail == p) {
            setTextColor(7);
            cout << "|";
        }
        p = p->next;
    }
    setTextColor(7);
    cout << endl;
}

// ============ UNDO & REDO ==========================================
void saveState(Stack &S, List &L) { // Menyimpan kondisi List ke Stack, Konsep nya sama seperti push stack
    if (!isFullStack(S)) {
        createList(S.info[S.top]);
        adr p = L.head;
        while (p != nullptr) {
            adr newElement = createElement(p->info);
            if (p == L.cursor.head) { // save cursor head
                S.info[S.top].cursor.head= newElement;
            }
            if (p == L.cursor.tail) { // save cursor tail
                S.info[S.top].cursor.tail = newElement;
            }
            insertLast(S.info[S.top], newElement);
            p = p->next;
        }
        S.top++;
    }
}

void loadState(Stack &S, List &L) { // Mengembalikan kondisi List dari Stack, konsepnya seperti pop stack
    if (!isEmptyStack(S)) {
        S.top--;
        createList(L);
        List snapshot = S.info[S.top];
        adr p = snapshot.head;
        while (p != nullptr) {
            adr newElement = createElement(p->info); // membuat element baru dengan info yang sama
            if (p == S.info[S.top].cursor.head) { // load cursor head
                L.cursor.head = newElement;
            }
            if (p == S.info[S.top].cursor.tail) { // load cursor head
                L.cursor.tail = newElement;
            }
            insertLast(L, newElement);
            p = p->next;
        }
    }
}

void undo(List &L, Stack &undoS, Stack &redoS) { // fungsi untuk pengimplementasian fitur undo
    if (undoS.top > 0) {
        saveState(redoS, L);
        loadState(undoS, L);
    } else {
        cout << "Tidak ada langkah yang bisa di-undo.\n";
    }
}

void redo(List &L, Stack &undoS, Stack &redoS) { // fungsi untuk pengimplementasian fitur undo
    if (redoS.top > 0) {
        saveState(undoS, L);
        loadState(redoS, L);
    } else {
        cout << "Tidak ada langkah yang bisa di-redo.\n";
    }
}

// =================== FIND & Replace ===============================
DLL stringToDll(string x) {               // merubah string menjadi multi linked list
    DLL hasil;
    createDll(hasil);
    for (int i = 0; x[i] != '\0'; i++) {
        adr p = createElement(x[i]);
        insertLastDll(hasil, p);
    }
    return hasil;
}

bool isEqual(adr p, adr find) {       // mengecek apakah 2 linkelist memiliki info yang sama persis
    adr L = p;
    if (L != nullptr && find != nullptr) {
        while (L->info == find -> info && find->next != nullptr && L-> next != nullptr) {
            L = L->next;
            find = find->next;
        }

        if (find->next == nullptr) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

int lenList(adr L) { // mengembalikan banyak karakter dari linked list
    int jum = 0;
    while (L != nullptr) {
        L = L->next;
        jum += 1;
    }
    return jum;
}

void findAndReplace(List &L, string find, string replace) { // fungsi untuk pengimplementasian fitur find and replace
    DLL findList = stringToDll(find);       // mengubah string menjadi list
    DLL replaceList = stringToDll(replace);
    int len = lenList(findList.head);
    bool found = false;

    adr p = L.head;
    while (p != nullptr) {
        if (p->info == findList.head->info) { // mencari karakter yang sama dengan karakter awal dari find
            found = isEqual(p, findList.head); // cek apakah karakter sisanya sama semua
            if (found) {                        // mengganti find pada list dengan replace
                replaceList.head-> prev = p->prev;
                if (p->prev != nullptr) {
                    p->prev ->next = replaceList.head;
                } else {
                    L.head = replaceList.head;
                }
                adr q = p;

                for (int i = 1; i <= len; i++) {
                    if (q == L.cursor.head) {
                        L.cursor.head = replaceList.tail;
                    }
                    if ( i != len) {
                        q = q->next;
                    }
                }
                replaceList.tail->next = q ->next;
                if (q->next != nullptr) {
                    q->next->prev = replaceList.tail;
                }
                p->prev = nullptr;
                q->next = nullptr;
                break;
            }
        }
        p = p->next;
    }
}

// ==================== Copy and Paste ======================

void copyList(Cursor l1, Cursor &l2) { // fungsi untuk menyalin isi char dari l1 ke l2
    createDll(l2);
    adr p = l1.head;
    while (p != nullptr) {
        adr newElement = createElement(p->info);
        insertLastDll(l2, newElement);
        if (p == l1.tail) {
            break;
        }
        p = p->next;

    }
}

void copyBlock(List &L) {  // fungsi untuk mensalin blok teks yang di block oleh cursor
    if (L.cursor.head != L.cursor.tail) {
        if (L.cursor.head != nullptr) {
            L.copyTxt.head = L.cursor.head->next;
        } else {
            L.copyTxt.head = L.head;
        }

        if (L.cursor.tail != nullptr) {
            L.copyTxt.tail = L.cursor.tail;
        }
    }
}

void blockAll(List &L) { // fungsi untuk memblok seluruh karakter di list
    L.cursor.head = nullptr;
    L.cursor.tail = L.tail;
}

void pasteBlock(List &L) {  // fungsi untuk menempel teks yang telah di salin ke list
    if (L.copyTxt.head != nullptr && L.copyTxt.tail != nullptr){ //
        DLL paste;
        copyList(L.copyTxt, paste);
        if (L.cursor.head == L.cursor.tail) {
            if (L.cursor.head != nullptr) {
                if (L.cursor.head ->next != nullptr) {
                    L.cursor.head ->next ->prev = paste.tail;
                }
                paste.tail->next = L.cursor.head->next;
                L.cursor.head->next = paste.head;
                paste.head->prev = L.cursor.head;
            } else {
                paste.tail ->next = L.head;
                L.head = paste.head;
            }
        } else {
            paste.head->prev = L.cursor.head;
            if (L.cursor.head != nullptr) {
                L.cursor.head ->next = paste.head;
            } else {
                L.head = paste.head;
            }
            paste.tail->next = L.cursor.tail->next;
            if (L.cursor.tail->next != nullptr) {
                L.cursor.tail->next->prev = paste.tail;
            }
        }
        L.cursor.head = paste.tail;
        L.cursor.tail = L.cursor.head;
    }
}


