#include <Windows.h>
#include "TXLib.h"
#include <iostream>
#include <locale>
#include <fstream>
#include <string>

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

int OBJOM_MAGAZINA = 8;
int MAXIMAL_HP = 8;
int COUNT_BULLETS = 8;
int MAX_COUNT_BULLETS = 8;
int t = 0;
string KOD;

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

void drawBullet(Bullet *bullet)
{
    txSetFillColor(TX_BLUE);
    if (bullet->isVisible) {
        txCircle(bullet->x, bullet->y, 3);
        bullet->y = bullet->y + 9;
    }
}
void drawBulletVraga(Bullet *bullet)
{
    txSetFillColor(TX_RED);
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
void fon()
{
    HDC kartinka = txLoadImage("fon.bmp");

    txBitBlt(txDC(), 0, 0, 1000, 600, kartinka, 0, 0);
    txDeleteDC(kartinka);

}
void ograda(int ox, int oy)
{
    txSetColour(TX_BLACK, 5);
    txLine(ox,oy,ox+998,oy);
}

void DNN (int dx, int dy)
{
    txSetColour(TX_BLUE);
    txLine(dx-13,dy+30,    dx-13, dy+40);
    txLine(dx-6, dy+40, dx-13, dy+40);
    txLine(dx-6, dy+40, dx-6, dy+30);

    txLine(dx-20, dy+30,dx-20, dy);
    txLine(dx, dy,      dx-20, dy);
    txLine(dx, dy,      dx, dy+30);
    txLine(dx-20,dy+30, dx, dy+30);

    txSelectFont ("Times New Roman", 10) ;
    txTextOut (dx-15, dy+15, "DN");
}

void ZloyDN (int vragX, int vragY)
{
    txSetColour(TX_RED);
    txLine(vragX-20, vragY+30,vragX-20, vragY);
    txLine(vragX, vragY,      vragX-20, vragY);
    txLine(vragX, vragY,      vragX, vragY+30);
    txLine(vragX-20,vragY+30, vragX, vragY+30);
    txLine(vragX-13,vragY,    vragX-13, vragY-10);
    txLine(vragX-6, vragY-10, vragX-13, vragY-10);
    txLine(vragX-6, vragY-10, vragX-6, vragY);

    txSelectFont ("Times New Roman", 10) ;
    txTextOut (vragX-15, vragY+15, "DN");
}

void upravlenieVragom(int* vragX, int* vragY)
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        *vragX = *vragX - 10;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        *vragX = *vragX + 10;
    }
    if (GetAsyncKeyState(VK_UP))
    {
        *vragY = *vragY - 10;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        *vragY = *vragY + 10;
    }
}

void upravleniePervoiButylkoi(int* dx, int* dy)
{
    if (GetAsyncKeyState('A'))
    {
        *dx = *dx - 10;
    }
    if (GetAsyncKeyState('D'))
    {
        *dx = *dx + 10;
    }
    if (GetAsyncKeyState('W'))
    {
        *dy = *dy - 10;
    }
    if (GetAsyncKeyState('S'))
    {
        *dy = *dy + 10;
    }
}

