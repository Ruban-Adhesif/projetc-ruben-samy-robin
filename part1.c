#include "part1.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction qui créer une cellule et initialise le tableau de pointeur a NULL
p_d_cell create_cell(int value, int level) {
    // Allouer de la mémoire pour la cellule
    p_d_cell new_cell = (p_d_cell)malloc(sizeof(t_d_cell));
    // Securité pour vérifier les cas pas possible
    if (new_cell == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la cellule.\n");
        return 0;
    }
    // Initialiser les valeurs de la cellule
    new_cell->value = value;
    new_cell->level = level;
    // Allouer de la mémoire pour le tableau de pointeurs "next"
    new_cell->next = (p_d_cell *)malloc((level + 1) * sizeof(p_d_cell));
    // Securité pour vérifier les cas pas possible
    if (new_cell->next == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour le tableau de pointeurs.\n");
        return 0;
    }
    // Initialiser le tableau de pointeurs à NULL
    for (int i = 0; i <= level; i++) {
        new_cell->next[i] = NULL;
    }
    return new_cell;
}


// Fonction qui créer une liste vide
p_d_list create_empty_list(int max_level) {
    // Allouer de la mémoire pour la liste
    p_d_list new_list = (p_d_list)malloc(sizeof(t_d_list));
    // Securité pour vérifier les cas pas possible
    if (new_list == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la liste.\n");
        return 0;
    }
    // Initialiser les valeurs de la liste
    new_list->max_level = max_level;
    // Allouer de la mémoire pour le tableau de pointeurs "heads"
    new_list->heads = (p_d_cell *)malloc((max_level + 1) * sizeof(p_d_cell));
    // Securité pour vérifier les cas pas possible
    if (new_list->heads == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour le tableau de pointeurs.\n");
        return 0;
    }
    // Initialiser le tableau de pointeurs à NULL à l'aide d'une boucle
    for (int i = 0; i <= max_level; i++) {
        new_list->heads[i] = NULL;
    }
    return new_list;
}

// Fonction qui insère une cellule en tête de liste
void insert_at_head(p_d_list list, p_d_cell new_cell) {
    // Vérifier si la liste ou la cellule est invalide en vérifiant si c'est NULL
    if (list == NULL || new_cell == NULL) {
        printf("Liste ou cellule invalide.\n");
        return;
    }
    // Vérifier si le niveau de la cellule est valide
    if (new_cell->level > list->max_level) {
        printf("Niveau de cellule invalide pour la liste.\n");
        return;
    }
    // Insérer la cellule à chaque niveau de la liste
    for (int i = new_cell->level; i >= 0; i--) {
        // Pointe vers l'ancienne tête du niveau i
        new_cell->next[i] = list->heads[i];
        // Pointe vers la nouvelle cellule
        list->heads[i] = new_cell;
    }
}


// Fonction qui affiche toutes les cellules de la liste du nniveau donné en paramètre
void print_cells_at_level(p_d_list list, int level) {
    // Vérifier si la liste ou le niveau est NULL
    if (list == NULL || level < 0 || level > list->max_level) {
        printf("Liste invalide ou niveau invalide.\n");
        return;
    }
    printf("Valeur au niveau %d : ", level);
    // Initialiser la cellule avec la tête du niveau donné
    p_d_cell current_cell = list->heads[level];
    // Le temps que la cellule n'est pas NULL on affiche les valeurs quelle contient et on se déplace vers la suivante
    while (current_cell != NULL) {
        printf("%d ", current_cell->value);
        current_cell = current_cell->next[level];
    }
    printf("\n");
}

// Fonction pour afficher tous les niveaux de la liste
void print_all_levels(p_d_list list) {
    // Verifier si la liste en parametre est NULL
    if (list == NULL) {
        printf("Liste invalide.\n");
        return;
    }
    // Boucle qui permet d'afficher chaque niveau avec ces cellules
    for (int i = 0; i <= list->max_level; i++) {
        printf("[List head_%d @-]-->", i);
        p_d_cell current_cell = list->heads[i];
        // Le temps que la cellule n'est pas NULL alors on affiche la cellule et on passe à la suivante
        while (current_cell != NULL) {
            printf("[ %d|@-]-->", current_cell->value);
            current_cell = current_cell->next[i];
        }
        printf("NULL\n");
    }
}

// Fonction pour afficher tous les niveaux de la liste en faisant un alignement
void print_all_levels_aligned(p_d_list list){
    // Boucle qui permet d'afficher chaque niveau avec ces cellules
      for (int i=0; i <= list->max_level; i++){
          p_d_cell current_cell = list->heads[i];
          printf("[list head_%d @-]---", i);
          // On a rajouter une condition pour bien aligner si il n'y a pas de valeur dans le niveau correspondant
          while (current_cell != NULL){
              if (current_cell->level < i){
                  printf("------------");
                  current_cell = current_cell->next[0];
              }
              else{
                  printf(">[ %d|@-]---", current_cell->value);
                  current_cell = current_cell->next[0];
              }
          }
          // A la fin on affiche NULL
          printf(">NULL\n");
      }
}


// Fonction permettant d'ajouter une cellule au bon endroit en gardant la liste triée
void insertSorted(p_d_list list, p_d_cell cell) {
    // Vérifier si la liste ou la cellule est valide
    if (list == NULL || cell == NULL) {
        printf("Liste ou cellule non valide pour l'insertion\n");
        return;
    }
    // Vérifier si le niveau de la cellule est supérieur au niveau maximum de la liste
    int level = cell->level;
    if (level > list->max_level) {
        printf("Niveau de cellule supérieur au niveau maximum de la liste\n");
        return;
    }
    // Allouer de la mémoire pour le tableau 'update', qui sera utilisé pour mettre à jour les liens lors de l'insertion
    p_d_cell *update = (p_d_cell *)malloc(level * sizeof(p_d_cell));
    if (update == NULL) {
        printf("Erreur d'allocation mémoire pour update\n");
        return;
    }
    p_d_cell current = NULL;
    p_d_cell next = NULL;
    // Parcourir les niveaux de la liste en commençant par le niveau maximum
    for (int i = list->max_level - 1; i >= 0; i--) {
        // Initialiser 'current' à la tête de la liste au niveau actuel
        current = list->heads[i];
        // Parcourir la liste au niveau actuel jusqu'à trouver la bonne position pour insérer la cellule
        while (current != NULL && current->value < cell->value) {
            // Mettre à jour le tableau 'update' avec le dernier élément inférieur à la valeur de la cellule
            update[i] = current;
            current = current->next[i];
        }
    }
    // Insérer la cellule dans la liste à chaque niveau approprié
    for (int i = 0; i < level; i++) {
        // Mettre à jour les liens pour insérer la cellule à chaque niveau
        next = update[i]->next[i];
        update[i]->next[i] = cell;
        cell->next[i] = next;
    }
    // Libérer la mémoire allouée pour le tableau 'update'
    free(update);
}
