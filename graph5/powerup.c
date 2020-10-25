#include "powerup.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>

int PowerUpGeneration(int x_perso,int y_perso,int origin,int RT)
{
    char adress[100];
    BITMAP *image;
    srand(time(NULL));
    int x = rand()%16/2;
    if (x > 5 ) x = 0;
    switch (x)
    {
    case 0:
        break;
    case 1:
        sprintf(adress,"image/%d/menu/PowerUp/PowerUp/bombe.bmp",RT);
        image = load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 2:
        sprintf(adress,"image/%d/menu/PowerUp/PowerUp/bombe_rayon.bmp",RT);
        image = load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 3:
        sprintf(adress,"image/%d/menu/PowerUp/PowerUp/life.bmp",RT);
        image = load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 4:
        sprintf(adress,"image/%d/menu/PowerUp/PowerUp/speed.bmp",RT);
        image = load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 5:
        sprintf(adress,"image/%d/menu/PowerUp/PowerUp/invisibilite.bmp",RT);
        image = load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    }
    return x;
}
