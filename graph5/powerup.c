#include "powerup.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>
//permet de generer les powerup
void PowerUpGeneration2(char item[10],int x,int y, int RT)
{
    char adress[100];
    BITMAP *image;
    sprintf(adress,"image/%d/menu/PowerUp/PowerUp/%s.bmp",RT,item);
    image = load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*x,RT*y,image->w, image->h);
}
//affichage des powerup
void PowerUpAffichage(int tableau[21][21],int origin,int RT,int CT)
{
    int i,j;
    for (i=0;i<CT;i++)
    {
        for (j=0;j<CT;j++)
        {
            switch (tableau[i][j])
            {
            case 0:
                break;
            case 20:
                PowerUpGeneration2("bombe",j+origin,i,RT);
                break;
            case 21:
                PowerUpGeneration2("bombe",j+origin,i,RT);
                break;
            case 22:
                PowerUpGeneration2("bombe",j+origin,i,RT);
                break;
            case 23:
                PowerUpGeneration2("bombe_rayon",j+origin,i,RT);
                break;
            case 24:
                PowerUpGeneration2("bombe_rayon",j+origin,i,RT);
                break;
            case 25:
                PowerUpGeneration2("bombe_rayon",j+origin,i,RT);
                break;
            case 26:
                PowerUpGeneration2("speed",j+origin,i,RT);
                break;
            case 27:
                PowerUpGeneration2("speed",j+origin,i,RT);
                break;
            case 28:
                PowerUpGeneration2("life",j+origin,i,RT);
                break;
            case 29:
                PowerUpGeneration2("invisibilite",j+origin,i,RT);
                break;
            }
        }
    }
}

