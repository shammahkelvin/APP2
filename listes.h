#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de compiler avec la macro 'SILENT' définie, en 
 * faisant 'make silent'
 */

#ifdef SILENT

/* Desactive tous les affichages */
#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)
/* Desactive les 'Appuyer sur entrée pour continuer' */
#define getchar() ('\n')

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;

typedef enum {
    TOKEN_NOMBRE,
    TOKEN_COMMANDE,
    TOKEN_OPERATEUR
} type_token_t;


struct cellule {
    type_token_t type;
    char command;
    /* vous pouvez rajouter d'autres champs ici */
    int value;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct cellule_pile {
    int value;
    struct cellule_pile *suivant;
};
typedef struct cellule_pile cellule_pile_t;

struct pile {
    cellule_pile_t *sommet;
};
typedef struct pile pile_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

bool pile_est_vide(const pile_t *pile);

void empiler (pile_t *pile, int value);

bool depiler(pile_t *pile, int *value);

void detruirePile(pile_t *pile);


#endif
