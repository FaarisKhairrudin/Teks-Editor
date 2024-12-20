#include <iostream>
#include "header.h"

using namespace std;

adr createElement(infotype data){
    adr p = new elmList;
    p->info = data;
    p->next = nullptr;
    p->prev = nullptr;

    return p;
}

void createDll(DLL &L) {
    L.head = nullptr;
    L.tail = nullptr;
}

void createList(List &L) {
//    adr p = createElement(13);
    L.head = nullptr;
    L.tail = nullptr;
    L.cursor.head = nullptr;
    L.cursor.tail = nullptr;
    L.copyTxt.head = nullptr;
    L.copyTxt.tail = nullptr;
}

void createStack(Stack &S) {
    S.top = 0;
}

void createCursor(Cursor &C) {
    C.head = nullptr;
    C.tail = nullptr;
}

bool isEmptyStack(Stack &S) {
    return S.top == 0;
}

bool isFullStack(Stack &S) {
    return S.top == 1000;
}

void insertFirst(List &L, adr p) {
    if (L.head != nullptr) {
        p->next = L.head;
        L.head->prev = p;
        L.head = p;
    } else {
        L.head = p;
        L.tail = p;
    }
}

void insertLastDll(DLL &L, adr p) {
    if (L.head != nullptr) {
        p->prev = L.tail;
        L.tail->next = p;
        L.tail = p;
    } else {
        L.head = p;
        L.tail = p;
    }
}

void insertLast(List &L, adr p) {
    if (L.head != nullptr) {
        p->prev = L.tail;
        L.tail->next = p;
        L.tail = p;
    } else {
        L.head = p;
        L.tail = p;
    }
}

void insertAfter(List &L, adr prec, adr p) {
    p->next = prec->next;
    p->prev = prec;
    prec->next = p;
    if (p->next != nullptr) {
        p->next->prev = p;
    }
}

void deleteFirst(List &L, adr &p) {
    if (L.head != L.tail) {
        p = L.head;
        L.head = p->next;
        L.head->prev = nullptr;
        p->next = nullptr;
    } else {
        L.head = nullptr;
        L.tail = nullptr;
    }
}

void deleteLast(List &L, adr &p) {
    if (L.head != L.tail) {
        p = L.tail;
        L.tail = p->prev;
        L.tail->next = nullptr;
        p->prev = nullptr;
    } else {
        L.head = nullptr;
        L.tail = nullptr;
    }
}

void deleteAfter(List &L, adr prec, adr &p) {
    p = prec->next;
    if (prec->next != nullptr) {
        prec ->next = p->next;
        if (p->next != nullptr) {
            p->next->prev = p->prev;
        }
        p->next = nullptr;
        p->prev = nullptr;
    }
}

void printForward(List L) {
    adr q= L.head;
    while (q != nullptr) {
        cout << q->info;
        q = q-> next;
    }
    cout << endl;
}

void printBackward(List L) {
    adr q= L.tail;
    while (q != nullptr) {
        cout << q->info << " " ;
        q = q-> prev;
    }
    cout << endl;
}
