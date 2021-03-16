#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>




//bouton quitter
void Quitter()
{
    allegro_exit();
    exit(EXIT_FAILURE);
}
//bouton play
void Play(int RT,int CT,int origin)
{
    int MenuBase = 0;;
    while (MenuBase == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuBase = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuLoad();
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,0);
    AffichageNiveau(RT,10,origin);
    Sleep(300);
}

//Affichage du niveau en jeu
void AffichageNiveauJeu(int MenuNiveau)
{
    BITMAP *image;
    char adress[100];

    sprintf(adress, "image/%d/menu/v2 niveau %d.bmp",30,MenuNiveau);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,30,10,image->w, image->h);
}
//bouton choix niveau
int ChoixNiveau(int tableau[21][21],int RT,int CT,int origin)
{
    int MenuNiveau = 0;
    while (MenuNiveau == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuNiveau = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuNiveau = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) MenuNiveau = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) MenuNiveau = 4;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*13 && mouse_y<=RT*14.5 && mouse_x<= RT*5 ) MenuNiveau = 5;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*15 && mouse_y<=RT*16.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,0);
    Sleep(300);

    AffichagePlayer(RT,CT,origin);
    Create(tableau,MenuNiveau,CT);
    AffichageAllegro(tableau,1,RT,CT,origin);
    return MenuNiveau;
}
//bouton choix mode de jeu
int ChoixPlayer(int RT,int CT,int origin)
{
    int MenuPlayer = 0;
    while (MenuPlayer == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuPlayer = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuPlayer = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,0);
    AffichageTypePerso(RT,CT,1,MenuPlayer);
    if (MenuPlayer == 2) AffichageTypePerso(RT,CT,1+origin+21,MenuPlayer);
    Sleep(300);
    return MenuPlayer;
}
//bouton choix type perso (stitch ou pug)

void ChoixTypePerso(int *ChoixPerso1,int *ChoixPerso2,int nbplayer,int RT,int CT,int origin)
{
    int condition = 1;
    while (condition == 1)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) *ChoixPerso1 = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) *ChoixPerso1 = 2;

        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x>= RT*(CT+origin )) *ChoixPerso2 = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x>= RT*(CT+origin )) *ChoixPerso2 = 2;

        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 ) Quitter();
        if (*ChoixPerso1 != 0 &&( *ChoixPerso2 !=0 || nbplayer != 2)) condition = 0;
    }
    AffichageMenuInv(RT,CT,origin,0);
    AffichagePerso(RT,CT,1,1,1,*ChoixPerso1);
    if(*ChoixPerso2 != 0)AffichagePerso(RT,CT,1+origin+21,2,*ChoixPerso2);
    Sleep(300);
}

//bouton choix perso
void ChoixPerso(int x_perso,int y_perso,int *MenuPerso, int x_perso2,int y_perso2 ,int *MenuPerso2,int RT,int CT,int origin,int MenuPlayer,int typeperso1,int typeperso2)
{
    int varaffichage = 1, condition = 1;

    while (condition == 1)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) *MenuPerso = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) *MenuPerso = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) *MenuPerso = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) *MenuPerso = 4;

        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x>= RT*(CT+origin )) *MenuPerso2 = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x>= RT*(CT+origin )) *MenuPerso2 = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x>= RT*(CT+origin ) ) *MenuPerso2 = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x>= RT*(CT+origin ) ) *MenuPerso2 = 4;

        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*13 && mouse_y<=RT*14.5 ) Quitter();

        if (*MenuPerso == *MenuPerso2&& *MenuPerso !=0 && varaffichage == 1 && typeperso1 == typeperso2)
        {
            allegro_message("Merci de selectionner deux perso differents  !!!");
            varaffichage = 0;
        }
        if (*MenuPerso != 0) PersoAffichage(x_perso,y_perso,RT,*MenuPerso,typeperso1,origin);
        if (*MenuPerso2 != 0 && MenuPlayer == 2) PersoAffichage(24,19,RT,*MenuPerso2,typeperso2,0);
        if ((*MenuPerso != 0 && (*MenuPerso2 != 0 || MenuPlayer != 2))&& (*MenuPerso != *MenuPerso2 || typeperso1 != typeperso2))condition = 0;
    }
    AffichageMenuInv(RT,CT,origin,CT+origin);
    AffichageMenuInv(RT,CT,origin,0);
    Sleep(500);
}



