#include "D:\Инженерка\TX\TXLib.h"

int x = 200;
int y = 300;
int vragX = 200;
int vragY = 300;
int Px = 40;
int Py = 40;

void DNN (int x, int y)
{

    txSetColour(TX_RED);
    txLine(x-20, y+30,x-20, y);
    txLine(x, y,      x-20, y);
    txLine(x, y,      x, y+30);
    txLine(x-20,y+30, x, y+30);
    txLine(x-13,y,    x-13, y-10);
    txLine(x-6, y-10, x-13, y-10);
    txLine(x-6, y-10, x-6, y);
    txSetColour(RGB(random(255),random(255),random(255)));
    txSelectFont ("Times New Roman", 10) ;
    txTextOut (x-15, y+15, "DN");

}

void ZloyDN (int vragX, int vragY)
{
    txLine(vragX-20, vragY+30,vragX-20, vragY);
    txLine(vragX, vragY,      vragX-20, vragY);
    txLine(vragX, vragY,      vragX, vragY+30);
    txLine(vragX-20,vragY+30, vragX, vragY+30);
    txLine(vragX-13,vragY,    vragX-13, vragY-10);
    txLine(vragX-6, vragY-10, vragX-13, vragY-10);
    txLine(vragX-6, vragY-10, vragX-6, vragY);
    txSetColour(RGB(random(255),random(255),random(255)));
    txSelectFont ("Times New Roman", 10) ;
    txTextOut (vragX-15, vragY+15, "DN");

}
void pechen(int Px, int Py)
{
 txSetColour(TX_RED);
 txLine(Px, Py, Px, Py+40);
 txLine(Px, Py, Px+20, Py);
 txLine(Px+20, Py+40, Px+20, Py);
}
int main()
{
    txCreateWindow(1000, 600);

    txSetColor(TX_RED, 4);
    while (1)
    {
        txClear();

        if (GetAsyncKeyState(VK_LEFT))
        {
            x = x - 10;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            x = x + 10;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            y = y - 10;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            y = y + 10;
        }

        if (GetAsyncKeyState(VK_NUMPAD4))
        {
            vragX = vragX - 10;
        }
        if (GetAsyncKeyState(VK_NUMPAD6))
        {
            vragX = vragX + 10;
        }
        if (GetAsyncKeyState(VK_NUMPAD8))
        {
            vragY = vragY - 10;
        }
        if (GetAsyncKeyState(VK_NUMPAD5))
        {
            vragY = vragY + 10;
        }

        pechen (40, 40);
        DNN (x, y);
        ZloyDN (vragX, vragY);
        txSleep(10);
    }
return 0;
}
