#include "D:\Инженерка\TX\TXLib.h"

struct Bullet
{
    int x;
    int y;
    bool isVisible;
};

struct Butylka
{
    int x;
    int y;
    int hp=10;
};
/*
vrag.hp = vrag.hp - 1;
Butylka vrag = {500, 500, 10};
*/
struct Rushbottles
{
    int rbx;
    int rby;
};
/*
void hp
{

}

void hpvraga
{

}
*/

void drawBullet(Bullet *bullet)
{
    if (bullet->isVisible) {
         txSetFillColour(TX_YELLOW);
        txCircle(bullet->x, bullet->y, 3);
        bullet->y = bullet->y + 9;
    }
}

void drawBulletVraga(Bullet *bullet)
{
    if(bullet->isVisible) {
txCircle(bullet->x, bullet->y, 3);
bullet->y = bullet->y - 9;
    }
}


void ikran (int *x, int *y, int minPoY, int maxPoY)
{
    if (*x > txGetExtentX()) {
        *x = txGetExtentX();
    }
    if (*y > maxPoY - 40) {
        *y = maxPoY - 40;
    }

    if (*x < 20) {
        *x = 20;
    }
    if (*y < minPoY) {
        *y = minPoY;
    }

}
void ograda(int ox, int oy)
{
    txLine(ox,oy,ox+998,oy);
}

void DNN (int dx, int dy)
{
    txSetColour(TX_RED);
    txLine(dx-13,dy+30,    dx-13, dy+40);
    txLine(dx-6, dy+40, dx-13, dy+40);
    txLine(dx-6, dy+40, dx-6, dy+30);

    txLine(dx-20, dy+30,dx-20, dy);
    txLine(dx, dy,      dx-20, dy);
    txLine(dx, dy,      dx, dy+30);
    txLine(dx-20,dy+30, dx, dy+30);


    txSetColour(RGB(random(255),random(255),random(255)));
    txSelectFont ("Times New Roman", 10) ;
    txTextOut (dx-15, dy+15, "DN");
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

int main()
{
    txDisableAutoPause();
    const int objom_magazina = 8;
    Bullet bulletButylki[objom_magazina];// 8 пуль

    //Делаем все пули невидимыми
    for (int i = 0; i < objom_magazina; i++) {
        bulletButylki[i] = {0, 0, false};
    }

    Bullet bulletVraga[objom_magazina];// 8 пуль

    //Делаем все пули невидимыми
    for (int i = 0; i < objom_magazina; i++) {
        bulletVraga[i] = {0, 0, false};
    }

    int countBullets = 8;
    int vragX = 500;
    int vragY = 560;
    //int ox = 2;
    //int oy = 300;
    int dx = 500;
    int dy = 20;
    int poryadkovyiNomerPuli = 0;
    int t = 0;

    txCreateWindow(1000, 600);

    txSetColor(TX_RED, 4);
    while (1)
    {
        txClear();

        if (GetAsyncKeyState(VK_LEFT))
        {
            dx = dx - 10;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            dx = dx + 10;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            dy = dy - 10;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            dy = dy + 10;
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

        ikran (&dx, &dy, 0, 300);
        ikran (&vragX, &vragY, 300+10, 600);

        if (GetAsyncKeyState(VK_SPACE) && (countBullets > 0)) {
            bulletButylki[poryadkovyiNomerPuli % objom_magazina] = {dx-10, dy+39, true};
            poryadkovyiNomerPuli++;
            countBullets--;
        }

        if (GetAsyncKeyState(VK_NUMPAD0) && (countBullets > 0)) {
            bulletVraga[poryadkovyiNomerPuli % objom_magazina] = {vragX-10, vragY-19, true};
            poryadkovyiNomerPuli++;
            countBullets--;
        }

        ograda (2, 300);
        DNN (dx, dy);
        ZloyDN (vragX, vragY);

        for (int i = 0; i < objom_magazina; i++) {
            drawBullet(&bulletButylki[i]);
            drawBulletVraga(&bulletVraga[i]);

            if (abs(bulletButylki[i].x - (vragX + 20)) + abs(bulletButylki[i].y - vragY) < 20) {//попадание {
                //lifes = lifes - 1;//жизни (как с кл-ом пуль)
            }

        }

        if (t % 300 == 0) {
            countBullets++;
        }


        txSleep(10);
        t = t + 10;
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
    }
    return 0;
}




