#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <allegro/font.h>
#include <allegro/text.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>

#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)
int timerval=0;
int timerminutes = 0;

const int RT = 30; //taille d'une image
// IMPORTANT CHANGER LA TAILLE DANS TOUT LES TABLEAUX SI CHANGEMENT(CTRL+R)
const int CT = 21; // taille d'une case graphique

int origin = 5;
void timer()
{
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/chrono.bmp",RT);
    image=load_bitmap(adress,NULL);
    blit(image,screen,0,0,RT*(9+origin),0,image->w, image->h);
    sprintf(adress, "image/%d/brick grey.bmp",RT);
    image=load_bitmap(adress,NULL);
    blit(image,screen,0,0,RT*(10+origin),0,image->w, image->h);
    blit(image,screen,0,0,RT*(11+origin),0,image->w, image->h);
    if (timerval == 60)
    {
        timerminutes++;
        timerval = 0;
    }
    textprintf_ex(screen,font,RT*(10+origin),RT/2,makecol(0,0,0),-1,"%d:%02d",timerminutes,timerval);
    timerval++;
}
void testload(BITMAP *image,char adress[100])
{
    char nom[100];
    sprintf(nom,"Impossible de trouver l'image ayant  l'adress %s",adress);
     if (!image)
    {
        allegro_message(nom);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

int main()
{
    int rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable

    int x_perso = 1,y_perso = 1,delta_perso = 1,nb_vie = 3;
    int BombeX[5] = {0},BombeY[5] = {0}, BombeTimer[5] = {0}, nb_Bombe= 0,nb_Bombe_max = 1,rayon = 1;  //variable pour le perso 1

    int x_perso2 = 24,y_perso2 = 19,delta_perso2 = 1,nb_vie2 = 3;
    int BombeX2[5] = {0},BombeY2[5] = {0}, BombeTimer2[5] = {0}, nb_Bombe2= 0,nb_Bombe_max2 = 1,rayon2 = 1;  //variable pour le perso 2

    int MenuBase = 1, MenuNiveau = 0,MenuPlayer  = 0,MenuPerso = 0,MenuPerso2 = 0, *PowerUpTab[21][21] = {0};
    int i,j,k;

    Create(rectangle,-1,CT);

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(32);
    int Ecran_X = RT*CT+2*RT*origin+10;
    int Ecran_Y = RT*CT;

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,Ecran_X,Ecran_Y,0,0) != 0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    AffichageMenu(RT,CT,origin);
    AffichageAllegro(rectangle,0,RT,CT,origin); // affichage de labyrinthe
    show_mouse(screen);

    Play(RT,CT,origin);
    MenuNiveau = ChoixNiveau(rectangle,RT,CT,origin);
    MenuPlayer = ChoixPlayer(RT,CT,origin);
    ChoixPerso(x_perso,y_perso,&MenuPerso,x_perso2,y_perso2,&MenuPerso2,RT,CT,origin,MenuPlayer);


    AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso,1,0);
    AffichageItem(RT,CT,nb_vie2,nb_Bombe_max2,rayon2,delta_perso2,2,origin+CT);
    install_int_ex(timer,BPS_TO_TIMER(1));

    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT])  PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,1,0,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,RT,CT,MenuPerso,origin);
        if (key[KEY_LEFT])    PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,-1,0,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,RT,CT,MenuPerso,origin);
        if (key[KEY_UP])       PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,0,-1,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,RT,CT,MenuPerso,origin);
        if (key[KEY_DOWN]) PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,0,1,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,RT,CT,MenuPerso,origin);
        if (key[KEY_SPACE]) BombePlacement(&BombeX,&BombeY,&BombeTimer,&nb_Bombe,nb_Bombe_max,rectangle,x_perso,y_perso,RT,origin,MenuPerso);

        PowerUpGeneration(x_perso,y_perso,origin,RT);
        BombeEffect3(BombeTimer,BombeX,BombeY,rayon,rectangle,RT,CT,origin);
        BombeEffect4(&BombeX,&BombeY,&BombeTimer,rectangle,&PowerUpTab,x_perso,y_perso,&nb_vie,nb_Bombe_max,&nb_Bombe,rayon,delta_perso,RT,CT,origin,MenuPerso);

        }
    readkey();
    return 0;
}
//attention ne pas oublier !
END_OF_MAIN();
