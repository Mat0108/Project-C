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
int TimerListBombes[5] = {0};

void timer()
{
    BITMAP *image;
    image=load_bitmap("image/chrono.bmp",NULL);
    blit(image,screen,0,0,40*18,0,image->w, image->h);
    image=load_bitmap("image/brick grey.bmp",NULL);
    blit(image,screen,0,0,40*19,0,image->w, image->h);
    textprintf_ex(screen,font,770,20,makecol(0,0,0),-1,"%03d",timerval);
    timerval++;

}


int main()
{

    // IMPORTANT CHANGER LA TAILLE DANS TOUT LES TABLEAUX SI CHANGEMENT(CTRL+R)
    const int RT = 21; //taille rectangle
    const int CT = 40; // taille d'une case graphique
    int rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable
    int x_perso = 1;
    int y_perso = 1;
    int delta_perso = 1;

    int BombeList[5][3] = {0}; //x,y,timer
    int nb_Bombe= 0;
    int rayon = 1;
    int i,j;


    Create(rectangle,0); //0 niveau vide 1 niveau basique, 2 niveau 2... >4 niveau aléatoire
    affichage(rectangle);



    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();

    // définir un mode graphique
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,CT*RT,CT*RT,0,0);


        nb_Bombe = AffichageAllegro(rectangle,0,BombeList); // affichage de labyrinthe
        PersoAffichage(x_perso,y_perso);

    install_int_ex(timer,BPS_TO_TIMER(1));

    while (!key[KEY_ESC])
    {
        if (key[KEY_RIGHT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0,BombeList);
        if (key[KEY_LEFT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0,BombeList);
        if (key[KEY_UP]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1,BombeList);
        if (key[KEY_DOWN]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1,BombeList);
        if (key[KEY_SPACE])
        {
            nb_Bombe=0;
            while (BombeList[nb_Bombe][0] != 0) BombeList;
            nb_Bombe = AffichageAllegro(rectangle,1,BombeList); // affichage de labyrinthe
            BombeList[nb_Bombe][0] = x_perso;
            BombeList[nb_Bombe][1] = y_perso;
            time_t timestamp = time( NULL );
            struct tm * timeInfos = localtime( & timestamp );
            BombeList[nb_Bombe][2] = timeInfos->tm_sec+10;
            if (BombeList[nb_Bombe][2] >= 60) BombeList[nb_Bombe][2] = BombeList[nb_Bombe][2] - 60;
            PersoAffichage(x_perso,y_perso);
        }
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        for (i=0;i<5;i++)
        {
            if (BombeList[i][2] == timeInfos->tm_sec && BombeList[i][2] != 0)
            {
                BombeEffect(BombeList[i][0],BombeList[i][1],rayon,rectangle);
            }
            if (BombeList[i][2]+1 == timeInfos->tm_sec && BombeList[i][2] != 0)
            {
                for (j=0;j<=2*rayon+1;j++)
                {
                    if(rectangle[BombeList[i][1]][j+BombeList[i][0]-rayon] == 1)rectangle[BombeList[i][1]][j+BombeList[i][0]-rayon]=0;
                    if(rectangle[j+BombeList[i][1]-rayon][BombeList[i][0]] == 1)rectangle[j+BombeList[i][1]-rayon][BombeList[i][0]]=0;
                    /*
                    if (j+BombeList[i][0]-rayon == y_perso || j+BombeList[i][1]-rayon == x_perso)
                    {
                        allegro_message("Vous avez perdu");
                        allegro_exit();
                        exit(EXIT_FAILURE);
                    }
                    */
                }
                BombeEffectInv(BombeList[i][0],BombeList[i][1],rayon,rectangle);
                BombeList[i][0] = 0;
                BombeList[i][1] = 0;
                BombeList[i][2] = 0;
                //nb_Bombe = AffichageAllegro(rectangle,1,BombeList); // affichage de labyrinthe
                //PersoAffichage(x_perso,y_perso);
            }
        }
    }
    // attend une touche pour quitter (similaire getch() de conio.h)
    readkey();

    return 0;

}
//attention ne pas oublier !
END_OF_MAIN();
