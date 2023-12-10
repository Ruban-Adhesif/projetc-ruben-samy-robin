#ifndef PROJET_C_PART3_H
#define PROJET_C_PART3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour stocker les informations d'un contact
struct Contact {
    char *nom;
    char *prenom;
    struct RendezVous *listeRendezVous;
    struct Contact* suivant;
};

// Structure pour stocker la date
struct Date {
    int jour;
    int mois;
    int annee;
};

// Structure pour stocker le temps
struct Heure {
    int heure;
    int minute;
};

// Structure pour stocker la durée
struct Duree {
    int heure;
    int minute;
};

// Structure pour stocker les informations d'un rendez-vous
struct RendezVous {
    struct Date date;
    struct Heure heureDebut;
    struct Duree duree;
    char **objet;
    struct RendezVous *suivant;
};

// Structure pour stocker une entrée de l'agenda
struct AgendaEntry {
    struct Contact *contact;
    struct RendezVous *rendezVousListe;  // Liste simplement chaînée de rendez-vous
};

struct Niveau {
    struct Contact* contact;
    struct Niveau* suivant;
};

char* scanString(void);
struct Niveau* loadContactsFichiers(const char* fichierNoms, const char* fichierPrenoms);
struct Niveau* searchContact(struct Niveau* niveauxContacts, const char* nomRecherche, const char* prenomRecherche);
void printRendezVous(struct AgendaEntry *agendaEntry);
struct Contact *createContact(const char *nom, const char *prenom);
void createRendezVous(struct Contact *contact, int jour, int mois, int annee, int heure, int minute, int dureeHeure, int dureeMinute, const char *objet);
void deleteRendezVous(struct Contact *contact);
void freeContacts(struct Contact* contact);

#endif //PROJET_C_PART3_H
