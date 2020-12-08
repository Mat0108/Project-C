#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>
//affichege du perso
void PersoAffichage(int x_perso,int y_perso,int RT,int choix,int origin)
{
    int typeperso = 2;
    char adress[100];
    BITMAP *perso;
    if (typeperso == 1) sprintf(adress, "image/%d/perso/Perso%d.bmp",RT, choix);
    if (typeperso == 2) sprintf(adress, "image/%d/perso2/pug%d.bmp",RT, choix);

    perso = load_bitmap(adress,NULL);
    testload(perso,adress);
    blit(perso,screen,0,0,RT*(x_perso+origin),RT*y_perso,perso->w, perso->h);
}

//affichage de la bombe
void BombePlace(int x,int y,int RT,int origin)
{
    char adress[100];
    BITMAP *BOMBE;
    sprintf(adress, "image/%d/bombe/bombe_item_sol.bmp",RT);
    BOMBE = load_bitmap(adress,NULL);
    testload(BOMBE,adress);
    blit(BOMBE,screen,0,0,RT*(x+origin),RT*y,BOMBE->w, BOMBE->h);
}
//deplacement du perso
int PersoDeplacement(int tableau[21][21],int *PowerUp[21][21],int *x_perso, int *y_perso, int *delta_perso,int dx, int dy,int BombeX[5],int BombeY[5],int *nb_vie,int *nb_Bombe_max,int *rayon,int item,int RT,int CT, int persochoix,int choix,int origin)
{
    int i;
    AffichageAllegro2(tableau,1,RT,CT,origin);
    if (PowerUp[*y_perso+dy][*x_perso+dx]> 19 && PowerUp[*y_perso+dy][*x_perso+dx]< 23 && *nb_Bombe_max<5) (*nb_Bombe_max)++;
    if (PowerUp[*y_perso+dy][*x_perso+dx]> 22 && PowerUp[*y_perso+dy][*x_perso+dx]< 26 && *rayon<5) (*rayon)++;
    //if (PowerUp[*y_perso+dy][*x_perso+dx]> 25 && PowerUp[*y_perso+dy][*x_perso+dx]< 28 && *delta_perso< 3) (*delta_perso)++;
    if (PowerUp[*y_perso+dy][*x_perso+dx]== 28 && *nb_vie<3) *nb_vie++;
    AffichageItem(RT,CT,*nb_vie,*nb_Bombe_max,*rayon,*delta_perso,persochoix,choix,item);
    PowerUp[*y_perso+dy][*x_perso+dx] = 0;
    if (tableau[*y_perso+dy* *delta_perso][*x_perso+dx* *delta_perso] == 0)
    {
        AfffichagePosition(tableau,*x_perso,*y_perso,RT,origin);
        for (i=0;i<5;i++)
        {
            if (BombeX[i]== *x_perso && BombeY[i] ==*y_perso)BombePlace(*x_perso,*y_perso,RT,origin);
        }
        if (dx == 1) (*x_perso)++;
        if (dy == 1) (*y_perso)++;
        if (dx == -1) (*x_perso)--;
        if (dy == -1) (*y_perso)--;
        PersoAffichage(*x_perso,*y_perso,RT,persochoix,origin);
    }
    return 1;
}
//Creation de la bombe
int BombePlacement(int *BombeX[5],int *BombeY[5], int *BombeTimer[5], int *nb_Bombe,int nb_Bombe_max,int tableau[21][21] ,int x_perso,int y_perso,int RT,int origin,int MenuPerso)
{
     if (*nb_Bombe < nb_Bombe_max)
    {
        BombeX[*nb_Bombe] = x_perso;
        BombeY[*nb_Bombe] = y_perso;
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        BombeTimer[*nb_Bombe] = timeInfos->tm_sec+3;
        if (BombeTimer[*nb_Bombe]>= 60) BombeTimer[*nb_Bombe] = BombeTimer[*nb_Bombe] - 60;
        AfffichagePosition(tableau,x_perso,y_perso,RT,origin);
        BombePlace(x_perso,y_perso,RT,origin);
        PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
        (*nb_Bombe)++;
    }
    return 1;
}
//effet de la bombe : affichage de la pointe de l'explotion
void BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation,int RT,int CT,int origin)
{
    BITMAP  *BOMBE;
    char adress[100];
    if (y+y2*rayon>0 && x+x2*rayon > 0 && y+y2*rayon<CT && x+x2*rayon < CT)
    {
    sprintf(adress,"image/%d/bombe/bombe_%d_pointe_%d.bmp",RT,tableau[y+y2*rayon][x+x2*rayon],rotation);
    BOMBE = load_bitmap(adress,NULL);
    testload(BOMBE,adress);
    blit(BOMBE,screen,0,0,RT*(x+x2*rayon+origin),RT*(y+y2*rayon),BOMBE->w, BOMBE->h);
    }

    else if (rotation == 1)
    {
        sprintf(adress,"image/%d/bombe/bombe_2_pointe_%d.bmp",RT,rotation);
        BOMBE = load_bitmap(adress,NULL);
        testload(BOMBE,adress);
        blit(BOMBE,screen,0,0,RT*(origin+CT-1),RT*(y+y2*rayon),BOMBE->w, BOMBE->h);
    }
    else if(rotation == 2)
    {
        sprintf(adress,"image/%d/bombe/bombe_2_pointe_%d.bmp",RT,rotation);
        BOMBE = load_bitmap(adress,NULL);
        testload(BOMBE,adress);
        blit(BOMBE,screen,0,0,RT*(x+x2*rayon+origin),0,BOMBE->w, BOMBE->h);
    }
    else if (rotation == 3)
    {
        sprintf(adress,"image/%d/bombe/bombe_2_pointe_%d.bmp",RT,rotation);
        BOMBE = load_bitmap(adress,NULL);
        testload(BOMBE,adress);
        blit(BOMBE,screen,0,0,origin*RT,RT*(y+y2*rayon),BOMBE->w, BOMBE->h);
    }
    else if(rotation == 4)
    {
        sprintf(adress,"image/%d/bombe/bombe_2_pointe_%d.bmp",RT,rotation);
        BOMBE = load_bitmap(adress,NULL);
        testload(BOMBE,adress);
        blit(BOMBE,screen,0,0,RT*(x+origin),RT*(CT-1),BOMBE->w, BOMBE->h);
    }

}
//effet de la bombe : affichage du rayon de la bombe (les traits)
void BombeEffect(int x,int y,int rayon,int *tableau[21][21],int RT,int CT,int origin)
{
    BITMAP *BOMBE;
    int i;
    char adress[100];
    if (x != 0 && y != 0)
    {
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
                if (x-i>0) blit(BOMBE,screen,0,0,RT*(x-1*i+origin),RT*y+RT/4,BOMBE->w, BOMBE->h);
                if (x+i<CT-1)blit(BOMBE,screen,0,0,RT*(x+1*i+origin),RT*y+RT/4,BOMBE->w, BOMBE->h);
                sprintf(adress,"image/%d/bombe/ligne_2.bmp",RT);
                BOMBE = load_bitmap(adress,NULL);
                testload(BOMBE,adress);
                if (y-i>0) blit(BOMBE,screen,0,0,RT*(x+origin)+RT/4,RT*(y-1*i),BOMBE->w, BOMBE->h);
                if (y+i<CT-1)blit(BOMBE,screen,0,0,RT*(x+origin)+RT/4,RT*(y+1*i),BOMBE->w, BOMBE->h);
            }
        }
        BombeEffect2(x,y,rayon,tableau,1,0,1,RT,CT,origin);
        BombeEffect2(x,y,rayon,tableau,-1,0,3,RT,CT,origin);
        BombeEffect2(x,y,rayon,tableau,0,1,4,RT,CT,origin);
        BombeEffect2(x,y,rayon,tableau,0,-1,2,RT,CT,origin);
    }
}
//affichage des effect de la bombe
void BombeEffect3(int BombeTimer[5],int BombeX[5], int BombeY[5],int rayon, int tableau[21][21],int RT,int CT,int origin)
{
    for (int i=0;i<5;i++)
    {
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        if (BombeTimer[i] == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] != 0)
            {
                BombeEffect(BombeX[i],BombeY[i],rayon,tableau,RT,CT,origin);
            }
        if (BombeTimer[i] + 2 == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] != 0)
            {
                BombeEffectInv(BombeX[i],BombeY[i],rayon,tableau,BombeX,BombeY,RT,origin);
            }

    }
}
//modification des tableaux par les bombes
void BombeEffect4(int *BombeX[5],int *BombeY[5],int *BombeTimer[5],int tableau[21][21],int *PowerUpTab[21][21],int x_perso,int y_perso,int *nb_vie,int nb_Bombe_max,int *nb_Bombe,int rayon,int delta_perso,int RT,int CT,int origin,int MenuPerso,int player,int xorigin,int *InvisibiliteTimerval)
{
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    int i,j,k,l;
    int xBombe;
    int yBombe;
    for (i=0;i<5;i++)
    {
        if (BombeTimer[i]== timeInfos->tm_sec && BombeTimer[i] != 0)
        {
            BombeEffect(BombeX[i],BombeY[i],rayon,tableau,RT,CT,origin);
            srand(time(NULL));
            for (j=0;j<2*rayon+1;j++)
            {
                xBombe = BombeX[i];
                yBombe = BombeY[i];
                if (tableau[(yBombe)][j+xBombe-rayon] == 1){

                    tableau[yBombe][j+xBombe-rayon] = 0;
                    int x = rand()%30;
                    if (x < 20 && x>29 ) x=0;

                    PowerUpTab[yBombe][j+xBombe-rayon] = x;

                }
                if (tableau[j+yBombe-rayon][xBombe] == 1){
                    tableau[j+yBombe-rayon][xBombe] = 0;
                    int x = rand()%30;
                    if (x < 20 && x>29 ) x=0;
                    PowerUpTab[j+yBombe-rayon][xBombe] = x;

                }
                if (yBombe== 1){
                    for (k=0;k<=rayon;k++)
                    {
                        if(tableau[yBombe+k][xBombe] == 1)tableau[yBombe+k][xBombe]  = 0;
                    }
                }
                /*if ((*InvisibiliteTimerval) == 100)
                {
                    printf("test0");*/
                printf("x %s",j+BombeY[i]-rayon == y_perso);
                if ((j+BombeY[i]-rayon == y_perso && BombeX[i] == x_perso) || (j+BombeX[i]-rayon == x_perso && BombeY[i] == y_perso)){
                    printf("test1");
                    (*nb_vie)--;
                    AffichageItem(RT,CT,*nb_vie,nb_Bombe_max,rayon,delta_perso,MenuPerso,player,0);
                    if (nb_vie == 0 )
                    {
                        allegro_message("Vous avez perdu");
                        allegro_exit();
                        exit(EXIT_FAILURE);
                    }
                }
                //}

            }
            PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
            //AffichageItem(RT,CT,*nb_vie,nb_Bombe_max,rayon,delta_perso,MenuPerso,player,0);
            AffichageItem(RT,CT,*nb_vie,nb_Bombe_max,rayon,delta_perso,MenuPerso,player,xorigin);
            PowerUpAffichage(PowerUpTab,origin,RT,CT);


            if(*nb_Bombe!= 0)(*nb_Bombe)--;
        }
        if (BombeTimer[i] == timeInfos->tm_sec && BombeTimer[i] != 0)
        {
            BombeEffectInv(BombeX[i],BombeY[i],rayon,tableau,BombeX,BombeY,RT,origin);

        }
    }
}

