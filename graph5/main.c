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

void timer()
{
    BITMAP *image;
    char adress[100];
    sprintf(adress, "image/%d/chrono.bmp",RT);
    image=load_bitmap(adress,NULL);
    blit(image,screen,0,0,RT*18,0,image->w, image->h);
    sprintf(adress, "image/%d/brick grey.bmp",RT);
    image=load_bitmap(adress,NULL);
    blit(image,screen,0,0,RT*19,0,image->w, image->h);
    blit(image,screen,0,0,RT*20,0,image->w, image->h);
    if (timerval == 60)
    {
        timerminutes++;
        timerval = 0;
    }
    textprintf_ex(screen,font,RT*19,RT/2,makecol(0,0,0),-1,"%d:%02d",timerminutes,timerval);
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
    int x_perso = 1;
    int y_perso = 1;
    int delta_perso = 1;

    int BombeX[5] = {0};
    int BombeY[5] = {0};
    int BombeTimer[5] = {0};
    int nb_Bombe= 0;
    int rayon = 3;
    int i,j;


    Create(rectangle,1,CT); //0 niveau vide 1 niveau basique, 2 niveau 2... >4 niveau al�atoire
    //affichage(rectangle,CT);



    // initialisation allegro obligatoire
    allegro_init();

    // pour disposer du clavier
    install_keyboard();

    // d�finir un mode graphique
    set_color_depth(desktop_color_depth());
    if (RT == 40) set_gfx_mode(GFX_AUTODETECT_WINDOWED,RT*CT,RT*CT,0,0);
    if (RT == 30) set_gfx_mode(GFX_AUTODETECT_WINDOWED,RT*CT+10,RT*CT,0,0);

    AffichageAllegro(rectangle,0,RT,CT); // affichage de labyrinthe
    PersoAffichage(x_perso,y_perso,RT);

    install_int_ex(timer,BPS_TO_TIMER(1));

    while (!key[KEY_ESC])
    {
        if (key[KEY_RIGHT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, 1,0,BombeX,BombeY,RT);
        if (key[KEY_LEFT]) x_perso = PersoDeplacementX(rectangle,x_perso, y_perso, delta_perso, -1,0,BombeX,BombeY,RT);
        if (key[KEY_UP]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,-1,BombeX,BombeY,RT);
        if (key[KEY_DOWN]) y_perso = PersoDeplacementY(rectangle,x_perso, y_perso, delta_perso, 0,1,BombeX,BombeY,RT);
        if (key[KEY_SPACE])
        {
            printf("%d\n",nb_Bombe);
            BombeX[nb_Bombe] = x_perso;
            BombeY[nb_Bombe] = y_perso;
            time_t timestamp = time( NULL );
            struct tm * timeInfos = localtime( & timestamp );
            BombeTimer[nb_Bombe] = timeInfos->tm_sec+10;
            if (BombeTimer[nb_Bombe]>= 60) BombeTimer[nb_Bombe] = BombeTimer[nb_Bombe] - 60;
            AfffichagePosition(rectangle,x_perso,y_perso,RT);
            BombePlace(x_perso,y_perso,RT);
            PersoAffichage(x_perso,y_perso,RT);
            nb_Bombe++;
            Sleep(300);
        }
        time_t timestamp = time( NULL );
        struct tm * timeInfos = localtime( & timestamp );
        for (i=0;i<5;i++)
        {
            if (BombeTimer[i] == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] != 0)
            {
                if(rectangle[BombeY[i]][BombeX[i]] == 0) BombeEffect(BombeX[i],BombeY[i],rayon,rectangle,RT);
            }
            if (BombeTimer[i]+1 == timeInfos->tm_sec && BombeTimer[i] != 0 && BombeX[i] !=0)
            {
                for (j=0;j<=2*rayon+1;j++)
                {
                    if (rectangle[BombeY[i]][j+BombeX[i]-rayon] == 1) rectangle[BombeY[i]][j+BombeX[i]-rayon] = 0;
                    if (rectangle[j+BombeY[i]-rayon][BombeX[i]] == 1) rectangle[j+BombeY[i]-rayon][BombeX[i]] = 0;
                    if ((j+BombeY[i]-rayon == y_perso && BombeX[i] == x_perso) || (j+BombeX[i]-rayon == x_perso && BombeY[i] == y_perso))
                    {
                        allegro_message("Vous avez perdu");
                        allegro_exit();
                        exit(EXIT_FAILURE);
                    }

                }
                BombeEffectInv(BombeX[i],BombeY[i],rayon,rectangle,BombeX,BombeY,RT);
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
