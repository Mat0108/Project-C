#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

int main()
{

    // IMPORTANT CHANGER LA TAILLE DANS TOUT LES TABLEAUX SI CHANGEMENT(CTRL+R)
    const int RT = 21; //taille rectangle
    const int CT = 40; // taille d'une case graphique
    int rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable
    int i,j;
    Create(rectangle);
    affichage(rectangle);





    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();

    // définir un mode graphique
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,CT*RT,CT*RT,0,0);


    AffichageAllegro(rectangle); // affichage de labyrinthe

        // attend une touche pour quitter (similaire getch() de conio.h)
    readkey();

    return 0;

}
//attention ne pas oublier !
END_OF_MAIN();
