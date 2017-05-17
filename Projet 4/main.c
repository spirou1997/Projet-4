//
//  main.c
//  Projet 4
//
//  Created by Paul-Henri Zimmerlin on 04/05/2017.
//  Copyright © 2017 Paul-Henri Zimmerlin. All rights reserved.
//

#include <stdio.h>
#include "Bibliotheque.h"
#define FLAG_HORIZONTAL 1
#define FLAG_VERTICAL 0

typedef struct {
    int x_debut;
    int y_debut;
    int x_fin;
    int y_fin;
} Mot;

int insererMotGrille(char **tab, int *taillex, int *tailley, char *mot);
int detectOrientation(char **tab, int taillex, int tailley, int posx, int posy);
Mot CoordonneesMot(char **tab, int taillex, int tailley, char *mot, int posx, int posy);
void MotsCroises();


// Cette fonction retourne 1 si un mot donné a pu être inséré automatiquement dans la grille.

int insererMotGrille(char **tab, int *taillex, int *tailley, char *mot){
    for(int i = 0; i < *taillex; i++){
        for(int j = 0; j < *tailley; j++){
            if(accederTab2D(tab, *taillex, *tailley, i, j) != '*'){
                if(*mot == tab[i][j]){
                    afficherTab2D(tab, *taillex, *tailley);
                    printf("\n");
                    int dir;
                    if(detectOrientation(tab, *taillex, *tailley, i, j)) dir = 0;
                    else dir = 1;
                    for(int l = 0; l <= strlen(mot); l++){
                        if(dir == FLAG_HORIZONTAL){
                            if(tab[i][j+l] != '*') return 0;
                            if(tab[i+1][j+l] != '*' || tab[i-1][j+l] != '*') return 0;
                        }
                    }
                    insererMotDansTab2D(&tab, taillex, tailley, i, j, dir, mot);
                    //printf("%d", detectOrientation(tab, *taillex, *tailley, i, j));
                    return 0;
                }
            }
        }
    }
    return 1;
}

// Retourne l'orientation du mot, ou -1 en cas d'erreur.

int detectOrientation(char **tab, int taillex, int tailley, int posx, int posy){
    if((accederTab2D(tab, taillex, tailley, posx - 1, posy) != '*'|| accederTab2D(tab, taillex, tailley, posx + 1, posy) != '*') && (accederTab2D(tab, taillex, tailley, posx, posy - 1) == '*'|| accederTab2D(tab, taillex, tailley, posx, posy + 1) == '*')) return FLAG_VERTICAL;
    if((accederTab2D(tab, taillex, tailley, posx, posy - 1) != '*'|| accederTab2D(tab, taillex, tailley, posx, posy + 1) != '*') && (accederTab2D(tab, taillex, tailley, posx - 1, posy) == '*'|| accederTab2D(tab, taillex, tailley, posx + 1, posy) == '*')) return FLAG_HORIZONTAL;
    return -1;
}

// Cette fonction détecte les coordonnées de début et de fin d'un mot dans la grille.

Mot CoordonneesMot(char **tab, int taillex, int tailley, char *mot, int posx, int posy){
    Mot newmot;
    int i = posx,j = posy, orientation = detectOrientation(tab, taillex, tailley, posx, posy);
    if(orientation == FLAG_HORIZONTAL){
        newmot.x_debut = posx;
        newmot.x_fin = posx;
        while(accederTab2D(tab, taillex, tailley, i, j) != '*'){
            newmot.y_debut = j;
            j--;
        }
        j = posy;
        while(accederTab2D(tab, taillex, tailley, i, j) != '*'){
            newmot.y_fin = j;
            j++;
        }
    }
    if(orientation == FLAG_VERTICAL){
        newmot.y_debut = posy;
        newmot.y_fin = posy;
        while(accederTab2D(tab, taillex, tailley, i, j) != '*'){
            newmot.x_debut = i;
            i--;
        }
        i = posx;
        while(accederTab2D(tab, taillex, tailley, i, j) != '*'){
            newmot.x_fin = i;
            i++;
        }
    }
    else{
        newmot.x_debut = 0;
        newmot.x_fin = 0;
        newmot.y_debut = 0;
        newmot.y_fin = 0;
    }
    return newmot;
}

// Partie 1 : Mots croisés
void MotsCroises(){
    
    int taillex = 0;
    int tailley = 0;
    
    // Créer une grille vide (uniquement des '*'
    char **tab = creerTab2D(taillex, tailley);
    
    // Charger le dictionnaire
    char **lexique = chargerLexique("/Users/Paul-Henri/ownCloud/Cours EFREI/Semestre 2/Algorithmique/Projet 4/Projet 4/dico.txt", calculerTailleLexique("/Users/Paul-Henri/ownCloud/Cours EFREI/Semestre 2/Algorithmique/Projet 4/Projet 4/dico.txt"));
    
    // Ajouter un mot du dictionnaire
    insererMotDansTab2D(&tab, &taillex, &tailley, 2, 5, FLAG_HORIZONTAL, lexique[0]);
    
    // Faire croiser ce mot
    insererMotDansTab2D(&tab, &taillex, &tailley, 0, 5, FLAG_VERTICAL, lexique[1]);
    
    for(int i = 0; i < 9; i++){
        insererMotGrille(tab, &taillex, &tailley, lexique[i]);
    }
    
    
    //insererMotDansTab2D(&tab, &taillex, &tailley, 1, 4, 1, lexique[0]);
    /**insererMotGrille(tab, &taillex, &tailley, lexique[0]);
    insererMotGrille(tab, &taillex, &tailley, lexique[3]);
    insererMotGrille(tab, &taillex, &tailley, lexique[0]);*/
    afficherTab2D(tab, taillex, tailley);
    //Mot blabla = CoordonneesMot(tab, taillex, tailley, "NNNNN", 0, 5);
    //printf("x : %d, %d ; y: %d, %d\n", blabla.x_debut, blabla.x_fin, blabla.y_debut, blabla.y_fin);
}


int main(int argc, const char * argv[]) {
    MotsCroises();
    return 0;
}
