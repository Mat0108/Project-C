#ifndef _menu_h
#define _menu_h
void Quitter();//Bouton Quit, permet de quitter le programme
void Play(int RT,int CT,int origin);//Bouton Play, pour jouer à Bomberman
int ChoixNiveau(int tableau[21][21],int RT,int CT,int origin);//Bouton pour le choix du niveau
int ChoixPlayer(int RT,int CT,int origin);//Bouton pour le choix du mode de jeu
void ChoixPerso(int x_perso,int y_perso,int *MenuPerso, int x_perso2,int y_perso2 ,int *MenuPerso2,int RT,int CT,int origin,int MenuPlayer);//Bouton pour choisir le personnage
void AffichageLigne(float x,float y,int RT);//Affichage des lignes qui se trouvent à gauche (et à droit si 2 joueurs) de l'écran pour les noms des power
void AffichageItemLoad(int RT,int debut,float x,int choix,char adress2[100]);//Affichage des powerups qui se trouvent à gauche (et à droit si 2 joueurs)
void AffichageItem(int RT,int CT,int nb_vie,int nb_bombes,int rayon ,int speed,int choixperso,int perso,int xorigin);//Permet l'appel des 2 fonctions pour l'affichage des powerups des persos
void InvisibiliteAffichage(int xorigin,int val,int RT);//Affichage de la barre d'invincibilité
void Invisibilite(int *invisibiliteOn,int InvisibiliteTimer,int xorigin,int RT);//Execution de l'invicibilité
void Invisibilite_Activable(int *InvisibiliteOn,int *InvisibiliteTimerval,int InvisibiliteTimer,int val, int RT);//Activation de l'invincibilité
void Invisibilite_Update(int *InvisibiliteTimerval,int InvisibiliteTimer,int val2, int RT);//Affichage qui se réduit avec le temps (quand le powerup est actif), réduction de la barre d'invincibilité
#endif
