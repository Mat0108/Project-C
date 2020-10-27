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

    if (choix >=5)
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
void AffichageAllegro(int tableau[21][21],int debut,int RT,int CT,int origin)
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
                blit(image,screen,0,0,RT*(j+origin),RT*i,image->w, image->h);
                break;
            case 1 :
                sprintf(adress, "image/%d/brick red.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*(j+origin),RT*i,image->w, image->h);
                break;
            case 2 :
                sprintf(adress, "image/%d/brick grey.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*(j+origin),RT*i,image->w, image->h);
                break;
            }
        }
    }
}
void AffichageAllegro2(int tableau[21][21],int debut,int RT,int CT,int origin)
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
            case 1 :
                sprintf(adress, "image/%d/brick red.bmp",RT);
                image=load_bitmap(adress,NULL);
                testload(image,adress);
                blit(image,screen,0,0,RT*(j+origin),RT*i,image->w, image->h);
                break;
            default :
                break;
             }
        }
    }
}

void AfffichagePosition(int tableau[21][21],int x_perso,int y_perso,int RT,int origin)
{
    BITMAP *image;
    char adress[100];
    switch(tableau[y_perso][x_perso])
    {
    case 0 :
        sprintf(adress, "image/%d/sol2.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 1 :
        sprintf(adress, "image/%d/brick red.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    case 2 :
        sprintf(adress, "image/%d/brick grey.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(x_perso+origin),RT*y_perso,image->w, image->h);
        break;
    }
}
void AffichageMenuInv(int RT,int CT,int origin,int debut)
{
    int i,j;
    BITMAP *image;
    char adress[100];
    for (i=0;i<=origin;i++)
    {
        for(j=0;j<=CT;j++)
        {
            sprintf(adress, "image/%d/brick grey.bmp",RT);
            image=load_bitmap(adress,NULL);
            testload(image,adress);
            blit(image,screen,0,0,RT*i,RT*j,image->w, image->h);
        }
    }
}
void AffichageMenu(int RT,int CT,int origin)
{
    AffichageMenuInv(RT,CT,origin,0);
    int i=1;
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/menu/play.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*(1+2*(i+1)),image->w, image->h);

}
int AffichageNiveau(int RT,int CT,int origin)
{

    int i;
    BITMAP *image;
    char adress[100];
    for (i=1;i<6;i++)
    {
        sprintf(adress, "image/%d/menu/niveau %d.bmp",RT,i);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
    }
    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
    return 0;
}


void AffichagePerso(int RT,int CT, int origin)
{
    int i;
    BITMAP *image;
    char adress[100];
    for (i=1;i<5;i++)
    {
        sprintf(adress, "image/%d/menu/perso %d.bmp",RT,i);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
    }
    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
}
void AffichageLigne(float x,float y,int RT)
{
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/menu/ligne.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*x,RT*y,image->w, image->h);
}
void AffichageItem(int RT,int CT,int nb_vie,int nb_bombes,int rayon ,int speed)
{
    BITMAP *image;
    char adress[100];
    int debut = 1;
    int delta = 2;
    AffichageLigne(3,debut,RT);
    sprintf(adress, "image/%d/menu/PowerUp/Life/LIFE %d.bmp",RT,nb_vie);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,0,RT*debut,image->w, image->h);
    AffichageLigne(3,debut+delta,RT);
    sprintf(adress, "image/%d/menu/PowerUP/Bombe/bombe %d.bmp",RT,nb_bombes);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,0,RT*(debut+delta),image->w, image->h);
    AffichageLigne(3,debut+2*delta,RT);
    sprintf(adress, "image/%d/menu/PowerUP/Rayon/Rayon %d.bmp",RT,rayon);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,0,RT*(debut+2*delta),image->w, image->h);
    AffichageLigne(3,debut+3*delta,RT);
    sprintf(adress, "image/%d/menu/PowerUP/Speed/Speed %d.bmp",RT,speed);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,0,RT*(debut+3*delta),image->w, image->h);

}



