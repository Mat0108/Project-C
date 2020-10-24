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
    blit(image,screen,0,0,RT*(18+origin),0,image->w, image->h);
    sprintf(adress, "image/%d/brick grey.bmp",RT);
    image=load_bitmap(adress,NULL);
    blit(image,screen,0,0,RT*(19+origin),0,image->w, image->h);
    blit(image,screen,0,0,RT*(20+origin),0,image->w, image->h);
    if (timerval == 60)
    {
        timerminutes++;
        timerval = 0;
    }
    textprintf_ex(screen,font,RT*(19+origin),RT/2,makecol(0,0,0),-1,"%d:%02d",timerminutes,timerval);
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
void Quitter()
{
    allegro_exit();
    exit(EXIT_FAILURE);
}
int main()
{
    int rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable
    int choix_perso = 1; //Pour changer le perso affiché
    int x_perso = 1;
    int y_perso = 1;
    int delta_perso = 1;

    int BombeX[5] = {0};
    int BombeY[5] = {0};
    int BombeTimer[5] = {0};
    int nb_Bombe= 0;

    int rayon = 3;
    int i,j,k;

    int MenuBase = 1;
    int MenuNiveau = 0;
    int MenuPerso = 0;
    int nb_Bombe_max = 3;
    int nb_vie = 3;

    Create(rectangle,0,CT); //0 niveau vide 1 niveau basique, 2 niveau 2... >4 niveau aléatoire
    //affichage(rectangle,CT);



    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();
    install_mouse();


    // définir un mode graphique
    set_color_depth(32);
    int Ecran_X = RT*CT+RT*origin;
    int Ecran_Y = RT*CT;
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,Ecran_X,Ecran_Y,0,0);

    AffichageMenu(RT,CT,origin);
    AffichageAllegro(rectangle,0,RT,CT,origin); // affichage de labyrinthe

    show_mouse(screen);
    while (MenuBase == 1)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuBase = 0;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,1);
    AffichageNiveau(RT,10,origin);
    while (MenuNiveau == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuNiveau = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuNiveau = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuNiveau = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) MenuNiveau = 4;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) MenuNiveau = 5;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*13 && mouse_y<=RT*14.5 && mouse_x<= RT*5 ) Quitter();
    }
    Create(rectangle,MenuNiveau,CT);
    AffichageAllegro(rectangle,1,RT,CT,origin);
    AffichageMenuInv(RT,CT,origin,1);
    AffichagePerso(RT,CT,origin);
    while (MenuPerso== 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuPerso = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuPerso = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuPerso = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) MenuPerso = 4;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) Quitter();
    }
    PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
    AffichageMenuInv(RT,CT,origin,1);
    AffichageItem(RT,CT,nb_vie,nb_Bombe_max);

    install_int_ex(timer,BPS_TO_TIMER(1));

    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0,BombeX,BombeY,RT,MenuPerso,origin);
        if (key[KEY_LEFT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0,BombeX,BombeY,RT,MenuPerso,origin);
        if (key[KEY_UP]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1,BombeX,BombeY,RT,MenuPerso,origin);
        if (key[KEY_DOWN]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1,BombeX,BombeY,RT,MenuPerso,origin);
        if (key[KEY_SPACE])
        {
            BombeX[nb_Bombe] = x_perso;
            BombeY[nb_Bombe] = y_perso;
            time_t timestamp = time( NULL );
            struct tm * timeInfos = localtime( & timestamp );
            BombeTimer[nb_Bombe] = timeInfos->tm_sec+10;
            if (BombeTimer[nb_Bombe]>= 60) BombeTimer[nb_Bombe] = BombeTimer[nb_Bombe] - 60;
            AfffichagePosition(rectangle,x_perso,y_perso,RT,origin);
            BombePlace(x_perso,y_perso,RT,origin);
            PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
            nb_Bombe++;
            Sleep(300);
        }
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        for (i=0;i<5;i++)
        {
            if (BombeTimer[i] == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] != 0)
            {
                if(rectangle[BombeY[i]][BombeX[i]] == 0) BombeEffect(BombeX[i],BombeY[i],rayon,rectangle,RT,origin);
            }
            if (BombeTimer[i]+1 == timeInfos->tm_sec && BombeTimer[i] != 0)
            {
                for (j=0;j<=2*rayon+1;j++)
                {
                    if (rectangle[BombeY[i]][j+BombeX[i]-rayon] == 1) rectangle[BombeY[i]][j+BombeX[i]-rayon] = 0;
                    if (rectangle[j+BombeY[i]-rayon][BombeX[i]] == 1 && BombeY[i]-rayon>0) rectangle[j+BombeY[i]-rayon][BombeX[i]] = 0;
                    if (BombeY[i] == 1)
                    {
                        for (k=0;k<=rayon;k++)
                        {
                            if(rectangle[BombeY[i]+k][BombeX[i]] == 1)rectangle[BombeY[i]+k][BombeX[i]]  = 0;
                        }
                    }
                    if ((j+BombeY[i]-rayon == y_perso && BombeX[i] == x_perso) || (j+BombeX[i]-rayon == x_perso && BombeY[i] == y_perso))
                    {
                        nb_vie--;
                        if (nb_vie == -1)
                        {
                            allegro_message("Vous avez perdu");
                            allegro_exit();
                            exit(EXIT_FAILURE);
                        }
                        AffichageItem(RT,CT,nb_vie,nb_Bombe_max);
                    }

                }
                BombeEffectInv(BombeX[i],BombeY[i],rayon,rectangle,BombeX,BombeY,RT,origin);
                AffichageItem(RT,CT,nb_vie,nb_Bombe_max);
                nb_Bombe--;
                for (i=0;i<5;i++)
                {
                    if (BombeX[i+1] != 0)
                    {
                        if (i+1<5)
                        {
                            BombeX[i] = BombeX[i+1];
                            BombeY[i] = BombeY[i+1];
                            BombeTimer[i] = BombeTimer[i+1];
                        }
                    }
                    else
                    {
                        BombeX[i] = 0;
                        BombeY[i] = 0;
                        BombeTimer[i] = 0;
                    }
                }
            }
        }
    }
    // attend une touche pour quitter (similaire getch() de conio.h)
    readkey();

    return 0;

}
//attention ne pas oublier !
END_OF_MAIN();
