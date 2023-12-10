#ifndef PROJET_C_PART2_H
#define PROJET_C_PART2_H
#include "part1.h"
#include "timer.h"

int recherche_niveau_0(const int *niveaux, int taille, int valeur_recherche);
int recherche_niveau_plus_haut(int **niveaux, int niveaux_count, int niveau_tailles[], int valeur_recherche);
p_d_list create_liste_n(int);
void performRandomSearch(p_d_list liste, int searches);
int getRandomValue(int max);
p_d_cell search(p_d_list liste, int value);

#endif //PROJET_C_PART2_H