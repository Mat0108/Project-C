#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include <winalleg.h>
#include <windows.h>

void Quitter()
{
    allegro_exit();
    exit(EXIT_FAILURE);
}

void Play(int RT,int CT,int origin)
{
    int MenuBase = 0;;
    while (MenuBase == 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuBase = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,1);
    AffichageNiveau(RT,10,origin);
    Sleep(300);
}
int ChoixNiveau(int tableau[21][21],int RT,int CT,int origin)
{
    int MenuNiveau = 0;
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
    Sleep(300);
    AffichagePerso(RT,CT,origin);
    Create(tableau,MenuNiveau,CT);
    AffichageAllegro(tableau,1,RT,CT,origin);
    return MenuNiveau;
}
int ChoixPerso(int x_perso,int y_perso,int RT,int CT,int origin)
{
    int MenuPerso = 0;
    while (MenuPerso== 0)
    {
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*3 && mouse_y<=RT*4.5 && mouse_x<= RT*5 ) MenuPerso = 1;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*5 && mouse_y<=RT*6.5 && mouse_x<= RT*5 ) MenuPerso = 2;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*7 && mouse_y<=RT*8.5 && mouse_x<= RT*5 ) MenuPerso = 3;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*9 && mouse_y<=RT*10.5 && mouse_x<= RT*5 ) MenuPerso = 4;
        if ( (mouse_b&1 || mouse_b&2) && mouse_y>RT*11 && mouse_y<=RT*12.5 && mouse_x<= RT*5 ) Quitter();
    }
    AffichageMenuInv(RT,CT,origin,1);
    PersoAffichage(x_perso,y_perso,RT,MenuPerso,origin);
    Sleep(50);
    return MenuPerso;
}
