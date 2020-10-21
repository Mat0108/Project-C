#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>

void Load(int *tableau[21][21],FILE *niveau) //fonction pour un charger un niveau précreer
{
    int i,j;
    const int RT = 21;
    int niv;
    for(i=0;i<RT+1;i++)
    {
        for (j=0;j<RT+1;j++)
        {
            niv = fgetc(niveau);
            if (niv != EOF)
            {
                switch(niv)
                {
                case '0':
                tableau[i][j] = 0;
                break;
                case '1':
                tableau[i][j] = 1;
                break;
                case '2':
                tableau[i][j] = 2;
                break;
                }
            }
        }
    }
}
void MethodeCreate(int *tableau[21][21],int choix) // 0 Aleatoire, 1 niveau 1, 2 niveau 2...
{
    int i,j;
    const int RT = 21;
    char adress[100];
    FILE *niveau;

    if (choix > 5)
    {
        for(i=0; i<RT;i++) //Case bordure
        {
            tableau[i][0] = 2;
            tableau[i][RT-1] = 2;
            tableau[0][i] = 2;
            tableau[RT-1][i] = 2;
        }
        for (i=1;i<RT-1;i++) //Aleatoire des cases
        {
            for (j=1;j<RT-1;j++)
            {
                tableau[i][j] = ((rand()%15)/10); //Pour modifier le random, changer %30 et /10(inversement)
                if(tableau[i][j] > 1) tableau[i][j] = 1;
                if(i%2 == 0 && j%2 == 0) tableau[i][j] = 2; //case special

            }
        }
        for (i=1;i<3;i++) //eviter soucis spawn kill
        {
            tableau[i][1]=0;
            tableau[RT-i-1][1]=0;
            tableau[1][RT-i-1]=0;
            tableau[RT-i-1][RT-2]=0;
        }
        tableau[RT-2][2]=0;
        tableau[2][RT-2]=0;
        tableau[RT-2][RT-3]=0;
        tableau[1][2]=0;
    }
    else
    {
        sprintf(adress,"niveau/niveau %d.txt", choix);
        niveau = fopen(adress,"r");
        Load(tableau,niveau);
    }
}

void Create(int *tableau[21][21],int choixniveau)
{
    const int RT = 21;
    FILE *niveau;
    char niv[RT*2];
    int i,j;
    srand(time(NULL)); //initiatilisation random
    MethodeCreate(tableau,choixniveau);
}

void affichage(int tableau[21][21])
{
    int i,j;
    const int RT = 21;
    for (i = 0;i<RT;i++)
    {
        for (j=0;j<RT;j++)
        {
            printf("%d ",tableau[i][j]);
        }
        printf("\n");
    }
}
int AffichageAllegro(int tableau[21][21],int debut,int *BombeList[5][3])
{
    BITMAP *image;
    int i,j;
    const int RT = 21;
    for (i = debut;i<RT;i++)
    {
        for (j=0;j<RT;j++)
        {
            switch(tableau[i][j])
            {
            case 0 :
                image=load_bitmap("image/sol2.bmp",NULL);
                blit(image,screen,0,0,40*j,40*i,image->w, image->h);
                //rectfill(screen,40*(j),40*i,40*(j+1),40*(i+1),makecol(90,205,80)); //rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
                break;
            case 1 :
                image=load_bitmap("image/brick red.bmp",NULL);
                blit(image,screen,0,0,40*j,40*i,image->w, image->h);
                //rectfill(screen,40*(j),40*i,40*(j+1),40*(i+1),makecol(255,55,55));
                break;
            case 2 :
                image=load_bitmap("image/brick grey.bmp",NULL);
                blit(image,screen,0,0,40*j,40*i,image->w, image->h);
                //rectfill(screen,40*(j),40*i,40*(j+1),40*(i+1),makecol(119,129,121));
                break;
            }
        }
    }
    return BombeAffichage(BombeList);
}



