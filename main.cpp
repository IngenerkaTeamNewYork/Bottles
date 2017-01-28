#include "TXLib.h"





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
void deadpd(int* pd.x, int* pd.y, int* vrag.x, int* vrag.y, int* pb.hp );
{
    if (pb.hp <= 0)

            if (txMessageBox ("Íà÷àòü çàíîâî?", "Ïðî÷òè ìåíÿ", MB_YESNO) =IDNO = IDYES)

                pb* = {500,  20,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};
                vrag* ={500, 560,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};

                for (int i = 0; i < pb*.count_bullets; i++) {        //Äåëàåì âñå ïóëè íåâèäèìûìè
                    bulletButylki[i] = {0, 0, false};
                }

                for (int i = 0; i < vrag.count_bullets; i++) {      //Äåëàåì âñå ïóëè íåâèäèìûìè
                    bulletVraga[i] = {0, 0, false};
                }

        }





int main()
{
    txDisableAutoPause();
                           //   x   y   æèçíåé   ïóëü               íîìåð ïóëè                öâåò
    Butylka pb = {500,  20,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};
    Butylka vrag =           {500, 560,   10,    objom_magazina,       0, RGB(random(255),random(255),random(255))};

    Bullet bulletButylki[pb.count_bullets];             // 8 ïóëü
    for (int i = 0; i < pb.count_bullets; i++) {        //Äåëàåì âñå ïóëè íåâèäèìûìè
        bulletButylki[i] = {0, 0, false};
    }

    Bullet bulletVraga[vrag.count_bullets];             // 8 ïóëü
    for (int i = 0; i < vrag.count_bullets; i++) {      //Äåëàåì âñå ïóëè íåâèäèìûìè
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

        //Óêàçàòåëü (*) íóæåí äëÿ òîãî, ÷òîáû ìåíÿòü çíà÷åíèå ïåðåìåííîé âíóòðè ôóíêöèè
        upravlenieVragom        (&vrag.x,  &vrag.y);
        upravleniePervoiButylkoi(&pb.x,    &pb.y);

        ikran (&pb.x,     &pb.y, 0,   300);
        ikran (&vrag.x,  &vrag.y,310, 600);

        if (GetAsyncKeyState(VK_SPACE) && (pb.count_bullets > 0)) {
            bulletButylki[pb.poryadkovyiNomerPuli % objom_magazina] = {pb.x-10, pb.y+39, true};
            pb.poryadkovyiNomerPuli = pb.poryadkovyiNomerPuli + 1;
            pb.count_bullets = pb.count_bullets - 1;
        }

        if (GetAsyncKeyState(VK_NUMPAD0) && (vrag.count_bullets > 0)) {
            bulletVraga[vrag.poryadkovyiNomerPuli % objom_magazina] = {vrag.x-10, vrag.y-19, true};
            vrag.poryadkovyiNomerPuli = vrag.poryadkovyiNomerPuli + 1;
            vrag.count_bullets = vrag.count_bullets - 1;
        }

        if (pb.hp > 0) {
            DNN    (pb.x, pb.y);
        }
        if (vrag.hp > 0) {
            ZloyDN  (vrag.x, vrag.y);
        }

        for (int i = 0; i < objom_magazina; i++) {
            drawBullet(&bulletButylki[i]);
            drawBulletVraga(&bulletVraga[i]);

            if (pb.hp > 0 &&
                bulletVraga[i].x <= pb.x &&
                bulletVraga[i].x >= pb.x - 20 &&
                bulletVraga[i].y <= pb.y + 30 &&
                bulletVraga[i].y >= pb.y) {//ïîïàäàíèå {
                pb.hp = pb.hp - 1;//æèçíè (êàê ñ êë-îì ïóëü)
                txSleep(10);
            }
            if (abs(bulletButylki[i].x - (vrag.x + 20)) + abs(bulletButylki[i].y - vrag.y) < 20) {//ïîïàäàíèå {
                vrag.hp = vrag.hp - 1;//æèçíè (êàê ñ êë-îì ïóëü)
                txSleep(10);
            }
        }

        if (t % 300 == 0) {
            pb.count_bullets++;
            vrag.count_bullets++;
        }




        deadpd(&pb.x, &pb.y, &vrag.x, &vrag.y, &pb.hp);
        txSleep(10);
        t = t + 10;
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            exit(0);
        }
    }
    return 0;
}
