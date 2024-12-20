#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <conio.h>
#include "header.h"

using namespace std;

void hideCursor() { // untuk menghilangkan kursor yang kedap kedip dan mengatur ukuran window
    system("mode con: cols=90 lines=33");
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void setWindow() { // untuk mengatur ukuran font cmd
    // Mendapatkan handle ke konsol
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Mengubah ukuran font menjadi lebih besar
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

    // Menentukan ukuran font
    cfi.dwFontSize.X = 24;  // Lebar font
    cfi.dwFontSize.Y = 24;  // Tinggi font
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

}

void setTextColor(int color) { // fungsi untuk merubah warna teks di cmd
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void checkKeyboard(){ // fungsi untuk mengetahui ascii (input) dari keyboard, untuk mengecek saja
    char ch;
    while (true) {
        ch = getch();
        cout << "Anda menekan: " << int(ch) << endl;
        cout << "Anda menekan: " << ch << endl;
    }
}

void menu(List L, bool shortcut){ // fungsi untuk menampilkan menu utama
    setTextColor(12);
    cout << " Esc    : Exit                                                         f1 : Show Features";
    setTextColor(14);
    cout <<  R"(
                _____ _______  _______   _____ ____ ___ _____ ___  ____
               |_   _| ____\ \/ /_   _| | ____|  _ \_ _|_   _/ _ \|  _ \
                 | | |  _|  \  /  | |   |  _| | | | | |  | || | | | |_) |
                 | | | |___ /  \  | |   | |___| |_| | |  | || |_| |  _ <
                 |_| |_____/_/\_\ |_|   |_____|____/___| |_| \___/|_| \_\
    )"<< endl;
    setTextColor(6);
    cout <<"                        - p  e  n  y  u     n  g  a  m  b  e  k -" << endl;
    if (shortcut) {
        cout << "                                           ===             "<< endl;
        cout << "                \x18 : Cursor up                        \x1A : cursor right"<< endl;
        cout << "                \x19 : cursor down                      \x1B5 : cursor left"<< endl;
        cout << "                ctrl + r : Find & Replace           ctrl + \x1D : Block Text" << endl;
        cout << "                ctrl + c : Copy Text                ctrl + v : Paste Text" << endl;
        cout << "                ctrl + A : Block All                crtl + Z : undo" << endl;
        cout << "                ctrl + Y : Redo                        " << endl << endl;
    } else {
        cout << endl;
    }
    setTextColor(7);
    printTextWithCursor(L);
    cout<< endl;

}
