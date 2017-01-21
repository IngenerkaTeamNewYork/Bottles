#include "D:\Инженерка\TX\TXLib.h"

int main()
{
    txCreateWindow(600, 400);

    int x = 200;
    int y = 300;

    for (int i = 0; i < 500; i++) {
        //txBitBlt (txDC(), 0, 0, 800, 600, 0, 0);

        if (GetAsyncKeyState(VK_LEFT)) {
            x = x - 5;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            x = x + 5;
        }
        if (GetAsyncKeyState(VK_UP)) {
            y = y - 5;
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            y = y + 5;
        }


    txLine((x+ 3*i), y-200, x+100, y+100);
    //txDeleteDC (fon);
    return 0;
}
