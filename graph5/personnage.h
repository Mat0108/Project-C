#ifndef _personnage_h
#define _personnage_h
void PersoAffichage(int x_perso,int y_perso,int RT);
void BombePlace(int x,int y,int RT);
int PersoDeplacementX(int tableau[21][21],int x_perso, int y_perso, int delta_perso, int dx,int dy,int BombeX[5],int BombeY[5],int RT);
int PersoDeplacementY(int tableau[21][21],int x_perso, int y_perso, int delta_perso, int dx,int dy,int BombeX[5],int BombeY[5],int RT);
void BombeEffect(int x,int y,int rayon,int *tableau[21][21],int RT);
void BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation,int RT);
void BombeEffectInv(int x,int y,int rayon,int *tableau[21][21],int BombeX,int BombeY,int RT);
#endif

