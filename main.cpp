#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <string>
#include "header.h"

using namespace std;

int main()
{
    setWindow(); // untuk set ukuran window
    hideCursor(); // untuk menghilangkan kursor
    string find,replace;
    Stack undoStack, redoStack;
    Text text;
    char temp =0 ;
    char pilihan = 0;
    bool shortcut = false, left = false, right = false, up = false, down = false;
    int jum = 0;

    createList(text);
    createStack(undoStack);
    createStack(redoStack);

    saveState(undoStack,text);

    while (pilihan != 27) { // 27 = escape
        setTextColor(8);
        cout << int(temp) << " " << int(pilihan) << endl;
        setTextColor(8);
        menu(text, shortcut);
        temp = pilihan;
        pilihan = getch();

        if (pilihan == 8) { // backspace
            deleteText(text, undoStack);
        } else if (temp == -32 && pilihan == 75) { // arrow left
            moveLeftCursor(text);
            right = false;
            left = false;

        } else if (temp == -32 && pilihan == 77) { // arrow right
            moveRightCursor(text);
            right = false;
            left = false;
        } else if (temp == -32 && pilihan == 72) { // arrow up
            up = false;
            moveUpCursor(text);
            right = false;
            left = false;

        } else if (temp == -32 && pilihan == 80) { // arrow down
            down = false;
            moveDownCursor(text);
            right = false;
            left = false;

        } else if (temp == -32 && pilihan == 115) { // ctrl+arrow left
            if (text.cursor.head == text.cursor.tail) {
                moveLeftCursorHead(text);
                right=false;
                left = true;
                down = false;
                up = true;
            } else if (right) {
                moveLeftCursorTail(text);
            } else if (left){
                moveLeftCursorHead(text);
            }

        } else if (temp == -32 && pilihan == 116) { // ctrl+arrow right
            if (text.cursor.head == text.cursor.tail) {
                moveRightCursorTail(text);
                left = false;
                right = true;
                down = true;
                up = false;
            } else if (left) {
                moveRightCursorHead(text);
            } else if (right){
                moveRightCursorTail(text);
            }


        } else if (temp == -32 && pilihan == -115) { // ctrl+arrow up
            moveUpCursorBlock(text,up,down);
            left = true;
            right = false;

        } else if (temp == -32 && pilihan == -111) { // ctrl+arrow down
            moveDownCursorBlock(text,up,down);
            right = true;
            left = false;

        } else if (pilihan == 1) { // ctrl+ a
            blockAll(text);
        } else if (pilihan == 18) { // ctrl + r
            saveState(undoStack,text);
            cout << "find: ";
            getline(cin,find);
            cout << "replace: ";
            getline(cin, replace);
            findAndReplace(text, find,replace);

        } else if (pilihan == 3) { // ctrl + c
            copyBlock(text);
        } else if (pilihan == 22) { // ctrl + v
            saveState(undoStack, text);
            pasteBlock(text);
        } else if (temp == 0 && pilihan == 59) { // f1
            if (shortcut) {
                shortcut = false;
            } else {
                shortcut = true;
            }

        } else if (pilihan == -32) {

        } else if (pilihan == 26) { // ctrl + z
            undo(text, undoStack, redoStack);
        } else if (pilihan == 25) {  // ctrl + y
            redo(text,undoStack,redoStack);
        } else {
            if (pilihan != ' ') {
                jum++;
            }
            if (jum == 10) { // kalau sudah 10 kali mengetik tanpa ada spasi, di saveState.
                saveState(undoStack, text);
                jum = 0;
            } else if (pilihan == ' ') {
                jum = 0;
            }
            addText(text, pilihan, undoStack, redoStack);

        }
        system("CLS");
    }
    return 0;
}


