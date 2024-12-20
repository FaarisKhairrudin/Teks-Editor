#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <string>

using namespace std;

typedef char infotype;
typedef struct elmList *adr;

struct elmList {
    infotype info;
    adr next;
    adr prev;
};

struct Cursor{
    adr head;
    adr tail;
};

typedef struct Cursor DLL;

struct List {
    adr head;
    adr tail;
    Cursor cursor;
    Cursor copyTxt;
};

typedef struct List Text;

struct Stack {
    List info[1000];
    int top;
};

// basic
adr createElement(infotype data);
void createList(List &L);
void createDll(DLL &L);
void createStack(Stack &S);
bool isEmptyStack(Stack &S);
bool isFullStack(Stack &S);
void createCursor(Cursor &C);
void insertFirst(List &L, adr p);
void insertLast(List &L, adr p);
void insertLastDll(DLL &L, adr p);
void insertAfter(List &L, adr prec, adr p) ;
void deleteFirst(List &L, adr &p);
void deleteLast(List &L, adr &p) ;
void deleteAfter(List &L, adr prec, adr &p);
void printForward(List L);
void printBackward(List L);

// textOperator
void addText(List &L, char x, Stack &undoS,Stack &redoS);
void addTextLoad(List &L, char x);
void deleteText(List &L, Stack &undoS);
void printTextWithCursor(List L);
void undo(List &L, Stack &undoS, Stack &redoS);
void redo(List &L, Stack &undoS, Stack &redoS);
void saveState(Stack &S, List &L);
void loadState(Stack &S, List &L);
DLL stringToDll(string x);
bool isEqual(adr L, adr find);
int lenList(adr L);
void findAndReplace(List &L, string find, string replace);
void copyList(Cursor l1, Cursor &l2);
void copyBlock(List &L);
void blockAll(List &L);
void pasteBlock(List &L);


// cursorOperator
void moveRightCursor(List &L);
void moveRightCursorHead(List &L);
void moveRightCursorTail(List &L);
void moveLeftCursor(List &L);
void moveLeftCursorHead(List &L);
void moveLeftCursorTail(List &L);
void moveUpCursor(List &L);
void moveUpCursorBlock(List &L, bool &up, bool &down);
void moveDownCursor(List &L);
void moveDownCursorBlock(List &L, bool &up, bool &down);
bool isRightCursor(adr c1, adr c2);
bool isLeftCursor(adr c1, adr c2);

// display
void hideCursor();
void setTextColor(int color);
void checkKeyboard();
void menu(List L, bool shortcut);
void setWindow();

#endif // HEADER_H_INCLUDED
