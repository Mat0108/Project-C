#ifndef _personnage_h
#define _personnage_h
void PersoAffichage(int x_perso,int y_perso,int RT,int choix,int typeperso,int origin);
void BombePlace(int x,int y,int RT,int origin);
int PersoDeplacement(int tableau[21][21],int *PowerUp[21][21],int *x_perso, int *y_perso, int *delta_perso,int dx, int dy,int BombeX[5],int BombeY[5],int *nb_vie,int *nb_Bombe_max,int *rayon,int item,int RT,int CT, int persochoix,int persotype,int choix,int origin);
int BombePlacement(int *BombeX[5],int *BombeY[5], int *BombeTimer[5], int *nb_bombe,int nb_Bombe_max,int x_perso,int y_perso,int RT,int origin,int MenuPerso);
void BombeEffect(int x,int y,int rayon,int *tableau[21][21],int RT,int CT,int origin);
void BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation,int RT,int CT,int origin);
void BombeEffect3(int BombeTimer[5],int BombeX[5], int BombeY[5],int rayon, int tableau[21][21],int RT,int CT,int origin);
void BombeEffect4(int *BombeX[5],int *BombeY[5],int *BombeTimer[5],int tableau[21][21],int *PowerUpTab[21][21],int x_perso,int y_perso,int *nb_vie,int nb_Bombe_max,int *nb_Bombe,int rayon,int delta_perso,int RT,int CT,int origin,int MenuPerso,int player,int xorigin,int *InvisibiliteTimerval);
void BombeEffectInv(int x,int y,int rayon,int *tableau[21][21],int BombeX,int BombeY,int RT,int origin);

void V2Bombes_Affichage(int (*BombeX)[5],int (*BombeY)[5],int (*BombeTimer)[5],int (*tableau)[21][21],int rayon);
int V2Bombes_Desaffichage(int (*BombeX)[5],int (*BombeY)[5],int (*BombeTimer)[5],int (*tableau)[21][21],int rayon,int *nb_bombe,int x_perso,int y_perso,int *life,int xorigin,int choixperso,int typeperso,int PowerUptab,int InvisibiliteTimerval);
int V2Bombes_Life(int BombeX[5],int BombeY[5],int BombeTimer[5],int rayon,int x_perso,int y_perso,int life,int xorigin,int *score,int valeur);
void V2Bombes_Powerup(int BombeX,int BombeY,int rayon,int *PowerUpTab[21][21],int tableau[21][21],int *score);
void V2Bombes_Print(int BombeX[5],int BombeY[5],int BombeTimer[5]);

#endif

