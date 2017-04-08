#include <Windows.h>
#include "TXLib.h"
#include <iostream>
#include <locale>

struct Button
{
    RECT area;
    const char* text;
    void (*onClick)();
};

void drawButton(Button* button)
{
    txSetColour(TX_RED);
    txRectangle(button->area.left, button->area.top, button->area.right, button->area.bottom);
    txDrawText(button->area.left, button->area.top, button->area.right, button->area.bottom, button->text);
}

void butylki()
{
    WinExec("butylki.exe",SW_SHOW);
}
void paint()
{
    //KOLICHESTVO_PUL = KOLICHESTVO_PUL + 1;
    WinExec("C:\\Windows\\System32\\mspaint.exe",SW_SHOW);
}
void game()
{
    WinExec("D:\\zandronum.exe -connect 192.168.11.68:10666 -file D:\\brutalv20b.pk3 -iwad D:\\doom2.wad",SW_SHOW);
}

int main()
{
    txCreateWindow(1000, 600);

    Button buttons[3];
    buttons[0] = {{ 330, 100, 660, 150 }, "sds", butylki};
    buttons[1] = {{ 330, 200, 660, 250 }, "345", paint};
    buttons[2] = {{ 330, 300, 660, 350 }, "346346", game};

    while (1)
    {
        for(int i = 0; i < 3; i++) {
            drawButton(&buttons[i]);
            if (In (txMousePos(), buttons[i].area) and txMouseButtons() & 1) {
                buttons[i].onClick();
            }
        }
    }
    return 0;
}
