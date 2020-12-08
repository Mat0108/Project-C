#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <allegro/font.h>
#include <allegro/text.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>

/*---------------------------------------------------------------------------------------------------------------------
------------------------------------------------Programme Bomberman----------------------------------------------------
-------------------------Matthieu Barnabé-------Alexandre La Fonta-------Nhat Khoa Tran--------------------------------
-----------------------------------------------------------------------------------------------------------------------
----Liste des bugs : https://docs.google.com/spreadsheets/d/16qRqcISNdt1qFeHDXFJQrD2jtbKLKgxOR5rZJznYJh4/edit#gid=0----
---------------------------------------------------------------------------------------------------------------------*/

int timerval=0;
int timerminutes = 0;

const int RT = 30; //taille d'une image
// IMPORTANT CHANGER LA TAILLE DANS TOUT LES TABLEAUX SI CHANGEMENT(CTRL+R)
const int CT = 21; // taille d'une case graphique
int origin = 5;

//fonction pour afficher un timer au cours de la partie
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

//fonction pour verifier l'existance d'une bitmap
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
    int *rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable

    int x_perso = 1,y_perso = 1,delta_perso = 1,nb_vie = 3,Item = 0;
    int BombeX[5] = {0},BombeY[5] = {0}, BombeTimer[5] = {0}, nb_Bombe= 0,nb_Bombe_max = 1,rayon = 2;  //variable pour le perso 1

    int x_perso2 = 19,y_perso2 = 19,delta_perso2 = 1,nb_vie2 = 3,Item2 = CT+origin;
    int BombeX2[5] = {0},BombeY2[5] = {0}, BombeTimer2[5] = {0}, nb_Bombe2 = 0,nb_Bombe_max2 = 2,rayon2 = 1;  //variable pour le perso 2

    int MenuBase = 1, MenuNiveau = 0,MenuPlayer  = 0,MenuPerso = 0,MenuPerso2 = 0, *PowerUpTab[21][21] = {0}; //variable pour les bombes
    int InvisibiliteOn = 0,InvisibiliteTimer=0,InvisibiliteTimerval = 100,val = 0; //variable pour le powerup invisibilité pour le perso 1
    int i,j,k,appui_touche = 0;


    Create(rectangle,-1,CT); //Initialisation du labyrinthe
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    //creation de la fenetre d'affichagge Allegro
    int Ecran_X = RT*CT+2*RT*origin+10;
    int Ecran_Y = RT*CT;
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,Ecran_X,Ecran_Y,0,0) != 0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    AffichageMenu(RT,CT,origin); //affichage du choix du menu
    AffichageAllegro(rectangle,0,RT,CT,origin); // affichage de labyrinthe en niveau -1
    show_mouse(screen); //affichage du pointeur de la souris
    Play(RT,CT,origin); //affichage du choix du niveau
    MenuNiveau = ChoixNiveau(rectangle,RT,CT,origin); //choix du niveau
    MenuPlayer = ChoixPlayer(RT,CT,origin); //choix du nombre de perso
    ChoixPerso(x_perso,y_perso,&MenuPerso,x_perso2,y_perso2,&MenuPerso2,RT,CT,origin,MenuPlayer);//choix des persos
    AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso,MenuPerso,1,Item); //affichage des powerup du perso 1
    if (MenuPlayer == 2) AffichageItem(RT,CT,nb_vie2,nb_Bombe_max2,rayon2,delta_perso2,MenuPerso2,2,Item2);//affichage des powerup du perso 2
    install_int_ex(timer,BPS_TO_TIMER(1)); //initialisation du timer


    while (!key[KEY_ESC])//boucle d'animation
    {
        //if pour le deplacment et le posement de la bombe du perso 1
        if (key[KEY_D])  appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,1,0,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,Item,RT,CT,MenuPerso,1,origin);
        if (key[KEY_A])  appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,-1,0,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,Item,RT,CT,MenuPerso,1,origin);
        if (key[KEY_W])  appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,0,-1,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,Item,RT,CT,MenuPerso,1,origin);
        if (key[KEY_S])  appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso,&y_perso,&delta_perso,0,1,BombeX,BombeY,&nb_vie,&nb_Bombe_max,&rayon,Item,RT,CT,MenuPerso,1,origin);
        if (key[KEY_SPACE]) appui_touche = BombePlacement(&BombeX,&BombeY,&BombeTimer,&nb_Bombe,nb_Bombe_max,rectangle,x_perso,y_perso,RT,origin,MenuPerso);

        V2Bombes_Affichage(BombeX,BombeY,BombeTimer,(int *)rectangle,rayon);
        for(int bombe_i=0;bombe_i<5;bombe_i++)
        {
            if(BombeTimer[bombe_i]!=0)
            {
                for(int bombe_j = 0;bombe_j<=2*rayon+2;bombe_j++)
                {
                    if (rectangle[BombeX[bombe_i]][BombeY[bombe_i]-rayon+bombe_j] == 1) rectangle[BombeX[bombe_i]][BombeY[bombe_i]-rayon+bombe_j] =0;
                }
            }
        }
        V2Bombes_desaffichage(&BombeX,&BombeY,&BombeTimer,(int *)rectangle,rayon);
        //BombeEffect4(&BombeX,&BombeY,&BombeTimer,rectangle,&PowerUpTab,x_perso,y_perso,&nb_vie,nb_Bombe_max,&nb_Bombe,rayon,delta_perso,RT,CT,origin,MenuPerso,1,Item,&InvisibiliteTimerval);

        //if pour le deplacment et le posement de la bombe du perso 2
        if (key[KEY_RIGHT] && MenuPlayer == 2) appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso2,&y_perso2,&delta_perso2,1,0,BombeX2,BombeY2,&nb_vie2,&nb_Bombe_max2,&rayon2,Item2,RT,CT,MenuPerso2,2,origin);
        if (key[KEY_LEFT] && MenuPlayer == 2) appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso2,&y_perso2,&delta_perso2,-1,0,BombeX2,BombeY2,&nb_vie2,&nb_Bombe_max2,&rayon2,Item2,RT,CT,MenuPerso2,2,origin);
        if (key[KEY_UP] && MenuPlayer == 2) appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso2,&y_perso2,&delta_perso2,0,-1,BombeX2,BombeY2,&nb_vie2,&nb_Bombe_max2,&rayon2,Item2,RT,CT,MenuPerso2,2,origin);
        if (key[KEY_DOWN] && MenuPlayer == 2) appui_touche = PersoDeplacement(rectangle,&PowerUpTab,&x_perso2,&y_perso2,&delta_perso2,0,1,BombeX2,BombeY2,&nb_vie2,&nb_Bombe_max2,&rayon2,Item2,RT,CT,MenuPerso2,2,origin);
        if (key[KEY_ENTER] && MenuPlayer == 2) appui_touche = BombePlacement(&BombeX2,&BombeY2,&BombeTimer2,&nb_Bombe2,nb_Bombe_max2,rectangle,x_perso2,y_perso2,RT,origin,MenuPerso2);

        //BombeEffect4(&BombeX2,&BombeY2,&BombeTimer2,rectangle,&PowerUpTab,x_perso2,y_perso2,&nb_vie2,nb_Bombe_max2,&nb_Bombe2,rayon2,delta_perso2,RT,CT,origin,MenuPerso2,2,Item2,&InvisibiliteTimerval);
        /*AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso,MenuPerso,1,Item);
        if (MenuPlayer == 2) AffichageItem(RT,CT,nb_vie2,nb_Bombe_max2,rayon2,delta_perso2,MenuPerso2,2,Item2);

        //Powerup Invisibilité (purement visuelle)
        if (key[KEY_ENTER_PAD]) Invisibilite_Activable(&InvisibiliteOn,&InvisibiliteTimerval,InvisibiliteTimer,Item,RT);
        Invisibilite_Update(&InvisibiliteTimerval,InvisibiliteTimer,Item,RT);
        */
        //permet l'appui de plusieurs touches en même temps
        if (appui_touche == 1){
            appui_touche = 0;
            Sleep(300);
        }
    }
    readkey();
    return 0;
}
//attention ne pas oublier !
END_OF_MAIN();
