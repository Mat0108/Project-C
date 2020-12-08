#ifndef _rectangle_h
#define _rectangle_h
#include <stdio.h>
#include <stdlib.h>
void Load(int *tableau[21][21],FILE *niveau,int CT);
void MethodeCreate(int *tableau[21][21],int Choix, int CT);
void Create(int *tableau[21][21],int choixniveau, int CT);
void affichage(int *tableau[21][21],int CT);
void AffichageAllegro(int tableau[21][21],int debut,int RT,int CT,int origin);
void AffichageAllegro2(int tableau[21][21],int debut,int RT,int CT,int origin);
void AffichagePosition(int tableau[21][21],int x_perso,int y_perso,int RT,int origin);
void AffichageMenuInv(int RT,int CT,int origin,int debut);
void AffichageMenu(int RT,int CT,int origin);
int AffichageNiveau(int RT,int CT,int origin);
void AffichagePlayer(int RT,int CT,int origin);
void AffichagePerso(int RT,int CT, int yposition,int player);


#endif
