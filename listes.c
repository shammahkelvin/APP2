#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


cellule_t* nouvelleCellule (void)
{
    cellule_t *cellule = malloc(sizeof(cellule_t));

    if (cellule == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cellule->type = TOKEN_COMMANDE;
    cellule->command = '\0';
    cellule->value = 0;
    cellule->suivant = NULL;
    return cellule;

}


void detruireCellule (cellule_t* cel)
{
    /* À compléter (utiliser free) */
    free(cel);
}


/* Attention: seq est utilisée pour une "valeur de retour", pour y stocker la 
 * séquence. Donc il n'y a pas de garantie sur son état, en particulier 
 * seq->tete peut ne pas être initialisée à NULL.
 */


//Cet fonction parcourt le text
void conversion (char *texte, sequence_t *seq)
{
    cellule_t *precedente = NULL;
    char *p = texte;

    assert(texte != NULL);
    assert(seq != NULL);

    seq->tete = NULL;

    while (*p != '\0') {
        cellule_t *nouv;

        if (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t') {
            p++;
            continue;
        }

        nouv = nouvelleCellule();

        if (*p >= '0' && *p <= '9') {
            nouv->type = TOKEN_NOMBRE;
            nouv->value = 0;

            while (*p >= '0' && *p <= '9') {
                nouv->value = nouv->value * 10 + (*p - '0');
                p++;
            }
        } else if (*p == 'A' || *p == 'G' || *p == 'D') {
            nouv->type = TOKEN_COMMANDE;
            nouv->command = *p;
            p++;
        } else if (*p == '+' || *p == '-' || *p == '*') {
            nouv->type = TOKEN_OPERATEUR;
            nouv->command = *p;
            p++;
        } else {
            eprintf("Caractère inconnu dans le programme: '%c'\n", *p);
            detruireCellule(nouv);
            p++;
            continue;
        }

        if (seq->tete == NULL)
        {
            seq->tete = nouv;
        } else
        {
            precedente->suivant = nouv;
        }
        precedente = nouv;
    }
}


void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */
    cellule_t *courante = seq->tete;

    while (courante != NULL)
    {
        if (courante->type == TOKEN_NOMBRE) {
            printf("%d", courante->value);
        } else {
            printf("%c", courante->command);
        }

        if (courante->suivant != NULL) {
            printf(" ");
        }

        courante = courante->suivant;
    }
}

bool pile_est_vide(const pile_t *pile)
{
    assert(pile != NULL);
    return pile->sommet == NULL;
}

void empiler (pile_t *pile, int value)
{
    cellule_pile_t *nouvelle = malloc(sizeof(cellule_pile_t));

    if (nouvelle == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    nouvelle->value = value;
    nouvelle->suivant = pile->sommet;
    pile->sommet = nouvelle;
}

bool depiler(pile_t *pile, int *value)
{
    cellule_pile_t *ancienne_tete;

    assert(pile != NULL);
    assert(value != NULL);

    if (pile_est_vide(pile)) {
        return false;
    }

    ancienne_tete = pile->sommet;
    *value = ancienne_tete->value;
    pile->sommet = ancienne_tete->suivant;

    free(ancienne_tete);

    return true;
}

void detruirePile(pile_t *pile)
{
    int value;

    assert(pile != NULL);

    while (depiler(pile, &value)) {
    }
}