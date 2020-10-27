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

    int rayon = 1;
    int i,j,k;

    int MenuBase = 1;
    int MenuNiveau = 0;
    int MenuPerso = 0;
    int nb_Bombe_max = 1;
    int nb_vie = 3;

    int PowerUpTab[21][21] = {0};




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
    Sleep(500);
    while (MenuNiveau == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuNiveau = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuNiveau = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuNiveau = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) MenuNiveau = 4;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) MenuNiveau = 5;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*13 && mouse_y<=RT*14.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,1);
    Sleep(500);
    AffichagePerso(RT,CT,origin);
    Create(rectangle,MenuNiveau,CT);
    AffichageAllegro(rectangle,1,RT,CT,origin);
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
    Sleep(50);
    AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);

    install_int_ex(timer,BPS_TO_TIMER(1));
    AffichageAllegro2(rectangle,1,RT,CT,origin);
    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT])
        {
            if (PowerUpTab[y_perso][x_perso+1] !=0) printf("\n%d",PowerUpTab[y_perso][x_perso+1]);
            if (PowerUpTab[y_perso][x_perso+1]> 19 && PowerUpTab[y_perso][x_perso+1]< 23 && nb_Bombe_max<5) nb_Bombe_max++;
            if (PowerUpTab[y_perso][x_perso+1]> 22 && PowerUpTab[y_perso][x_perso+1]< 26 && rayon<5) rayon++;
            if (PowerUpTab[y_perso][x_perso+1]> 25 && PowerUpTab[y_perso][x_perso+1]< 28 && delta_perso< 3) delta_perso++;
            if (PowerUpTab[y_perso][x_perso+1]= 28 && nb_vie<3) nb_vie++;
            AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);
            PowerUpTab[y_perso][x_perso+1] = 0;
            x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0,BombeX,BombeY,RT,MenuPerso,origin);
        }
        if (key[KEY_LEFT])
        {
            if (PowerUpTab[y_perso][x_perso-1] !=0) printf("\n%d",PowerUpTab[y_perso][x_perso+1]);
            if (PowerUpTab[y_perso][x_perso-1]> 19 && PowerUpTab[y_perso][x_perso-1]< 23 && nb_Bombe_max<5) nb_Bombe_max++;
            if (PowerUpTab[y_perso][x_perso-1]> 22 && PowerUpTab[y_perso][x_perso-1]< 26 && rayon<5) rayon++;
            if (PowerUpTab[y_perso][x_perso-1]> 25 && PowerUpTab[y_perso][x_perso-1]< 28 && delta_perso< 3) delta_perso++;
            if (PowerUpTab[y_perso][x_perso-1]= 28 && nb_vie<3) nb_vie++;
            AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);
            PowerUpTab[y_perso][x_perso+1] = 0;
            x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0,BombeX,BombeY,RT,MenuPerso,origin);
        }
        if (key[KEY_UP])
        {
            if (PowerUpTab[y_perso-1][x_perso]> 19 && PowerUpTab[y_perso-1][x_perso]< 23 && nb_Bombe_max<5) nb_Bombe_max++;
            if (PowerUpTab[y_perso-1][x_perso]> 22 && PowerUpTab[y_perso-1][x_perso]< 26 && rayon<5) rayon++;
            if (PowerUpTab[y_perso-1][x_perso]> 25 && PowerUpTab[y_perso-1][x_perso]< 28 && delta_perso< 3) delta_perso++;
            if (PowerUpTab[y_perso-1][x_perso]= 28 && nb_vie<3) nb_vie++;
            AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);
            PowerUpTab[y_perso][x_perso+1] = 0;
            y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1,BombeX,BombeY,RT,MenuPerso,origin);
        }
        if (key[KEY_DOWN])
        {
            if (PowerUpTab[y_perso+1][x_perso]> 19 && PowerUpTab[y_perso+1][x_perso]< 23 && nb_Bombe_max<5) nb_Bombe_max++;
            if (PowerUpTab[y_perso+1][x_perso]> 22 && PowerUpTab[y_perso+1][x_perso]< 26 && rayon<5) rayon++;
            if (PowerUpTab[y_perso+1][x_perso]> 25 && PowerUpTab[y_perso+1][x_perso]< 28 && delta_perso< 3) delta_perso++;
            if (PowerUpTab[y_perso+1][x_perso]= 28 && nb_vie<3) nb_vie++;
            AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);
            PowerUpTab[y_perso][x_perso+1] = 0;
            y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1,BombeX,BombeY,RT,MenuPerso,origin);
        }
        if (key[KEY_SPACE])
        {
            BombeX[nb_Bombe] = x_perso;
            BombeY[nb_Bombe] = y_perso;
            time_t timestamp = time( NULL );
            struct tm * timeInfos = localtime( & timestamp );
            BombeTimer[nb_Bombe] = timeInfos->tm_sec+5;
            if (BombeTimer[nb_Bombe]>= 60) BombeTimer[nb_Bombe] = BombeTimer[nb_Bombe] - 60;
            AfffichagePosition(rectangle,x_perso,y_perso,RT,origin);
            BombePlace(x_perso,y_perso,RT,origin);
            PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
            nb_Bombe++;
            Sleep(300);
        }
        if (key[KEY_ENTER])PowerUpGeneration(x_perso,y_perso,origin,RT);
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        for (i=0;i<5;i++)
        {
            if (BombeTimer[i] == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] != 0)
            {
                if(rectangle[BombeY[i]][BombeX[i]] == 0) BombeEffect(BombeX[i],BombeY[i],rayon,rectangle,RT,CT,origin);
            }
            if (BombeTimer[i]+1 == timeInfos->tm_sec && BombeTimer[i] != 0)
            {
                srand(time(NULL));
                for (j=0;j<2*rayon+1;j++)
                {
                    if (rectangle[BombeY[i]][j+BombeX[i]-rayon] == 1)
                    {
                        rectangle[BombeY[i]][j+BombeX[i]-rayon] = 0;
                        int x = rand()%30;
                        if (x < 20 && x>29 ) x=0;

                        PowerUpTab[BombeY[i]][j+BombeX[i]-rayon] = x;
                    }
                    if (rectangle[j+BombeY[i]-rayon][BombeX[i]] == 1)
                    {
                        rectangle[j+BombeY[i]-rayon][BombeX[i]] = 0;
                        int x = rand()%30;
                        if (x < 20 && x>29 ) x=0;
                        PowerUpTab[j+BombeY[i]-rayon][BombeX[i]] = x;
                    }

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
                        AffichageItem(RT,CT,nb_vie,nb_Bombe_max);
                        if (nb_vie == 0)
                        {
                            allegro_message("Vous avez perdu");
                            allegro_exit();
                            exit(EXIT_FAILURE);
                        }
                    }

                }
                BombeEffectInv(BombeX[i],BombeY[i],rayon,rectangle,BombeX,BombeY,RT,origin);
                AffichageItem(RT,CT,nb_vie,nb_Bombe_max,rayon,delta_perso);
                PowerUpAffichage(PowerUpTab,origin,RT,CT);
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
