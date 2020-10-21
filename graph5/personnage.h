#ifndef _personnage_h
#define _personnage_h
void PersoAffichage(x_perso,y_perso);
int PersoDeplacementX(int *tableau[21][21],int x_perso, int y_perso, int delta_perso, int dx,int dy,int *BombeList[5][2]);
int PersoDeplacementY(int *tableau[21][21],int x_perso, int y_perso, int delta_perso, int dx,int dy,int *BombeList[5][2]);
void BombePlace(int x,int y);
int BombeAffichage(int *BombeList[5][3]);
int BombeReplace(int *tableau[21][21],int x,int y);
int BombeEffect(int x,int y,int rayon,int *tableau[21][21]);
int BombeEffect2(int x,int y,int rayon,int *tableau[21][21],int x2,int y2,int rotation);
#endif

