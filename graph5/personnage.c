#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
void PersoAffichage(x_perso,y_perso)
{
    BITMAP *perso;
    perso = load_bitmap("image/perso3.bmp",NULL);
    if (!perso)
    {
        allegro_message("pas pu trouver/charger perso.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    blit(perso,screen,0,0,10+40*x_perso,10+40*y_perso,perso->w, perso->h);
}

int PersoDeplacementX(int *tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy)
{

    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
            if (dx == 1) x_perso += delta_perso;
            if (dy == 1) y_perso += delta_perso;
            if (dx == -1) x_perso -= delta_perso;
            if (dy == -1) y_perso -= delta_perso;
            AffichageAllegro(tableau);
            PersoAffichage(x_perso,y_perso);
    }
    return x_perso;
}
int PersoDeplacementY(int *tableau[21][21],int x_perso, int y_perso, int delta_perso,int dx, int dy)
{

    if (tableau[y_perso+dy*delta_perso][x_perso+dx*delta_perso] == 0)
    {
            if (dx == 1) x_perso += delta_perso;
            if (dy == 1) y_perso += delta_perso;
            if (dx == -1) x_perso -= delta_perso;
            if (dy == -1) y_perso -= delta_perso;
            AffichageAllegro(tableau);
            PersoAffichage(x_perso,y_perso);
    }
    return y_perso;

}


