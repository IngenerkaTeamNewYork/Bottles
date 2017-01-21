#include "D:\Инженерка\TX\TXLib.h"

const int objom_magazina = 10;

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
    int hp;
    int count_bullets;
    int poryadkovyiNomerPuli;
    COLORREF color;
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

void DNN (int dx, int dy) // but1
{/*
    if (txGetPixel(dx, dy) == Butylka->but1->color) {
        Butylka->but
    }
    */
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

void upravlenieVragom(int* vragX, int* vragY)
{
    if (GetAsyncKeyState(VK_NUMPAD4))
    {
        *vragX = *vragX - 10;
    }
    if (GetAsyncKeyState(VK_NUMPAD6))
    {
        *vragX = *vragX + 10;
    }
    if (GetAsyncKeyState(VK_NUMPAD8))
    {
        *vragY = *vragY - 10;
    }
    if (GetAsyncKeyState(VK_NUMPAD5))
    {
        *vragY = *vragY + 10;
    }
}

void upravleniePervoiButylkoi(int* dx, int* dy)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        *dx = *dx - 10;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        *dx = *dx + 10;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        *dy = *dy - 10;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        *dy = *dy + 10;
    }
}



int main()
{
    txDisableAutoPause();
                           //   x   y   жизней   пуль               номер пули                цвет
    Butylka pervayaButylka = {500,  20,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};
    Butylka vrag =           {500, 560,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};

    Bullet bulletButylki[pervayaButylka.count_bullets];             // 8 пуль
    for (int i = 0; i < pervayaButylka.count_bullets; i++) {        //Делаем все пули невидимыми
        bulletButylki[i] = {0, 0, false};
    }

    Bullet bulletVraga[vrag.count_bullets];             // 8 пуль
    for (int i = 0; i < vrag.count_bullets; i++) {      //Делаем все пули невидимыми
        bulletVraga[i] = {0, 0, false};
    }
    int t = 0;

    txCreateWindow(1000, 600);

    txSetColor(TX_RED, 4);

    //menu


    while (1)
    {
        txClear();
        ograda (2, 300);

        //Указатель (*) нужен для того, чтобы менять значение переменной внутри функции
        upravlenieVragom        (&vrag.x,           &vrag.y);
        upravleniePervoiButylkoi(&pervayaButylka.x, &pervayaButylka.y);

        ikran (&pervayaButylka.x, &pervayaButylka.y, 0,   300);
        ikran (&vrag.x,           &vrag.y,           310, 600);

        if (GetAsyncKeyState(VK_SPACE) && (pervayaButylka.count_bullets > 0)) {
            bulletButylki[pervayaButylka.poryadkovyiNomerPuli % objom_magazina] = {pervayaButylka.x-10, pervayaButylka.y+39, true};
            pervayaButylka.poryadkovyiNomerPuli = pervayaButylka.poryadkovyiNomerPuli + 1;
            pervayaButylka.count_bullets = pervayaButylka.count_bullets - 1;
        }

        if (GetAsyncKeyState(VK_NUMPAD0) && (vrag.count_bullets > 0)) {
            bulletVraga[vrag.poryadkovyiNomerPuli % objom_magazina] = {vrag.x-10, vrag.y-19, true};
            vrag.poryadkovyiNomerPuli = vrag.poryadkovyiNomerPuli + 1;
            vrag.count_bullets = vrag.count_bullets - 1;
        }

        if (pervayaButylka.hp > 0) {
            DNN    (pervayaButylka.x, pervayaButylka.y);
        }
        if (vrag.hp > 0) {
            ZloyDN  (vrag.x, vrag.y);
        }

        for (int i = 0; i < objom_magazina; i++) {
            drawBullet(&bulletButylki[i]);
            drawBulletVraga(&bulletVraga[i]);

            if (pervayaButylka.hp > 0 &&
                bulletVraga[i].x <= pervayaButylka.x &&
                bulletVraga[i].x >= pervayaButylka.x - 20 &&
                bulletVraga[i].y <= pervayaButylka.y + 30 &&
                bulletVraga[i].y >= pervayaButylka.y) {//попадание {
                pervayaButylka.hp = pervayaButylka.hp - 1;//жизни (как с кл-ом пуль)
                txSleep(10);
            }
            if (abs(bulletButylki[i].x - (vrag.x + 20)) + abs(bulletButylki[i].y - vrag.y) < 20) {//попадание {
                vrag.hp = vrag.hp - 1;//жизни (как с кл-ом пуль)
                txSleep(10);
            }
        }

        if (t % 300 == 0) {
            pervayaButylka.count_bullets++;
            vrag.count_bullets++;
        }



        if (pervayaButylka.hp <= 0) {
            if (txMessageBox ("Начать заново?", "Прочти меня", MB_YESNO) == IDYES)
            {
                pervayaButylka = {500,  20,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};
                vrag =           {500, 560,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};

                for (int i = 0; i < pervayaButylka.count_bullets; i++) {        //Делаем все пули невидимыми
                    bulletButylki[i] = {0, 0, false};
                }

                for (int i = 0; i < vrag.count_bullets; i++) {      //Делаем все пули невидимыми
                    bulletVraga[i] = {0, 0, false};
                }
            }
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
