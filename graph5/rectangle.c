#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>


void Create(int *tableau[21][21])
{
    const int RT = 21;
    int i,j;
    srand(time(NULL)); //initiatilisation random
    for(i=0; i<RT;i++)
    {
        tableau[i][0] = 2;
        tableau[i][RT-1] = 2;
        tableau[0][i] = 2;
        tableau[RT-1][i] = 2;
    }
    for (i=1;i<RT-1;i++)
    {
        for (j=1;j<RT-1;j++)
        {
            tableau[i][j] = ((rand()%18)/10);
            if(i%2 == 0 && j%2 == 0) tableau[i][j] = 2;
        }
    }
    for (i=1;i<3;i++)
    {
        tableau[i][1]=0;
        tableau[RT-i-1][1]=0;
        tableau[1][RT-i-1]=0;
        tableau[RT-i-1][RT-2]=0;
    }
    tableau[RT-2][2]=0;
    tableau[2][RT-2]=0;
    tableau[RT-2][RT-3]=0;
    tableau[1][2]=0;

}

void affichage(int tableau[21][21])
{
    int i,j;
    const int RT = 21;
    for (i = 0;i<RT;i++)
    {
        for (j=0;j<RT;j++)
        {
            printf("%d ",tableau[i][j]);
        }
        printf("\n");
    }
}
void AffichageAllegro(int tableau[21][21])
{
    int i,j;
    const int RT = 21;
    for (i = 0;i<RT;i++)
    {
        for (j=0;j<RT;j++)
        {
            switch(tableau[i][j])
            {
            case 0 :
                rectfill(screen,40*(i),40*j,40*(i+1),40*(j+1),makecol(90,205,80)); //rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color)
                break;
            case 1 :
                rectfill(screen,40*(i),40*j,40*(i+1),40*(j+1),makecol(255,55,55));
                break;
            case 2 :
                rectfill(screen,40*(i),40*j,40*(i+1),40*(j+1),makecol(119,129,121));
                break;

            }
        }
    }
}



