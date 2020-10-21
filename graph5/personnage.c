#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>
void PersoAffichage(x_perso,y_perso)
{
    BITMAP *perso;
    perso = load_bitmap("image/perso3.bmp",NULL);
    blit(perso,screen,0,0,10+40*x_perso,10+40*y_perso,perso->w, perso->h);
}
void BombePlace(int x,int y)
{
    BITMAP *BOMBE;
    BOMBE = load_bitmap("image/bombe/bombe_item_sol.bmp",NULL);
    blit(BOMBE,screen,0,0,40*x,40*y,BOMBE->w, BOMBE->h);
}

int PersoDeplacementX(int *tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy,int *BombeList[5][2])
{
    int i;
    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
        AfffichagePosition(tableau,x_perso,y_perso);
        for (i=0;i<5;i++)
        {
            if (BombeList[i][0] == x_perso && BombeList[i][1] ==y_perso) BombePlace(x_perso,y_perso);
        }
        if (dx == 1) x_perso += delta_perso;
        if (dy == 1) y_perso += delta_perso;
        if (dx == -1) x_perso -= delta_perso;
        if (dy == -1) y_perso -= delta_perso;
        PersoAffichage(x_perso,y_perso);
    }
    Sleep(300);
    return x_perso;
}
int PersoDeplacementY(int *tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy,int *BombeList[5][2])
{
    int i;
    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
        AfffichagePosition(tableau,x_perso,y_perso);
        for (i=0;i<5;i++)
        {
            if (BombeList[i][0] == x_perso && BombeList[i][1] ==y_perso) BombePlace(x_perso,y_perso);
        }
        if (dx == 1) x_perso += delta_perso;
        if (dy == 1) y_perso += delta_perso;
        if (dx == -1) x_perso -= delta_perso;
        if (dy == -1) y_perso -= delta_perso;
        PersoAffichage(x_perso,y_perso);
    }
    Sleep(300);
    return y_perso;
}

int BombeAffichage(int *BombeList[5][3])
{
    int nb_bombes = 0;
    int i;
    for (i=0;i<5;i++)
    {
        if (BombeList[i][0] != 0)
        {
            BombePlace(BombeList[i][0],BombeList[i][1]);
            nb_bombes++;
        }
    }
    return nb_bombes;
}
int BombeReplace(int *tableau[21][21],int x,int y)
{
    if (tableau[x][y] == 1) return 0;
}
int BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation)
{
    BITMAP  *BOMBE;
    char adress[100];
    sprintf(adress,"image/bombe/bombe_%d_pointe_%d.bmp",tableau[y+y2*rayon][x+x2*rayon],rotation);
    BOMBE = load_bitmap(adress,NULL);
    blit(BOMBE,screen,0,0,40*(x+x2*rayon),40*(y+y2*rayon),BOMBE->w, BOMBE->h);
}
int BombeEffect(int x,int y,int rayon,int *tableau[21][21])
{
    BITMAP *BOMBE;
    int i;

    BOMBE = load_bitmap("image/bombe/bombe_croix_sol.bmp",NULL);
    blit(BOMBE,screen,0,0,40*x,40*y,BOMBE->w, BOMBE->h);
    if(rayon>1)
    {
        for(i=1;i<rayon;i++)
        {
            BOMBE = load_bitmap("image/bombe/ligne_1.bmp",NULL);

            blit(BOMBE,screen,0,0,40*(x-1*i),40*y+10,BOMBE->w, BOMBE->h);
            blit(BOMBE,screen,0,0,40*(x+1*i),40*y+10,BOMBE->w, BOMBE->h);
            BOMBE = load_bitmap("image/bombe/ligne_2.bmp",NULL);
            blit(BOMBE,screen,0,0,40*x+10,40*(y-1*i),BOMBE->w, BOMBE->h);
            blit(BOMBE,screen,0,0,40*x+10,40*(y+1*i),BOMBE->w, BOMBE->h);
        }
    }
    BombeEffect2(x,y,rayon,tableau,1,0,1);
    BombeEffect2(x,y,rayon,tableau,-1,0,3);
    BombeEffect2(x,y,rayon,tableau,0,1,4);
    BombeEffect2(x,y,rayon,tableau,0,-1,2);
}
void BombeEffectInv(int x,int y,int rayon,int *tableau[21][21])
{
    int i;
    for(i=0;i<=2*rayon+1;i++)
    {
    AfffichagePosition(tableau,i,y);
    AfffichagePosition(tableau,x,i);
    }
}
