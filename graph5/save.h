#ifndef _save_h
#define _save_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
typedef struct Player Player;
struct Player
{
    char nom[50];
    int x;
    int y;
    int type;
    int color;
    int bombe;
    int rayon;
    int vie;
};

typedef struct Bombe Bombe;
struct Bombe
{
    int X[5];
    int Y[5];
    int Timer[5];
};
void writeFile(int tableau[21][21],int powerTab[21][21],Player* perso1,Player* perso2,Bombe* bombe1,Bombe* bombe2,int niveau);
void playerAffichage(Player* perso);
void CharTabtoInt(FILE *file,int *tableau[21][21],int pos);
int extract(int from, int to, char *chaine, char *sousChaine);
void extractPlayer(char text[200], Player * player);
void loadFile(const char *filename,int *tableau[21][21],int *powerUpTab[21][21],Player* perso1,Player* perso2,Bombe* bombe1,Bombe* bombe2,int *niveau);
void AffichageSave();
int MenuLoad();
void ChoixNom(int MenuPlayer,char *player1_nom,char *player2_nom);
void ChoixNomAffichage(char player1[100],char player2[100],int Menuplayer);
#endif // _SAVE_H
