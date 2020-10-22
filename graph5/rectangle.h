#ifndef _rectangle_h
#define _rectangle_h
#include <stdio.h>
#include <stdlib.h>
void Load(int *tableau[21][21],FILE *niveau,int CT);
void MethodeCreate(int *tableau[21][21],int Choix, int CT);
void Create(int *tableau[21][21],int choixniveau, int CT);
void affichage(int *tableau[21][21],int CT);
void AffichageAllegro(int tableau[21][21],int debut,int RT,int CT);
void AfffichagePosition(int tableau[21][21],int x_perso,int y_perso,int RT);


#endif
