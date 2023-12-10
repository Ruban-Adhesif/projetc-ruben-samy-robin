#include <stdio.h>
#include <stdlib.h>
#include "part2.h"
#include "timer.c"
#include <math.h>

// Fonction permettant de creer une liste a partir de n, creer un tableau de 2^n-1 valeurs
p_d_list create_liste_n(int n){
    p_d_list liste = create_empty_list(n);
    p_d_cell temp = NULL;
    for (int i = 0; i < pow(2, n)-1; i++) { // on va creer la liste avec (2^n)-1 cellules et les valeurs correspondantes toutes de niveau 0
        p_d_cell cellule = create_cell(i + 1, 1);
        if (liste->heads[0] == NULL) { // Pour faire en sorte que la premiere soit la tete du niveau
            liste->heads[0] = cellule;
        } else {
            temp = liste->heads[0];// Pour ensuite que les autres se lient entre elles
            while (temp->next[0] != NULL) {
                temp = temp->next[0];
            }
            temp->next[0] = cellule;
        }}
    int niveau = 1;
    for(int j = 2; j <= pow(2,n-1); j = j*2){ // Ensuite on utilise les instructions presentent dans le document pour augmenter les niveaux qu"il faut , un sur 2 puis un sur 4 puis un sur 8 ect selon n
        temp=liste->heads[0];// On aura une variable temp qui va parcourir l'entierete du niveau 0 pour voir grace à la valeur si le niveau de chaque cellule doit etre augmenté ou pas
        p_d_cell temp2 = NULL;// Et une autre variable temp qui va permettre de lier les maillons des autres niveaux
        while (temp!=NULL){
            if (temp->value%j == 0){ // Savoir si on doit rajouter des niveaux pour ce maillon
                temp->level++; // On incremente son niveau
                temp->next[(temp->level)-1] = NULL; // On rajoute une case "NULL" dans son tableau suivant (au lieu de faire un ajout de mémoire)
                if (liste->heads[niveau] == NULL){ // Si il n'y a aucun maillon à ce niveau on le met en tête
                    liste->heads[niveau] = temp;
                    temp2=liste->heads[niveau];
                }
                else{
                    temp2->next[niveau]=temp;// Sinon on le relie
                    temp2 = temp2->next[niveau];
                }
            }
            temp = temp->next[0];
        }
        niveau ++;// On augmente le niveau ou on se trouve
    }
    return liste;
}

// Fonction qui recherche dans le niveau 0
int recherche_niveau_0(const int *niveaux, int taille, int valeur_recherche) {
    // Parcourir le niveau 0 de la liste
    for (int i = 0; i < taille; i++) {
        if (niveaux[i] == valeur_recherche) {
            // Retourner l'index si la valeur est trouvée
            return i;
        }
    }
    // Retourner -1 si la valeur n'est pas trouvée dans le niveau 0
    return -1;
}

// Fonction qui recherche en partant du niveau le plus haut
int recherche_niveau_plus_haut(int **niveaux, int niveaux_count, int niveau_tailles[], int valeur_recherche) {
    // Parcourir du niveau le plus haut au niveau 0
    for (int niveau = niveaux_count - 1; niveau >= 0; niveau--) {
        // Parcourir le niveau actuel
        for (int i = 0; i < niveau_tailles[niveau]; i++) {
            if (niveaux[niveau][i] == valeur_recherche) {
                // Retourner l'index si la valeur est trouvée
                return i;
            }
        }
    }
    // Retourner -1 si la valeur n'est pas trouvée dans les niveaux
    return -1;
}

int getRandomValue(int max) {
    return rand() % max + 1;
}

// Fonction qui permet de rechercher
p_d_cell search(p_d_list liste, int value) {
    int currentLevel = liste->max_level - 1; // On commence au niveau le plus haut
    p_d_cell current = liste->heads[currentLevel];
    while (current != NULL) {
        if (current->value == value) { // Si Valeur trouvée
            return current;
        } else if (current->next[currentLevel] != NULL && current->next[currentLevel]->value <= value) { // Se déplacer à l'élément d'apres dans le niveau
            current = current->next[currentLevel];
        } else {
            // Se déplacer au niveau plus bas
            currentLevel--;
            if (currentLevel < 0) { // Valeur non trouvée
                return NULL;
            }
            current = current->next[currentLevel];
        }
    }
    // Valeur non trouvée
    return NULL;
}


// Fonction pour effectuer une recherche aléatoire dans la liste et mesurer le temps pris
void performRandomSearch(p_d_list liste, int searches) {
    startTimer();
    for (int i = 0; i < searches; i++) {
        int valueToSearch = getRandomValue(pow(2, liste->max_level) - 1);
        search(liste, valueToSearch);
    }
    stopTimer();
    printf("Nombres de recherches effectuees: %d\n", searches);
    displayTime();
}