//desaffichage des bombes
void BombeEffectInv(int x,int y,int rayon,int *tableau[21][21],int BombeX[5],int BombeY[5],int RT,int origin)
{
    int i,j;
    BITMAP *image;
    char adress[100];
    for(i=0;i<2*rayon+1;i++)
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
void V2Bombes(int (*BombeX)[5],int (*BombeY)[5],int (*BombeTimer)[5],int (*tableau)[21][21],int rayon)
{
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    int i,j,k;
    int RT = 30,CT = 21,origin = 5;
    int xpos, ypos;
    for (i=0;i<5;i++)
    {
        if ((*BombeTimer[i])== timeInfos->tm_sec && (*BombeTimer[i]) != 0) //affichage du rayon de la bombe
        {
            BombeEffect((*BombeX)[i],(*BombeY)[i],rayon,tableau,RT,CT,origin);
        }
        if ((*BombeTimer)[i] + 1 == timeInfos->tm_sec && (*BombeTimer)[i] != 0) //transformation des cases rouge (type 1) en case grise (type 0)
        {
            for (j=0;j<=(2*rayon)+2;j++)
            {
                printf("x = %d\n",(*tableau)[(*BombeX)[i]+j-rayon][(*BombeY)[i]]);
                printf("y = %d\n",(*tableau)[(*BombeX)[i]][(*BombeY)[i]+j-rayon]);
                if ((*tableau)[(*BombeX)[i]+j-rayon][(*BombeY)[i]] == 1) ((*tableau)[(*BombeX)[i]+j-rayon][(*BombeY)[i]]) = 0;
                if ((*tableau)[(*BombeX)[i]][(*BombeY)[i]+j-rayon] == 1) ((*tableau)[(*BombeX)[i]][(*BombeY)[i]+j-rayon]) = 0;
            }
        }
        if ((*BombeTimer)[i] + 2 == timeInfos->tm_sec && (*BombeTimer)[i] != 0)
        {

            BombeEffectInv((*BombeX)[i],(*BombeY)[i],rayon,tableau,BombeX,BombeY,RT,origin); //deaffichage du rayon de la bombe

        }
    }
}
