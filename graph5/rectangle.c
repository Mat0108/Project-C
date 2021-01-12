#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>

//permet de charger un niveau depuis un .txt
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
//Permet de creer le niveau
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
//affichage du niveau dans la console pour tester
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
//affichage du niveau dans Allegro
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
//permet de corriger un bug d'affichage
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
//Desaffichage du perso
void AffichagePosition(int tableau[21][21],int x_perso,int y_perso,int RT,int origin)
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
//Desaffichage du menu
void AffichageMenuInv(int RT,int CT,int origin,int debut)
{
    int i,j;
    BITMAP *image;
    char adress[100];
    for (i=debut;i<=debut+origin;i++)
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
//affichage du premier menu
void AffichageMenu(int RT,int CT,int origin)
{
    AffichageMenuInv(RT,CT,origin,0);
    AffichageMenuInv(RT,CT,origin,CT+origin);
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
//affichage du menu de choix de niveau
int AffichageNiveau(int RT,int CT,int origin)
{

    int i;
    BITMAP *image;
    char adress[100];
    sprintf(adress,"image/%d/menu/choix niveau.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*3,image->w, image->h);
    for (i=2;i<7;i++)
    {
        sprintf(adress, "image/%d/menu/niveau %d.bmp",RT,i-1);
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
//affichage du menu de choix du nombre de player
void AffichagePlayer(int RT,int CT,int origin)
{
    int i;
    BITMAP *image;
    char adress[100];
    for (i=1;i<4;i++)
    {
        sprintf(adress, "image/%d/menu/nb_player %d.bmp",RT,i-1);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
    }
    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*1,RT*(1+2*i),image->w, image->h);
}
//affichage du choix du perso
void AffichagePerso(int RT,int CT, int yposition,int player)
{
    int i=1;
    BITMAP *image;
    char adress[100];
    int typeperso = default_perso();
    /* sprintf(adress, "image/%d/menu/stitch/stitch_0.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
    */
    for (i=1;i<6;i++)
    {
        if (typeperso == 1) sprintf(adress, "image/%d/menu/stitch/stitch_%d.bmp",RT,i-1);
        if (typeperso == 2) sprintf(adress, "image/%d/menu/pug/pug_%d.bmp",RT,i-1);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
    }
    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);

}


void AffichageTypePerso(int RT,int CT,int yposition,int nbplayer)
{
    int i = 1;
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/menu/nb_perso_0.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
    i++;

    sprintf(adress, "image/%d/menu/stitch/stitch_01.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
    i++;

    sprintf(adress, "image/%d/menu/pug/pug_01.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
    i++;

    sprintf(adress, "image/%d/menu/quit.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*yposition,RT*(1+2*i),image->w, image->h);
}