void AffichageLigne(float x,float y,int RT)
{
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/menu/ligne.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*(x+1),RT*y,image->w, image->h);
    sprintf(adress, "image/%d/menu/ligne2.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*(x-4),RT*y,image->w, image->h);
}
void AffichageItemLoad(int RT,int debut,float x,int choix,char adress2[100])
{
    BITMAP *image;
    char adress[100];

    sprintf(adress, "image/%d/menu/%s%d.bmp",RT,adress2,choix);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*x,RT*debut,image->w, image->h);
}
//affichages des powerups des persos
void AffichageItem(int RT,int CT,int nb_vie,int nb_bombes,int rayon ,int speed,int choixperso,int perso,int typeperso,int xorigin)
{
    BITMAP *image;
    char adress[100];
    int debut = 5;
    int delta = 2;
    AffichageLigne(3+xorigin,debut,RT);
    if (xorigin == 0)
    {
        AffichageItemLoad(RT,debut,xorigin,nb_vie,"PowerUp/Life/LIFE ");
        AffichageItemLoad(RT,debut-2,1,perso,"v2 player ");
        AffichageLigne(2,debut,RT);

    }
    else
    {
        AffichageItemLoad(RT,debut,xorigin+2,nb_vie,"PowerUp/Life/LIFE ");
        AffichageItemLoad(RT,debut-2,xorigin,perso,"v2 player ");
        sprintf(adress, "image/%d/menu/ligne.bmp",RT);
        image=load_bitmap(adress,NULL);
        testload(image,adress);
        blit(image,screen,0,0,RT*(xorigin),RT*debut,image->w, image->h);
    }



    AffichageLigne(3+xorigin,debut+delta,RT);
    AffichageItemLoad(RT,debut+delta,xorigin,nb_bombes,"PowerUp/Bombe/Bombe ");

    AffichageLigne(3+xorigin,debut+2*delta,RT);
    AffichageItemLoad(RT,debut+2*delta,xorigin,rayon,"PowerUp/Rayon/Rayon ");

    AffichageLigne(3+xorigin,debut+3*delta,RT);
    AffichageItemLoad(RT,debut+3*delta,xorigin,speed,"PowerUp/Speed/Speed ");

    if (xorigin == 0){
        AffichageItemLoad(RT,debut+6.5*delta,xorigin,perso,"Touche ");
        if (typeperso == 1) AffichageItemLoad(RT,debut+6.5*delta,xorigin,choixperso,"stitch/stitch_gris_");
        if (typeperso == 2) AffichageItemLoad(RT,debut+6.5*delta,xorigin,choixperso,"pug/pug_gris_");
    }
    else
    {
        AffichageItemLoad(RT,debut+6.5*delta,xorigin+1.3,perso,"Touche ");
        if (typeperso == 1) AffichageItemLoad(RT,debut+6.5*delta,xorigin+2.1,choixperso,"stitch/stitch_gris_");
        if (typeperso == 2) AffichageItemLoad(RT,debut+6.5*delta,xorigin+2.1,choixperso,"pug/pug_gris_");
    }
}

//affichage de la barre d'invisiblilite
void InvisibiliteAffichage(int xorigin,int val,int RT)
{
    BITMAP *image;
    char adress[100];
    int debut = 3;
    int delta = 2;
    sprintf(adress, "image/%d/menu/ligne2.bmp",RT);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,RT*(4.9+xorigin),RT*(debut+4*delta),image->w, image->h);
    sprintf(adress, "image/%d/menu/PowerUp/Invisibilite/Invisibilite %d.bmp",RT,val);
    image=load_bitmap(adress,NULL);
    testload(image,adress);
    blit(image,screen,0,0,0,RT*(debut+4*delta),image->w, image->h);
}
//execution de l'invisibilite
void Invisibilite(int *invisibiliteOn,int InvisibiliteTimer,int xorigin,int RT)
{

    switch(*invisibiliteOn)
    {
    case 0:
        break;
    case 1:;
        *invisibiliteOn = 2;

        InvisibiliteAffichage(xorigin,InvisibiliteTimer,RT);
        break;
    case 2:
        if (InvisibiliteTimer >= 12)
        {
            InvisibiliteAffichage(xorigin,11,RT);
            (*invisibiliteOn ) = 0;
        }
        else
        {
            InvisibiliteAffichage(xorigin,InvisibiliteTimer,RT);
        }
        break;
    }
}
//activation d'invisibilite
void Invisibilite_Activable(int *InvisibiliteOn,int *InvisibiliteTimerval,int InvisibiliteTimer,int val, int RT)
{
    (*InvisibiliteOn) = 1;
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    (*InvisibiliteTimerval) = timeInfos->tm_sec+10;
    if (*InvisibiliteTimerval>59 ) (*InvisibiliteTimerval) = (*InvisibiliteTimerval) -60;
    Invisibilite(InvisibiliteOn,InvisibiliteTimer,val,RT);
}
//update l'invisiblilite
void Invisibilite_Update(int *InvisibiliteTimerval,int InvisibiliteTimer,int val2, int RT)
{
    int val;
    if (*InvisibiliteTimerval != 100 )
    {
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );

        if (*InvisibiliteTimerval>=timeInfos->tm_sec) val = *InvisibiliteTimerval-timeInfos->tm_sec;
        else val = 60-timeInfos->tm_sec+InvisibiliteTimer;

        if (val >= 0 && val <= 11) InvisibiliteAffichage(val2,10-val,RT);
        if (val == 0)
        {
            InvisibiliteAffichage(val2,10,RT);
            Sleep(400);
            InvisibiliteAffichage(val2,11,RT);
            (*InvisibiliteTimerval) = 100;
        }
    }
}


void SaveFichier()
{

}
