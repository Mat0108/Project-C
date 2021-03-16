#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <allegro.h>
#include <dirent.h>
//savegarde une partie
void writeFile(int tableau[21][21],int powerTab[21][21],Player* perso1,Player* perso2,Bombe* bombe1,Bombe* bombe2)
{
    char buffer[100];
    char buffer2[100];
    int returnCode;
    int index;

    char filename[100];
    time_t timestamp = time( NULL );
    struct tm * timeInfos = localtime( & timestamp );
    sprintf(filename,"./savegame/save_%d.%d_%dh%d.data",timeInfos->tm_mday+1,timeInfos->tm_mon+1,timeInfos->tm_hour,timeInfos->tm_min);


    FILE * stream = fopen( filename, "w" );
    if ( stream == NULL ) {
        fprintf( stderr, "Cannot open file for writing\n" );
        exit( -1 );
    }
    //savegarde du niveau
    fwrite("Niveau : \n\n",10,1,stream);
    for( int i=0; i<21; i++ ) {
        sprintf(buffer,"");
        for (int j = 0;j<21;j++){
            sprintf( buffer2, "%d", tableau[i][j]);
            strcat(buffer,buffer2);
        }
        strcat(buffer,"\n");
        if ( 1 != fwrite( buffer,22, 1, stream ) ) {
            fprintf( stderr, "Cannot write block in file\n" );
        }
    }
    fwrite("\nPowerUpTab: \n",14,1,stream);
    //savegarde des powerup
    for( int i=0; i<21; i++ ) {
        sprintf(buffer,"");
        for (int j = 0;j<21;j++){
            sprintf( buffer2,"%2d", powerTab[i][j]);
            strcat(buffer,buffer2);
        }
        strcat(buffer,"\n");
        if ( 1 != fwrite( buffer,strlen(buffer), 1, stream ) ) {
            fprintf( stderr, "Cannot write block in file\n" );
        }
    }

    //savegardes des infos des deux persos
    sprintf(buffer,"\n\nplayer 1 : nom:%s ,x:%2d,y:%2d,color:%d,type:%d,nb_b:%d,nb_rayon:%d,nb_vie:%d",perso1->nom,perso1->x,perso1->y,perso1->color,perso1->type,perso1->bombe,perso1->rayon,perso1->vie);
    fwrite(buffer,70+strlen(perso1->nom),1,stream);
    fwrite("\n\nPosition des bombes du player 1\nX  Y  T",41,1,stream);
    for (int i = 0;i<5;i++)
    {
        sprintf( buffer, "\n%2d %2d %2d", bombe1->X[i],bombe1->Y[i],bombe1->Timer[i]);
        fwrite(buffer,9,1,stream);
    }
    sprintf(buffer,"\n\nplayer 2 : nom:%s ,x:%2d,y:%2d,color:%d,type:%d,nb_b:%d,nb_rayon:%d,nb_vie:%d",perso2->nom,perso2->x,perso2->y,perso2->color,perso2->type,perso2->bombe,perso2->rayon,perso2->vie);
    fwrite(buffer,70+strlen(perso2->nom),1,stream);
    sprintf(buffer,"");

    fwrite("\n\nPosition des bombes du player 2\nX  Y  T",41,1,stream);
    for (int i = 0;i<5;i++)
    {
        sprintf( buffer, "\n%2d %2d %2d", bombe2->X[i],bombe2->Y[i],bombe2->Timer[i]);
        fwrite(buffer,9,1,stream);
    }


    returnCode = fclose( stream );
    if ( returnCode == EOF ) {
        fprintf( stderr, "Cannot close file\n" );
        exit( -1 );
    }
}
void playerAffichage(Player* perso)
{
    printf("\n%s %d %d %d %d %d %d %d",perso->nom,perso->x,perso->y,perso->color,perso->type,perso->bombe,perso->rayon,perso->vie);
}
//recuperation des tableaux
void CharTabtoInt(FILE *file,int *tableau[21][21],int pos)
{
    int i,j;
    char niv;
    for(i=0;i<22;i++){
        for (j=0;j<22;j++){
            niv = fgetc(file);
            if (niv != EOF){
                switch(niv)
                {
                case '0':
                    tableau[i][j] = 0;
                    break;
                case '1':
                    tableau[i][j] = 1;
                    break;
                case '2':
                    tableau[i][j] = 2;
                    break;
                }}}}
}
//utlisé par la fonciton extractPlayer
int extract(int from, int to, char *chaine, char *sousChaine)
{
    int i=0, j=0;
    //récupérer la longueur de la chaîne
    for( i = from; i <= to; i++){
    sousChaine[i-from] = chaine[i];
    }
    return 0;
}
//extrait les données des joueurs
void extractPlayer(char text[200], Player * player)
{
    int k = 15;
    char xc[50],yc[50],colorc[50],typec[50],bombec[50],rayonc[50],viec[50];
    while (text[k] != ',')
    {
        k++;
    }
    extract(15,k-1,text,player->nom);

    if (player->nom[-2] == " ") player->nom[-1] = ' ';

    extract(k+3,k+4,text,xc);
    if(xc[0] == ' ') player->x = (int) xc[1]-48;
    else player->x = ((int) xc[0]-48)*10 + (int) xc[1]-48;
    extract(k+8,k+9,text,yc);
    if(yc[0] == ' ') player->y = (int) yc[1]-48;
    else player->y = ((int) yc[0]-48)*10 + (int) yc[1]-48;
    extract(k+17,k+17,text,colorc);
    player->color = (int)colorc[0] - 48;
    extract(k+24,k+24,text,typec);
    player->type = (int)typec[0] - 48;
    extract(k+31,k+31,text,bombec);
    player->bombe = (int)bombec[0]-48;
    extract(k+42,k+42,text,rayonc);
    player->rayon = (int)rayonc[0]-48;
    extract(k+51,k+51,text,viec);
    player->vie = (int)viec[0]-48;
    playerAffichage(player);

}
//charger une partie
void loadFile(const char *filename,int *tableau[21][21],int *powerUpTab[21][21],Player* perso1,Player* perso2,Bombe* bombe1,Bombe* bombe2)
{
    int niv;
    int i,j,k;
    char text[255];

    FILE * stream = fopen(filename, "r" );
    if ( stream == NULL ) {
        fprintf( stderr, "Cannot open file for writing\n" );
        exit( -1 );
    }
    //chargement du niveau
    fgets(text,50,stream);
    printf("\n\n");
    for(i = 0;i<21;i++)
    {
        fgets(text,50,stream);
        for(j = 0;j<21;j++)
        {
             tableau[i][j] =  (int)text[j]-48;
        }
    }
    affichage(tableau,21);

    //chargement du poweruptab
    fgets(text,50,stream);
    fgets(text,50,stream);
    for(i = 0;i<21;i++)
    {
        fgets(text,50,stream);
        for(j = 0;j<21;j++)
        {
            if (text[2*j+1] == '0'){
                powerUpTab[i][j] =  (int)text[2*j+1]-48;
            }
            else {
                if (text[2*j] != ' '){
                    powerUpTab[i][j] =  ((int)text[2*j]-48)*10+(int)text[2*j+1]-48;
                }
                else{
                    powerUpTab[i][j] = (int)text[2*j+1]-48;
                }
            }
        }
    }
    printf("\n\n");
    affichage(powerUpTab,21);


    fgets(text,150,stream);
    fgets(text,150,stream);
    fgets(text,150,stream);
    //recuperation des données du joueur 1
    extractPlayer(text,perso1);

    fgets(text,150,stream);
    fgets(text,150,stream);
    fgets(text,150,stream);
    printf("%s",text);
    //recuperation des données du joueur 1
    for (i = 0;i<5;i++)
    {
        fgets(text,150,stream);
        if(text[0] == ' ') bombe1->X[i] = (int)text[1]-48;
        else bombe1->X[i] = ((int)text[0] - 48)*10 + (int)text[1]-48;
        if(text[3] == ' ') bombe1->Y[i] = (int)text[4]-48;
        else bombe1->Y[i] = ((int)text[3]-48)*10 + (int)text[4]-48;
        if (text[6] == ' ') bombe1->Timer[i] = (int)text[7]-48;
        else bombe1->Timer[i] = ((int)text[6]-48)*10 + (int)text[7]-48;
        printf("\n%d %d %d",bombe1->X[i],bombe1->Y[i],bombe1->Timer[i]);
    }

    //recuperation des données du joueur 2
    fgets(text,150,stream);
    fgets(text,150,stream);
    extractPlayer(text,perso2);


    fgets(text,150,stream);
    fgets(text,150,stream);
    fgets(text,150,stream);
    printf("\n\n");
    //recuperation des données du joueur 2
    for (i = 0;i<5;i++)
    {
        fgets(text,150,stream);

        if(text[0] == ' ') bombe2->X[i] = (int)text[1]-48;
        else bombe2->X[i] = ((int)text[0] - 48)*10 + (int)text[1]-48;
        if(text[3] == ' ') bombe2->Y[i] = (int)text[4]-48;
        else bombe2->Y[i] = ((int)text[3]-48)*10 + (int)text[4]-48;
        if (text[6] == ' ') bombe2->Timer[i] = (int)text[7]-48;
        else bombe2->Timer[i] = ((int)text[6]-48)*10 + (int)text[7]-48;
        printf("\n%d %d %d",bombe2->X[i],bombe2->Y[i],bombe2->Timer[i]);
    }

    int returnCode = fclose(stream);
    if ( returnCode == EOF ) {
        fprintf( stderr, "Erreur durant la fermeture du fichier" );
        exit( -1 );
    }
}

void AffichageSave()
{
    BITMAP *image;
    image=load_bitmap("image/30/menu/save.bmp",NULL);
    blit(image,screen,0,0,30*26,10,image->w, image->h);
}
int MenuLoad()
{
    struct dirent *dir;
    DIR *d = opendir("./savegame/");
    int i=0,imax,result=0;
    char tab[12][100];
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(tab[i],dir->d_name);
            if (i<12) i++;
        }
        closedir(d);
    }
    imax = i;
    for (int i = 2;i<imax;i++)
    {

        printf("\n%d) %s",i-1,tab[i]);
    }
    Sleep(300);
    if (imax == 2) allegro_message("Aucun fichier a charger");
    else
    {
        printf("\nQuel fichier voulez vous charger ? ");
        fflush(stdout);
        scanf("%d",&result);
    }
    if (imax == 2) return 0;
    else return result+2;
}
