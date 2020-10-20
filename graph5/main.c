#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>

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
    int couleur;
    couleur=makecol(255,255,255);
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

    AffichageAllegro(rectangle); // affichage de labyrinthe


    //Chronometre
    start :
            /*printf("\n\nappuyez sur une touche pour lancer le chronometre.\n");
            system("PAUSE");*/
            repere1 :
            system("cls");
            textprintf_ex(screen,font,775,20,couleur,-1,"%03d",valeur);
            valeur++;
            Sleep(1000); //le prog attend une seconde
            image=load_bitmap("image/brick grey.bmp",NULL);
            blit(image,screen,0,0,775,0,image->w, image->h);
            goto repere1; //renvoie au repere1 pour ajouter une seconde

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
