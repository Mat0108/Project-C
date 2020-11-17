#ifndef _menu_h
#define _menu_h
void Quitter();
void Play(int RT,int CT,int origin);
int ChoixNiveau(int tableau[21][21],int RT,int CT,int origin);
int ChoixPlayer(int RT,int CT,int origin);
void ChoixPerso(int x_perso,int y_perso,int *MenuPerso, int x_perso2,int y_perso2 ,int *MenuPerso2,int RT,int CT,int origin,int MenuPlayer);
void AffichageLigne(float x,float y,int RT);
void AffichageItemLoad(int RT,int debut,float x,int choix,char adress2[100]);
void AffichageItem(int RT,int CT,int nb_vie,int nb_bombes,int rayon ,int speed,int choixperso,int perso,int xorigin);
void InvisibiliteAffichage(int xorigin,int val,int RT);
void Invisibilite(int *invisibiliteOn,int InvisibiliteTimer,int xorigin,int RT);
#endif