bool dead(Butylka* pb, Butylka* vrag)
{
    if (pb->hp <= 0) {
        if (txMessageBox (TEXT("Ты окончательно умер?"), "Соглашайся, второго шанса не будет (но это неточно)", MB_YESNO) == IDNO) {
            *pb   = {500,  20,   10,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
        } else {
            return false;
        }
    }

    if (vrag->hp <= 0) {
        if (txMessageBox (TEXT("Ты окончательно умер?"), "Соглашайся, второго шанса не будет (но это неточно)", MB_YESNO) == IDNO) {
            *vrag = {500, 560,   10,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
        } else {
            return false;
        }
    }

    return true;
}

void ranen(Butylka* pb, Butylka* vrag, Bullet* bulletButylki, Bullet* bulletVraga)
{
     for (int i = 0; i < OBJOM_MAGAZINA; i++)
        {
            drawBullet(&bulletButylki[i]);
            drawBulletVraga(&bulletVraga[i]);


            if (pb->hp > 0 &&
                bulletVraga[i].isVisible &&
                bulletVraga[i].x <= pb->x &&
                bulletVraga[i].x >= pb->x - 20 &&
                bulletVraga[i].y <= pb->y + 30 &&
                bulletVraga[i].y >= pb->y)
            {
                pb->hp = pb->hp -1;
                bulletVraga[i].isVisible = false;
                //txSleep(10);
            }


            if (vrag->hp > 0 &&
                bulletButylki[i].isVisible &&
                bulletButylki[i].x <= vrag->x &&
                bulletButylki[i].x >= vrag->x - 20 &&
                bulletButylki[i].y <= vrag->y + 30 &&
                bulletButylki[i].y >= vrag->y)
            {
                vrag->hp = vrag->hp - 1;
                bulletButylki[i].isVisible = false;
                //txSleep(10);
            }


        }
}
void strelba(Butylka* pb, Butylka* vrag,  Bullet* bulletButylki, Bullet* bulletVraga)
{
    if (GetAsyncKeyState(VK_SPACE) && (pb->count_bullets > 0))
        {
            bulletButylki[pb->poryadkovyiNomerPuli % OBJOM_MAGAZINA] = {pb->x-10, pb->y+39, true};
            pb->poryadkovyiNomerPuli = pb->poryadkovyiNomerPuli + 1;
            pb->count_bullets = pb->count_bullets - 1;
        }

    if (GetAsyncKeyState(VK_NUMPAD0) && (vrag->count_bullets > 0))
        {
            bulletVraga[vrag->poryadkovyiNomerPuli % OBJOM_MAGAZINA] = {vrag->x-10, vrag->y-19, true};
            vrag->poryadkovyiNomerPuli = vrag->poryadkovyiNomerPuli + 1;
            vrag->count_bullets = vrag->count_bullets - 1;
        }

}
void magazin_shkala(Butylka* vrag, Butylka* pb, Bullet* bulletButylki, Bullet* bulletVraga, int t )
{



   if (t % 350 == 0)
        {
            if  (pb->count_bullets < OBJOM_MAGAZINA)
                {
                 pb->count_bullets++;
                }
             if (vrag->count_bullets < OBJOM_MAGAZINA)
                {
                 vrag->count_bullets++;
                }

        }
         t = t + 10;

         strelba( vrag,  pb,  bulletButylki,  bulletVraga);

            txSetFillColor(TX_RED);
            txRectangle(25 , 550 - 12.5*vrag->hp, 75, 550);
            txSetFillColor(TX_BLUE);
            txRectangle(25, 250 - 12.5*pb->hp, 75 , 250);
            txSetFillColor(TX_GREEN);
            txRectangle(925, 550 - 12.5*vrag->count_bullets, 975 , 550);
            txRectangle(925, 250 - 12.5*pb->count_bullets, 975 , 250);
}

void eXit()
{
    if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
}

using namespace std;
int main()
{
    ifstream file("config.txt");

    while(file) {
        string line;
        getline(file, line);

        if (line.substr(0, strlen("OBJOM_MAGAZINA = ")) == "OBJOM_MAGAZINA = ") {
            OBJOM_MAGAZINA= atoi(line.substr(strlen("OBJOM_MAGAZINA = "), 100).c_str());
        }
        if (line.substr(0, strlen("MAXIMAL_HP = ")) == "MAXIMAL_HP = ") {
            MAXIMAL_HP = atoi(line.substr(strlen("MAXIMAL_HP = "), 100).c_str());
        }
        if (line.substr(0, strlen("COUNT_BULLETS = ")) == "COUNT_BULLETS = ") {
            COUNT_BULLETS = atoi(line.substr(strlen("COUNT_BULLETS = "), 100).c_str());
        }
        if (line.substr(0, strlen("MAX_COUNT_BULLETS = ")) == "MAX_COUNT_BULLETS = ") {
            MAX_COUNT_BULLETS = atoi(line.substr(strlen("MAX_COUNT_BULLETS = "), 100).c_str());
        }
        if (line.substr(0, strlen("KOD = ")) == "KOD = ") {
            KOD = line.substr(strlen("KOD = "), 100);
        }
    }
    file.close();
    //return 0;


    eXit();

    txCreateWindow(1000, 600);

    int dlina = strlen(KOD.c_str());
    MAXIMAL_HP = MAXIMAL_HP - dlina;

    txDisableAutoPause();
    setlocale(LC_ALL, "Russian");


    Butylka pb   = {500,  20,   MAXIMAL_HP,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
    Butylka vrag = {500, 560,   MAXIMAL_HP,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
//---------------------------------------------------------------------

    Bullet bulletButylki[pb.count_bullets];
    for (int i = 0; i < pb.count_bullets; i++) {
        bulletButylki[i] = {0, 0, false};
    }

    Bullet bulletVraga[vrag.count_bullets];
    for (int i = 0; i < vrag.count_bullets; i++) {
        bulletVraga[i] = {0, 0, false};
    }



    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        fon();
        txClear();
        magazin_shkala(&pb,&vrag, bulletButylki,  bulletVraga, t);

        ograda (2, 300);

        upravlenieVragom        (&vrag.x,  &vrag.y);
        upravleniePervoiButylkoi(&pb.x,    &pb.y);

        ikran ( &pb.x,     &pb.y, 0,   300);
        ikran  (&vrag.x,  &vrag.y,312, 600);
       // strelba(&pb,  &vrag,bulletButylki,  bulletVraga);
        ranen  (&pb,  &vrag,  bulletButylki,  bulletVraga);


         if (pb.hp > 0)
        {
            DNN    (pb.x, pb.y);
        }
        if (vrag.hp > 0)
        {
            ZloyDN  (vrag.x, vrag.y);
        }


        if (dead(&pb, &vrag) == false)
        {
            break;
        }

        txSleep(10);




    }
    return 0;
}
