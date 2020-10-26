#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>
void PersoAffichage(int x_perso,int y_perso,int RT,int choix,int origin)
{

    char adress[100];
    BITMAP *perso;
    sprintf(adress, "image/%d/perso2/pug%d.bmp",RT, choix);
    perso = load_bitmap(adress,NULL);
    testload(perso,adress);
    blit(perso,screen,0,0,RT*(x_perso+origin),RT*y_perso,perso->w, perso->h);
}

void BombePlace(int x,int y,int RT,int origin)
{
    char adress[100];
    BITMAP *BOMBE;
    sprintf(adress, "image/%d/bombe/bombe_item_sol.bmp",RT);
    BOMBE = load_bitmap(adress,NULL);
    testload(BOMBE,adress);
    blit(BOMBE,screen,0,0,RT*(x+origin),RT*y,BOMBE->w, BOMBE->h);
}

int PersoDeplacementX(int tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy,int BombeX[5],int BombeY[5],int RT,int choix,int origin)
{
    int i;
    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
        AfffichagePosition(tableau,x_perso,y_perso,RT,origin);
        for (i=0;i<5;i++)
        {
            if (BombeX[i]== x_perso && BombeY[i] ==y_perso) BombePlace(x_perso,y_perso,RT,origin);
        }
        if (dx == 1) x_perso += delta_perso;
        if (dy == 1) y_perso += delta_perso;
        if (dx == -1) x_perso -= delta_perso;
        if (dy == -1) y_perso -= delta_perso;
        PersoAffichage(x_perso,y_perso,RT,choix,origin);
    }
    Sleep(300);
    return x_perso;
}
int PersoDeplacementY(int tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy,int BombeX[5],int BombeY[5],int RT,int choix,int origin)
{
    int i;
    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
        AfffichagePosition(tableau,x_perso,y_perso,RT,origin);
        for (i=0;i<5;i++)
        {
            if (BombeX[i]== x_perso && BombeY[i] ==y_perso)BombePlace(x_perso,y_perso,RT,origin);
        }
        if (dx == 1) x_perso += delta_perso;
        if (dy == 1) y_perso += delta_perso;
        if (dx == -1) x_perso -= delta_perso;
        if (dy == -1) y_perso -= delta_perso;
        PersoAffichage(x_perso,y_perso,RT,choix,origin);
    }
    Sleep(300);
    return y_perso;
}


void BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation,int RT,int origin)
{
    BITMAP  *BOMBE;
    char adress[100];
    if (y+y2*rayon>0 && x+x2*rayon > 0)
    {
    sprintf(adress,"image/%d/bombe/bombe_%d_pointe_%d.bmp",RT,tableau[y+y2*rayon][x+x2*rayon],rotation);
    BOMBE = load_bitmap(adress,NULL);
    testload(BOMBE,adress);
    blit(BOMBE,screen,0,0,RT*(x+x2*rayon+origin),RT*(y+y2*rayon),BOMBE->w, BOMBE->h);
    }
    else if (rotation == 3)
    {
        sprintf(adress,"image/%d/bombe/bombe_2_pointe_%d.bmp",RT,rotation);
        BOMBE = load_bitmap(adress,NULL);
        testload(BOMBE,adress);
        blit(BOMBE,screen,0,0,origin*RT,RT*(y+y2*rayon),BOMBE->w, BOMBE->h);
    }
}
void BombeEffect(int x,int y,int rayon,int *tableau[21][21],int RT,int origin)
{
    BITMAP *BOMBE;
    int i;
    char adress[100];
    sprintf(adress,"image/%d/bombe/bombe_croix_sol.bmp",RT);
    BOMBE = load_bitmap(adress,NULL);
    testload(BOMBE,adress);
    blit(BOMBE,screen,0,0,RT*(x+origin),RT*y,BOMBE->w, BOMBE->h);
    if(rayon>1)
    {
        for(i=1;i<rayon;i++)
        {
            sprintf(adress,"image/%d/bombe/ligne_1.bmp",RT);
            BOMBE = load_bitmap(adress,NULL);
            testload(BOMBE,adress);
            if (x-rayon+i > 0) blit(BOMBE,screen,0,0,RT*(x-1*i+origin),RT*y+RT/4,BOMBE->w, BOMBE->h);
            blit(BOMBE,screen,0,0,RT*(x+1*i+origin),RT*y+RT/4,BOMBE->w, BOMBE->h);
            sprintf(adress,"image/%d/bombe/ligne_2.bmp",RT);
            BOMBE = load_bitmap(adress,NULL);
            testload(BOMBE,adress);
            blit(BOMBE,screen,0,0,RT*(x+origin)+RT/4,RT*(y-1*i),BOMBE->w, BOMBE->h);
            blit(BOMBE,screen,0,0,RT*(x+origin)+RT/4,RT*(y+1*i),BOMBE->w, BOMBE->h);
        }
    }
    BombeEffect2(x,y,rayon,tableau,1,0,1,RT,origin);
    BombeEffect2(x,y,rayon,tableau,-1,0,3,RT,origin);
    BombeEffect2(x,y,rayon,tableau,0,1,4,RT,origin);
    BombeEffect2(x,y,rayon,tableau,0,-1,2,RT,origin);
}
void BombeEffectInv(int x,int y,int rayon,int *tableau[21][21],int BombeX[5],int BombeY[5],int RT,int origin)
{
    int i,j;
    BITMAP *image;
    char adress[100];
    for(i=0;i<2*rayon+2;i++)
    {
        AfffichagePosition(tableau,x,y+i-rayon,RT,origin);
        if(x+i-rayon >0 ) AfffichagePosition(tableau,x+i-rayon,y,RT,origin);
        else
        {
            sprintf(adress, "image/%d/brick grey.bmp",RT);
            image=load_bitmap(adress,NULL);
            testload(image,adress);
            blit(image,screen,0,0,RT*origin,RT*y,image->w, image->h);
        }
        for (j=0;j<5;j++)
        {
            if (x+i-rayon == BombeX[j] && y == BombeY[j] && BombeX[j]!=0 && x != BombeX[j]) BombePlace(BombeX[j],BombeY[j],RT,origin);
            if (x == BombeX[j] && y+i-rayon == BombeY[j] && BombeX[j]!=0 && x != BombeX[j]) BombePlace(BombeX[j],BombeY[j],RT,origin);
        }
    }

}
