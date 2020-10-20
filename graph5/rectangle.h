#ifndef _rectangle_h
#define _rectangle_h
#include <stdio.h>
#include <stdlib.h>
void Load(int *tableau[21][21],FILE *niveau);
void MethodeCreate(int *tableau[21][21],int Choix);
void Create(int *tableau[21][21],int choixniveau);
void affichage(int tableau[21][21]);
void AffichageAllegro(int tableau[21][21],int debut);


#endif
