#include <Windows.h>
#include "TXLib.h"
#include <iostream>
#include <locale>

int main()
{
    txCreateWindow(1000, 600);
    txSetColour(TX_RED);
    txRectangle(330, 100, 660, 150);
    txRectangle(330, 200, 660, 250);
    txRectangle(330, 300, 660, 350);

    RECT area1 = { 330, 100, 660, 150 };
    RECT area2 = { 330, 200, 660, 250 };
    RECT area3 = { 330, 300, 660, 350 };

    while (1)
    {
        if (In (txMousePos(), area1) and txMouseButtons() & 1) {
            WinExec("butylki.exe",SW_SHOW);
        }
        if (In (txMousePos(), area2) and txMouseButtons() & 1) {
            WinExec("C:\\Windows\\System32\\mspaint.exe",SW_SHOW);
        }
        if (In (txMousePos(), area3) and txMouseButtons() & 1) {
            WinExec("C:\\Windows\\System32\\notepad.exe",SW_SHOW);
        }
    }


    return 0;




}




