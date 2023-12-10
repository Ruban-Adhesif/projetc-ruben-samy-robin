#include "part3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour effectuer la saisie d'une chaîne de caractères dynamique
char* scanString(void) {
    char buffer[256];
    scanf("%255s", buffer);
    return strdup(buffer);
}

struct Niveau* loadContactsFichiers(const char* fichierNoms, const char* fichierPrenoms) {
    FILE* fichierNomsPtr = fopen(fichierNoms, "r");
    FILE* fichierPrenomsPtr = fopen(fichierPrenoms, "r");
    if (fichierNomsPtr == NULL || fichierPrenomsPtr == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL; // Retourne NULL en cas d'échec de l'ouverture du fichier
    }
    struct Niveau* niveauInitial = NULL;
    struct Niveau* niveauActuel = NULL;
    char ligneNom[256];
    char lignePrenom[256];

    while (fgets(ligneNom, sizeof(ligneNom), fichierNomsPtr) != NULL &&
           fgets(lignePrenom, sizeof(lignePrenom), fichierPrenomsPtr) != NULL) {
        // Supprime le caractère de nouvelle ligne à la fin de la ligne
        ligneNom[strcspn(ligneNom, "\n")] = '\0';
        lignePrenom[strcspn(lignePrenom, "\n")] = '\0';
        // Creer un nouveau contact
        struct Contact* nouveauContact = malloc(sizeof(struct Contact));
        if (nouveauContact == NULL) {
            printf("Erreur lors de l'allocation de la mémoire pour un contact\n");
            fclose(fichierNomsPtr);
            fclose(fichierPrenomsPtr);
            freeContacts((struct Contact *) niveauInitial); // Libérer la mémoire déjà allouée
            return NULL;
        }
        // Initialise le nom et le prenom du contact avec les lignes lues depuis les fichiers
        nouveauContact->nom = strdup(ligneNom);
        nouveauContact->prenom = strdup(lignePrenom);
        // Vérifiez si l'allocation de mémoire a réussi
        if (nouveauContact->nom == NULL || nouveauContact->prenom == NULL) {
            printf("Erreur lors de l'allocation de la mémoire pour un nom ou un prénom\n");
            fclose(fichierNomsPtr);
            fclose(fichierPrenomsPtr);
            freeContacts((struct Contact *) niveauInitial); // Libérer la mémoire déjà allouée
            freeContacts(nouveauContact); // Libérer la mémoire du contact actuel
            return NULL;
        }
        // Créez un nouveau niveau si nécessaire
        if (niveauInitial == NULL) {
            niveauInitial = malloc(sizeof(struct Niveau));
            niveauActuel = niveauInitial;
        } else {
            niveauActuel->suivant = malloc(sizeof(struct Niveau));
            niveauActuel = niveauActuel->suivant;
        }
        niveauActuel->contact = nouveauContact;
        niveauActuel->suivant = NULL;
    }
    fclose(fichierNomsPtr);
    fclose(fichierPrenomsPtr);
    return niveauInitial;
}

struct Niveau* searchContact(struct Niveau* niveauxContacts, const char* nomRecherche, const char* prenomRecherche) {
    // Convertir les noms recherches en minuscules pour la comparaison
    char nomRechercheMinuscule[256];
    char prenomRechercheMinuscule[256];
    strcpy(nomRechercheMinuscule, nomRecherche);
    strcpy(prenomRechercheMinuscule, prenomRecherche);
    strlwr(nomRechercheMinuscule);
    strlwr(prenomRechercheMinuscule);
    // Parcourir les niveaux
    struct Niveau* niveauActuel = niveauxContacts;
    while (niveauActuel != NULL) {
        // Comparer les noms dans chaque niveau
        if (strcmp(niveauActuel->contact->nom, nomRechercheMinuscule) == 0 &&
            strcmp(niveauActuel->contact->prenom, prenomRechercheMinuscule) == 0) {
            // Contact trouvé, renvoyer le niveau correspondant
            return niveauActuel;
        }
        // Passer au niveau suivant
        niveauActuel = niveauActuel->suivant;
    }
    // Contact non trouvé
    return NULL;
}

// Fonction pour afficher les rendez-vous d'un contact
void printRendezVous(struct AgendaEntry *agendaEntry) {
    // Vérifier si l'entrée de l'agenda est valide
    if (agendaEntry == NULL || agendaEntry->contact == NULL) {
        printf("Entree de l'agenda non valide pour l'affichage des rendez-vous\n");
        return;
    }
    // Afficher les informations du contact
    printf("Rendez-vous de %s %s :\n", agendaEntry->contact->prenom, agendaEntry->contact->nom);
    // Parcourir la liste des rendez-vous du contact
    struct RendezVous *rendezVousCourant = agendaEntry->rendezVousListe;
    while (rendezVousCourant != NULL) {
        // Afficher les details du rendez-vous
        printf("Date: %02d/%02d/%04d\n", rendezVousCourant->date.jour, rendezVousCourant->date.mois, rendezVousCourant->date.annee);
        printf("Heure de debut: %02d:%02d\n", rendezVousCourant->heureDebut.heure, rendezVousCourant->heureDebut.minute);
        printf("Durée: %02d:%02d\n", rendezVousCourant->duree.heure, rendezVousCourant->duree.minute);
        printf("Objet: %s\n", *rendezVousCourant->objet);
        printf("\n");
        // Pour pouvoir passer au rendez-vous suivant
        rendezVousCourant = rendezVousCourant->suivant;
    }
}


