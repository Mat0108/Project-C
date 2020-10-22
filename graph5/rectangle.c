#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>

void Load(int *tableau[21][21],FILE *niveau,int CT) //fonction pour un charger un niveau précreer
{
    int i,j;
    int niv;
    for(i=0;i<CT+1;i++)
    {
        for (j=0;j<CT+1;j++)
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
void MethodeCreate(int *tableau[21][21],int choix,int CT) // 0 Aleatoire, 1 niveau 1, 2 niveau 2...
{
    int i,j;
    char adress[100];
    FILE *niveau;

    if (choix > 5)
    {
        for(i=0; i<CT;i++) //Case bordure
        {
            tableau[i][0] = 2;
            tableau[i][CT-1] = 2;
            tableau[0][i] = 2;
            tableau[CT-1][i] = 2;
        }
        for (i=1;i<CT-1;i++) //Aleatoire des cases
        {
            for (j=1;j<CT-1;j++)
            {
                tableau[i][j] = ((rand()%15)/10); //Pour modifier le random, changer %30 et /10(inversement)
                if(tableau[i][j] > 1) tableau[i][j] = 1;
                if(i%2 == 0 && j%2 == 0) tableau[i][j] = 2; //case special

            }
        }
        for (i=1;i<3;i++) //eviter soucis spawn kill
        {
            tableau[i][1]=0;
            tableau[CT-i-1][1]=0;
            tableau[1][CT-i-1]=0;
            tableau[CT-i-1][CT-2]=0;
        }
        tableau[CT-2][2]=0;
        tableau[2][CT-2]=0;
        tableau[CT-2][CT-3]=0;
        tableau[1][2]=0;
    }
    else
    {
        sprintf(adress,"niveau/niveau %d.txt", choix);
        niveau = fopen(adress,"r");
        Load(tableau,niveau,CT);
    }
}

void Create(int *tableau[21][21],int choixniveau,int CT)
{
    srand(time(NULL)); //initiatilisation random
    MethodeCreate(tableau,choixniveau,CT);
}

void affichage(int *tableau[21][21],int CT)
{
    int i,j;
    for (i = 0;i<CT;i++)
    {
        for (j=0;j<CT;j++)
        {
            printf("%d ",tableau[i][j]);
        }
        printf("\n");
    }
}
void AffichageAllegro(int tableau[21][21],int debut,int RT,int CT)
{
    BITMAP *image;
    int i,j;
    char adress[100];
    for (i = debut;i<CT;i++)
    {
        for (j=0;j<CT;j++)
        {
            switch(tableau[i][j])
            {
            case 0 :
                sprintf(adress, "image/%d/sol2.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*j,RT*i,image->w, image->h);
                break;
            case 1 :
                sprintf(adress, "image/%d/brick red.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*j,RT*i,image->w, image->h);
                break;
            case 2 :
                sprintf(adress, "image/%d/brick grey.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*j,RT*i,image->w, image->h);
                break;
            }
        }
    }
}

void AfffichagePosition(int tableau[21][21],int x_perso,int y_perso,int RT)
{
    BITMAP *image;
    char adress[100];
    switch(tableau[y_perso][x_perso])
    {
    case 0 :
        sprintf(adress, "image/%d/sol2.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*x_perso,RT*y_perso,image->w, image->h);
        break;
    case 1 :
        sprintf(adress, "image/%d/brick red.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*x_perso,RT*y_perso,image->w, image->h);
        break;
    case 2 :
        sprintf(adress, "image/%d/brick grey.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*x_perso,RT*y_perso,image->w, image->h);
        break;
    }
}


