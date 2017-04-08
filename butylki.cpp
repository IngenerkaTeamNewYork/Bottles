#include <Windows.h>
#include "TXLib.h"
#include <iostream>
#include <locale>


#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

const int OBJOM_ZDOROVYA = 10;
const int OBJOM_MAGAZINA = 8;
int t = 0;

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

struct Button
{
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    const char* text;
    bool (*onClick)();
};

bool return_to_game()
{
    return true;
}

void draw_button(Button* button)
{
    txRectangle(button->min_x, button->min_y, button->max_x, button->max_y);
    txDrawText(button->min_x, button->min_y, button->max_x, button->max_y, button->text);
}

bool is_button_clicked(Button* button)
{
    if (txMouseX() >= button->min_x &&
        txMouseX() <= button->max_x &&
        txMouseY() >= button->min_y &&
        txMouseY() <= button->max_y &&
        txMouseButtons() & 1) {
            return true;
        }
    return false;
}

void pause(Butylka* butylki_usera, int* kolichestvo_butylok_usera)
{
    bool isreturn = false;

    if (GetAsyncKeyState(VK_ESCAPE)) {

        txSelectFont("Times New Roman", 17);

        txSetColour(TX_BLUE);
        txRectangle(330, 150, 660, 350);
        txSetColour(TX_BLACK);

        Button buttonPlay = {440, 178, 550, 206, "Play", return_to_game};
        Button buttonMenu = {440, 234, 550, 262, "Menu", return_to_game};
        Button buttonExit = {440, 290, 550, 318, "Exit", return_to_game};

        draw_button(&buttonPlay);
        draw_button(&buttonMenu);
        draw_button(&buttonExit);

        while (!isreturn) {
            if (is_button_clicked(&buttonPlay)) {
                isreturn = buttonPlay.onClick();
            }
            if (is_button_clicked(&buttonMenu))
            {
                butylki_usera[*kolichestvo_butylok_usera] = {random(500),  80,   OBJOM_ZDOROVYA,    OBJOM_MAGAZINA,   0};
                *kolichestvo_butylok_usera = *kolichestvo_butylok_usera + 1;
                txSleep(1000);
            }
            if (is_button_clicked(&buttonExit))
            {
               WinExec("D:\\Инженерка\\C++\\Chainik\\Chelovechek\\menu1\\main2.exe",SW_SHOW);
            }
            txSleep(10);
        }
    }
}
void drawBullet(Bullet *bullet)
{
    txSetFillColor(TX_BLUE);
    if (bullet->isVisible) {
        txCircle(bullet->x, bullet->y, 3);
        bullet->y = bullet->y + 19;
    }
}
void drawBulletVraga(Bullet *bullet)
{
    txSetFillColor(TX_RED);
    if(bullet->isVisible) {
        txCircle(bullet->x, bullet->y, 3);
        bullet->y = bullet->y - 19 ;
    }
}

void ikran (int *x, int *y, int minPoY, int maxPoY)
{
    if (*x > 898) {
        *x = 898 ;
    }
    if (*y > maxPoY - 40) {
        *y = maxPoY - 40;
    }

    if (*x < 121) {
        *x = 121;
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

        WinExec("D:\\Инженерка\\C++\\Chainik\\Chelovechek\\menu1\\main2.exe",SW_SHOW);
            /*
        if (txMessageBox (TEXT("Ты окончательно умер?"), "Соглашайся, второго шанса не будет (но это неточно)", MB_YESNO) == IDNO) {
            *pb   = {500,  20,   10,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
        } else {
            return false;
        }
        */
    }


    if (vrag->hp <= 0) {
          WinExec("D:\\Инженерка\\C++\\Chainik\\Chelovechek\\menu1\\main2.exe",SW_SHOW);
        /*
        if (txMessageBox (TEXT("Ты окончательно умер?"), "Соглашайся, второго шанса не будет (но это неточно)", MB_YESNO) == IDNO) {
            *vrag = {500, 560,   10,    OBJOM_MAGAZINA,       0, RGB(random(255),random(255),random(255))};
        } else {
            return false;
        }
    */
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



   if (t % 50 == 0)
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
            txRectangle(25 , 550 - 120 * pb->hp / OBJOM_ZDOROVYA, 80, 550);
            txSetFillColor(TX_BLUE);
            txRectangle(25, 250 - 120  * vrag->hp / OBJOM_ZDOROVYA, 80 , 250);
            txSetFillColor(TX_GREEN);
            txRectangle(915, 550 - 120 * pb->count_bullets / OBJOM_MAGAZINA, 980 , 550);
            txRectangle(915, 250 - 120 * vrag->count_bullets / OBJOM_MAGAZINA, 980 , 250);
}

void eXit()
{
    if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
}

int main()
{
    int kolichestvo_butylok_usera = 0;
    eXit();

    txDisableAutoPause();
    setlocale(LC_ALL, "Russian");

    Butylka butylki_usera[10];
    Butylka pb   = {500,  20,   OBJOM_ZDOROVYA,    OBJOM_MAGAZINA,   0};
    Butylka vrag = {500, 560,   OBJOM_ZDOROVYA,    OBJOM_MAGAZINA,   0};
//---------------------------------------------------------------------

    Bullet bulletButylki[pb.count_bullets];
    for (int i = 0; i < pb.count_bullets; i++) {
        bulletButylki[i] = {0, 0, false};
    }

    Bullet bulletVraga[vrag.count_bullets];
    for (int i = 0; i < vrag.count_bullets; i++) {
        bulletVraga[i] = {0, 0, false};
    }


    txCreateWindow(1000, 600);

    while (!GetAsyncKeyState('P'))
    {
        fon();

        magazin_shkala(&pb,&vrag, bulletButylki,  bulletVraga, t);

        ograda (2, 300);


        upravlenieVragom        (&vrag.x,  &vrag.y);
        upravleniePervoiButylkoi(&pb.x,    &pb.y);
        for (int i = 0; i < kolichestvo_butylok_usera; i++) {
            upravleniePervoiButylkoi(&butylki_usera[i].x, &butylki_usera[i].y);
        }

        ikran ( &pb.x,     &pb.y, 0,   300);
        ikran  (&vrag.x,  &vrag.y,312, 600);
        for (int i = 0; i < kolichestvo_butylok_usera; i++) {
            ikran(&butylki_usera[i].x, &butylki_usera[i].y, 0,   300);
        }
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

        for (int i = 0; i < kolichestvo_butylok_usera; i++) {
            DNN(butylki_usera[i].x, butylki_usera[i].y);
        }


        if (dead(&pb, &vrag) == false)
        {
            break;
        }

        pause(butylki_usera, &kolichestvo_butylok_usera);
        t = t + 10;

        txSleep(10);
    }

    return 0;
}
