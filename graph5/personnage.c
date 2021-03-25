#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>
//Animation du personnage
void PersoAnimation(int x,int y,int dx,int dy,int RT,int choix,int typeperso,int origin,int tableau[21][21])
{
    char adress[100],personame[20];
    int i=1,pas = 0.01,delay = 20,sens;
    BITMAP *perso;
    if (typeperso == 1) sprintf(personame, "stitch");
    if (typeperso == 2) sprintf(personame, "pug");
    if (dx != 0)sens = 1;
    if (dy != 0)sens = 2;
    for (i=1;i<30;i++)
    {
        if (dx == -1 || dy == -1) sprintf(adress,"animation/%s/%d/%s_%d_%d.bmp",personame,choix,personame,sens,30-i);
        else sprintf(adress,"animation/%s/%d/%s_%d_%d.bmp",personame,choix,personame,sens,i);
        perso = load_bitmap(adress,NULL);
        if (!perso) printf("\n%s",adress);
        blit(perso,screen,0,0,RT*(x+origin),RT*y,perso->w, perso->h);
        Sleep(delay);
    }
}
//affichege du perso
void PersoAffichage(int x_perso,int y_perso,int RT,int choix,int typeperso,int origin)
{

    char adress[100];
    BITMAP *perso;
    if (typeperso == 1) sprintf(adress, "image/%d/stitch/stitch_%d.bmp",RT, choix);
    if (typeperso == 2) sprintf(adress, "image/%d/pug/pug_%d.bmp",RT, choix);

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
int PersoDeplacement(int tableau[21][21],int *PowerUp[21][21],int *x_perso, int *y_perso, int *delta_perso,int dx, int dy,int BombeX[5],int BombeY[5],int *nb_vie,int *nb_Bombe_max,int *rayon,int item,int RT,int CT, int persochoix,int persotype,int choix,int origin, int *score)
{
    int i;
    int oldx = *x_perso, oldy = *y_perso;
    AffichageAllegro2(tableau,1,RT,CT,origin);
    if (PowerUp[*y_perso+dy][*x_perso+dx]> 19 && PowerUp[*y_perso+dy][*x_perso+dx]< 23 && *nb_Bombe_max<5) {(*nb_Bombe_max)++;*score+=3;}
    if (PowerUp[*y_perso+dy][*x_perso+dx]> 22 && PowerUp[*y_perso+dy][*x_perso+dx]< 26 && *rayon<5) {(*rayon)++;*score+=3;}
    //if (PowerUp[*y_perso+dy][*x_perso+dx]> 25 && PowerUp[*y_perso+dy][*x_perso+dx]< 28 && *delta_perso< 3) (*delta_perso)++;
    if (PowerUp[*y_perso+dy][*x_perso+dx]== 28 && *nb_vie<3) {(*nb_vie)++;printf("%d",*nb_vie);*score+=6;}
    AffichageItem(RT,CT,*nb_vie,*nb_Bombe_max,*rayon,*delta_perso,persochoix,choix,persotype,item);
    PowerUp[*y_perso+dy][*x_perso+dx] = 0;
    if (tableau[*y_perso+dy* *delta_perso][*x_perso+dx* *delta_perso] == 0)
    {
        AffichagePosition(tableau,*x_perso,*y_perso,RT,origin);
        for (i=0;i<5;i++)
        {
            if (BombeX[i]== *x_perso && BombeY[i] ==*y_perso)BombePlace(*x_perso,*y_perso,RT,origin);
        }
        if (dx == 1) {PersoAnimation(*x_perso,*y_perso,1,0,RT,persochoix,persotype,origin,tableau);(*x_perso)++;}
        if (dy == 1) {PersoAnimation(*x_perso,*y_perso,0,1,RT,persochoix,persotype,origin,tableau);(*y_perso)++;}
        if (dx == -1) {PersoAnimation(*x_perso-1,*y_perso,-1,0,RT,persochoix,persotype,origin,tableau);(*x_perso)--;}
        if (dy == -1) {PersoAnimation(*x_perso,*y_perso-1,0,-1,RT,persochoix,persotype,origin,tableau);(*y_perso)--;}
        PersoAffichage(*x_perso,*y_perso,RT,persochoix,persotype,origin);

    }
    return 1;
}
//Creation de la bombe
int BombePlacement(int *BombeX[5],int *BombeY[5], int *BombeTimer[5], int *nb_Bombe,int nb_Bombe_max,int tableau[21][21] ,int x_perso,int y_perso,int RT,int origin,int MenuPerso,int TypePerso)
{
     if (*nb_Bombe < nb_Bombe_max)
    {
        BombeX[*nb_Bombe] = x_perso;
        BombeY[*nb_Bombe] = y_perso;
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        BombeTimer[*nb_Bombe] = timeInfos->tm_sec+3;
        if (BombeTimer[*nb_Bombe]>= 60) BombeTimer[*nb_Bombe] = BombeTimer[*nb_Bombe] - 60;
        AffichagePosition(tableau,x_perso,y_perso,RT,origin);
        BombePlace(x_perso,y_perso,RT,origin);
        PersoAffichage(x_perso,y_perso,RT,MenuPerso,TypePerso,origin);
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
            PersoAffichage(x_perso,y_perso,RT,MenuPerso,1,origin);
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
        AffichagePosition(tableau,x,y+i-rayon,RT,origin);
        if(x+i-rayon >0 ) AffichagePosition(tableau,x+i-rayon,y,RT,origin);
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

void V2Bombes_Affichage(int (*BombeX)[5],int (*BombeY)[5],int (*BombeTimer)[5],int (*tableau)[21][21],int rayon)
{
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    int i,j,k,l;
    int RT = 30,CT = 21,origin = 5;
    int xpos, ypos;
    for (i=0;i<5;i++)
    {
        if ((*BombeTimer[i])+1 == timeInfos->tm_sec && (*BombeTimer[i]) != 0) //affichage du rayon de la bombe
        {
            BombeEffect((*BombeX)[i],(*BombeY)[i],rayon,tableau,RT,CT,origin);
        }
    }

}
int  V2Bombes_Desaffichage(int (*BombeX)[5],int (*BombeY)[5],int (*BombeTimer)[5],int (*tableau)[21][21],int rayon,int *nb_bombe,int x_perso,int y_perso,int *life,int xorigin,int choixperso,int typeperso,int PowerUptab,int InvisibiliteTimerval)
{
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    int RT = 30,origin =5;
    int i,l;

    for (i=0;i<5;i++)
    {
        if ((*BombeTimer)[i] + 2 == timeInfos->tm_sec && (*BombeX)[i] != 0)
        {
            *nb_bombe = *nb_bombe - 1;
            BombeEffectInv((*BombeX)[i],(*BombeY)[i],rayon,tableau,BombeX,BombeY,RT,origin); //deaffichage du rayon de la bombe
            PowerUpAffichage(PowerUptab,origin,RT,21);
            for ( l=0;l<4;l++)
            {
                if ((*BombeX)[l+1] != 0)
                {
                    (*BombeX)[l] = (*BombeX)[l+1];
                    (*BombeY)[l] = (*BombeY)[l+1];
                    (*BombeTimer)[l] =(*BombeTimer)[l+1];
                }
                else
                {
                    (*BombeX)[l] = 0;
                    (*BombeY)[l] = 0;
                    (*BombeTimer)[l] = 0;
                }
            }
            (*BombeX)[4] = 0;
            (*BombeY)[4] = 0;
            (*BombeTimer)[4] = 0;
            return 1;
        }
        return 0;
    }
}

int V2Bombes_Life(int BombeX[5],int BombeY[5],int BombeTimer[5],int rayon,int x_perso,int y_perso,int life,int xorigin,int *score,int valeur)
{
    int i,j;
    int modif = 0;
    BITMAP *image;
    char adress[100];
    int debut = 3;
    int RT = 30;
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    for (j = 0;j<5;j++)
    {
        if (BombeTimer[j]+2== timeInfos->tm_sec && BombeX[j] != 0)
        {

            for (i=0;i<2*rayon+1;i++)
            {
                //printf("\nbx = %d by = %d px = %d py = %d",BombeX-rayon+i,BombeY,x_perso,y_perso);
                //printf("\nbx = %d by = %d px = %d py = %d",BombeX,BombeY-rayon+i,x_perso,y_perso);
                if ((BombeX[j]-rayon+i) == x_perso && BombeY[j] == y_perso) {life--;*score += valeur;printf("\n(%d)",*score);modif = 1;}
                if (BombeX[j] == x_perso && (BombeY[j]-rayon+i) == y_perso){life--;*score += valeur;printf("\n(%d)",*score);modif = 1;}
                if (modif == 1)
                {
                    if (xorigin == 0)
                    {
                        AffichageItemLoad(RT,debut+2,xorigin,life,"PowerUp/Life/LIFE ");
                    }
                    else
                    {
                        AffichageItemLoad(RT,debut+2,xorigin+2,life,"PowerUp/Life/LIFE ");
                        /*sprintf(adress, "image/%d/menu/ligne.bmp",RT);
                        image=load_bitmap(adress,NULL);
                        testload(image,adress);
                        blit(image,screen,0,0,RT*(xorigin),RT*debut,image->w, image->h);*/
                    }
                    if (life == 0)
                    {
                        allegro_message("Vous avez perdu");
                        allegro_exit();
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }
    return life;
}
void V2Bombes_Powerup(int BombeX,int BombeY,int rayon,int *PowerUpTab[21][21],int tableau[21][21],int *score)
{
    int i;
    int origin = 5,RT = 30,CT = 21;
    srand(time(NULL));
    for (i=0;i<2*rayon+1;i++)
    {
        if (tableau[BombeY][i+BombeX-rayon] == 1)
        {
            *score+=2;
            printf("\n%d",*score);
            int x = rand()%30;
            if (x < 20 && x>29 ) x=0;
            PowerUpTab[BombeY][i+BombeX-rayon] = x;
        }
        if (tableau[i+BombeY-rayon][BombeX] == 1)
        {
            *score+=2;
            printf("\n%d",*score);
            int x = rand()%30;
            if (x < 20 && x>29 ) x=0;
            PowerUpTab[i+BombeY-rayon][BombeX] = x;
        }
    }
}
void V2Bombes_Print(int BombeX[5],int BombeY[5],int BombeTimer[5])
{
    int i =0;
    if (BombeX[i]!=0)printf("\n");
    for (i=0;i<5;i++)
    {
        if (BombeX[i]!=0)printf("\n%d eme bombe x=%d y=%d timer=%d",i,BombeX[i],BombeY[i],BombeTimer[i]);
    }
}

