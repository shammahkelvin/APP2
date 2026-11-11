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
    /* À compléter (utiliser malloc) */
    cellule_t *cellule = malloc(sizeof(cellule_t));

    if (cellule == NULL) {
        return NULL;
    }

    cellule->command = '\0';
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
  /* À compléter */
    cellule_t *precedente = NULL;
    assert(texte != NULL);
    assert(seq != NULL);

    seq->tete = NULL;

    for (char *p = texte; *p != '\0'; p++)
    {
        if (*p != 'A' && *p != 'G' && *p != 'D')
        {
            /* les retours à la ligne et espaces presents dans le fichiers sont ignores. */
            continue;
        }
        cellule_t *nouv = nouvelleCellule();
        nouv->command = *p;

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
    /* À compléter */
    cellule_t *courante = seq->tete;
    while (courante != NULL)
    {
        printf("%c", courante->command);
        courante = courante->suivant;
    }
}

int est_vide(sequence_t *seq)
{
    return seq->tete == NULL;
}

void empiler (sequence_t* seq, int value)
{
    cellule_t *nouv = nouvelleCellule();

    nouv->value = value;
    nouv->suivant = seq->tete;
    seq->tete = nouv;
}

int depiler(sequence_t *seq)
{
    cellule_t *courante;
    int value;
    if (est_vide(seq))
    {
       printf("La sequence est vide.\n");
        return 0;
    }

    courante = seq->tete;
    value = courante->value;
    seq->tete = courante->suivant;
    detruireCellule(courante);

    return value;

}