// Fonction pour créer un contact
struct Contact *createContact(const char *nom, const char *prenom) {
    // Verifier si les arguments sont valides
    if (nom == NULL || prenom == NULL) {
        printf("Nom ou prénom non valide pour la création du contact\n");
        return NULL;
    }
    // Allouer de la memoire pour le nouveau contact
    struct Contact *nouveauContact = (struct Contact *)malloc(sizeof(struct Contact));
    if (nouveauContact == NULL) {
        printf("Erreur d'allocation memoire pour le nouveau contact\n");
        return NULL;
    }
    // Allouer de la memoire pour les champs nom et prenom et copier les valeurs fournies
    nouveauContact->nom = strdup(nom);
    nouveauContact->prenom = strdup(prenom);
    // Verifier si l'allocation de memoire pour les champs nom et prenom a reussi
    if (nouveauContact->nom == NULL || nouveauContact->prenom == NULL) {
        printf("Erreur d'allocation memoire pour le nom ou le prenom du contact\n");
        free(nouveauContact->nom);
        free(nouveauContact->prenom);
        free(nouveauContact);
        return NULL;
    }
    // Initialiser le pointeur suivant à NULL
    nouveauContact->suivant = NULL;
    return nouveauContact;
}

// Fonction pour creer un rendez-vous pour un contact
void createRendezVous(struct Contact *contact, int jour, int mois, int annee, int heure, int minute, int dureeHeure, int dureeMinute, const char *objet) {
    // Verifier si le contact est valide
    if (contact == NULL) {
        printf("Contact non valide pour la creation du rendez-vous\n");
        return;
    }
    // Allouer de la memoire pour le nouveau rendez-vous
    struct RendezVous *nouveauRendezVous = (struct RendezVous *)malloc(sizeof(struct RendezVous));
    if (nouveauRendezVous == NULL) {
        printf("Erreur d'allocation memoire pour le nouveau rendez-vous\n");
        return;
    }
    // Initialiser les champs du rendez-vous avec les valeurs fournies
    nouveauRendezVous->date.jour = jour;
    nouveauRendezVous->date.mois = mois;
    nouveauRendezVous->date.annee = annee;
    nouveauRendezVous->heureDebut.heure = heure;
    nouveauRendezVous->heureDebut.minute = minute;
    nouveauRendezVous->duree.heure = dureeHeure;
    nouveauRendezVous->duree.minute = dureeMinute;
    // Allouer de la memoire pour le champ objet et copier la valeur fournie
    nouveauRendezVous->objet = (char **)malloc(sizeof(char *));
    *nouveauRendezVous->objet = strdup(objet);
    // Verifier si l'allocation de mémoire a réussi
    if (*nouveauRendezVous->objet == NULL) {
        printf("Erreur d'allocation memoire pour l'objet du rendez-vous\n");
        free(nouveauRendezVous->objet);
        free(nouveauRendezVous);
        return;
    }
    // Ajouter le rendez-vous à la liste des rendez-vous du contact
    nouveauRendezVous->suivant = contact->listeRendezVous;
    contact->listeRendezVous = nouveauRendezVous;
}

// Fonction pour supprimer un rendez-vous d'un contact
void deleteRendezVous(struct Contact *contact) {
    if (contact == NULL || contact->listeRendezVous == NULL) {
        printf("Aucun rendez-vous a supprimer pour ce contact\n");
        return;
    }
    // Afficher les rendez-vous pour aider l'utilisateur à choisir l'index à supprimer
    printRendezVous((struct AgendaEntry *) contact);
    // Demander à l'utilisateur de choisir l'index du rendez-vous à supprimer
    int indexASupprimer;
    printf("Entrez le numero du rendez-vous a supprimer : ");
    scanf("%d", &indexASupprimer);

    // Vérifier si l'index est valide
    if (indexASupprimer < 1) {
        printf("Index invalide\n");
        return;
    }

    // Supprimer le rendez-vous correspondant à l'index
    struct RendezVous *rendezVousCourant = contact->listeRendezVous;
    struct RendezVous *rendezVousPrecedent = NULL;

    for (int i = 1; i < indexASupprimer && rendezVousCourant != NULL; ++i) {
        rendezVousPrecedent = rendezVousCourant;
        rendezVousCourant = rendezVousCourant->suivant;
    }
    // Verifier si l'index est superieur à la taille de la liste des rendez-vous
    if (rendezVousCourant == NULL) {
        printf("Index invalide\n");
        return;
    }
    // Mettre à jour les liens pour retirer le rendez-vous de la liste
    if (rendezVousPrecedent != NULL) {
        rendezVousPrecedent->suivant = rendezVousCourant->suivant;
    } else {
        // Le rendez-vous a supprimer est le premier de la liste
        contact->listeRendezVous = rendezVousCourant->suivant;
    }

    // Liberer la mémoire du rendez-vous supprimé
    free(*rendezVousCourant->objet);
    free(rendezVousCourant->objet);
    free(rendezVousCourant);
}

// Fonction pour libérer la mémoire d'un contact et de ses rendez-vous
void freeContacts(struct Contact* contact) {
    if (contact == NULL) {
        return;
    }
    // Libérer la mémoire des champs nom et prénom du contact
    free(contact->nom);
    free(contact->prenom);
    // Liberer la mémoire de la liste des rendez-vous
    struct RendezVous* rendezVousCourant = contact->listeRendezVous;
    while (rendezVousCourant != NULL) {
        struct RendezVous* rendezVousSuivant = rendezVousCourant->suivant;
        free(*rendezVousCourant->objet);
        free(rendezVousCourant->objet);
        free(rendezVousCourant);
        rendezVousCourant = rendezVousSuivant;
    }
    // Liberer la mémoire du contact lui-même
    free(contact);
}