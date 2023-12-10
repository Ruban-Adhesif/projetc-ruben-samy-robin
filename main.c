#include "part1.h"
#include "part2.h"
#include "part3.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    // PARTIE 1
    // Détermination du nombre de niveaux maximum
    int max_level = 4;

    // Créer un liste vide

    //p_d_list emptylist = create_empty_list(max_level);

    p_d_list new_list = create_empty_list(max_level);
    // Utilisation des fonctions pour créer une cellule et insérer une valeur à la tête des niveaux
    p_d_cell new_cell = create_cell(42, 3);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(40, 4);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(38, 1);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(35, 2);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(35, 3);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(21, 4);
    insert_at_head(new_list, new_cell);
    new_cell = create_cell(21, 35);
    insert_at_head(new_list, new_cell);

    // Appel de fonction pour afficher les saisies faites précédement
    printf("Afficher le contenu d'un niveau d'une maniere simple :\n");
    print_cells_at_level(new_list, 35);
    printf("\nChaque niveaux de la liste affiches :\n");
    // Afficher tous les niveaux de la liste
    print_all_levels(new_list);

    printf("\n----------------\n");
    printf("----------------\n\n");

    // Afficher tous les niveaux de la liste en étant alignés
    printf("Chaque niveaux de la liste affiches alignes :\n");
    print_all_levels_aligned(new_list);

    //Libérer la mémoire à la fin
    free(new_list->heads);
    free(new_list);
    //////////////////////////////////////////////////////////
    // Fonction PARTIE 2

    /*p_d_list new_list2 = create_liste_n(3);
    print_all_levels(new_list2);*/

    /*int valeur_recherche = 3;

    // Appeler la fonction de recherche
    int resultat_recherche = recherche_niveau_0(0, 1, valeur_recherche);

    // Afficher le résultat de la recherche
    if (resultat_recherche != -1) {
        printf("La valeur %d a été trouvée à l'index %d dans le niveau 0.\n", valeur_recherche, resultat_recherche);
    } else {
        printf("La valeur %d n'a pas été trouvée dans le niveau 0.\n", valeur_recherche);
    }*/
    /*printf("\n----------------\n");
    printf("----------------\n\n");
    // Utilisation de la fonction timer dans les différents cas
    printf("1. Temps pour %d recherches:\n", 1000);
    performRandomSearch(new_list2, 1000);

    printf("\n2. Temps pour %d recherches:\n", 10000);
    performRandomSearch(new_list2, 10000);

    printf("\n3. Temps pour %d recherches:\n", 100000);
    performRandomSearch(new_list2, 100000);*/


    //////////////////////////////////////////////////////////
    // PARTIE 3
    /*
    // Charger les contacts depuis les fichiers
    struct Niveau* niveauxContacts = loadContactsFichiers("noms.txt", "prenoms.txt");

    // Afficher les contacts chargés
    struct Niveau* niveauActuel = niveauxContacts;
    while (niveauActuel != NULL) {
        printf("Nom: %s, Prenom: %s\n", niveauActuel->contact->nom, niveauActuel->contact->prenom);
        niveauActuel = niveauActuel->suivant;
    }

    // Rechercher un contact par nom et prénom
    printf("Entrez le nom a rechercher : ");
    char* nomRecherche = scanString();
    printf("Entrez le prenom a rechercher : ");
    char* prenomRecherche = scanString();

    struct Niveau* contactTrouve = searchContact(niveauxContacts, nomRecherche, prenomRecherche);

    if (contactTrouve != NULL) {
        printf("Contact trouve : %s %s\n", contactTrouve->contact->prenom, contactTrouve->contact->nom);
        // Afficher les rendez-vous du contact trouvé
        printRendezVous(contactTrouve);
    } else {
        printf("Contact non trouve.\n");
    }
    // Libérer la mémoire des contacts
    freeContacts(niveauxContacts);*/
    return 0;
}