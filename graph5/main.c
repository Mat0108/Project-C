#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

int main()
{

    // IMPORTANT CHANGER LA TAILLE DANS TOUT LES TABLEAUX SI CHANGEMENT(CTRL+R)
    const int RT = 21; //taille rectangle
    const int CT = 40; // taille d'une case graphique
    int rectangle[21][21] = {0}; // 0 case libre, 1 case cassable, 2 case incassable
    int x_perso = 1;
    int y_perso = 1;
    int delta_perso = 1;


    Create(rectangle,1); //0 niveau vide 1 niveau basique, 2 niveau 2... >4 niveau aléatoire
    affichage(rectangle);






    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();

    // définir un mode graphique
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,CT*RT,CT*RT,0,0);

    AffichageAllegro(rectangle); // affichage de labyrinthe

    PersoAffichage(x_perso,y_perso);

    while (!key[KEY_ESC])
    {

        if (key[KEY_RIGHT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0);
        if (key[KEY_LEFT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0);
        if (key[KEY_UP]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1);
        if (key[KEY_DOWN]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1);
    }
    // attend une touche pour quitter (similaire getch() de conio.h)
    readkey();

    return 0;

}
//attention ne pas oublier !
END_OF_MAIN();
