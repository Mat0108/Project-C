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
int valeur=0;
void timer()
{
    BITMAP *image;
    image=load_bitmap("image/chrono.bmp",NULL);
    blit(image,screen,0,0,40*18,0,image->w, image->h);
    image=load_bitmap("image/brick grey.bmp",NULL);
    blit(image,screen,0,0,40*19,0,image->w, image->h);
    textprintf_ex(screen,font,770,20,makecol(0,0,0),-1,"%03d",valeur);
    valeur++;
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
    int valeur = 0;
    int valeur2 = 0;
    int couleur;
    couleur=makecol(255,255,0);
    BITMAP *image;


    Create(rectangle,1); //0 niveau vide 1 niveau basique, 2 niveau 2... >4 niveau aléatoire
    affichage(rectangle);



    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();

    // définir un mode graphique
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,CT*RT,CT*RT,0,0);

    AffichageAllegro(rectangle,0); // affichage de labyrinthe




    PersoAffichage(x_perso,y_perso);

    while (!key[KEY_ESC])
    {
        if (key[KEY_RIGHT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0);
        if (key[KEY_LEFT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0);
        if (key[KEY_UP]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1);
        if (key[KEY_DOWN]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1);
        install_int_ex(timer,BPS_TO_TIMER(1));
    }
    // attend une touche pour quitter (similaire getch() de conio.h)
    readkey();

    return 0;

}
//attention ne pas oublier !
END_OF_MAIN();
