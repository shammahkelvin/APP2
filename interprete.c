#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}


static void detruireSeq(sequence_t *seq)
{
    cellule_t *courante = seq->tete;

    while (courante != NULL)
    {
        cellule_t *suivante = courante->suivant;
        detruireCellule(courante);
        courante = suivante;
    }
    seq->tete = NULL;
}

// Cette fonction parcourt la liste crée.
int interprete (sequence_t* seq, bool debug)
{
    assert(seq != NULL);

    cellule_t *courante = seq->tete;


    // debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    /* L'affichage est désactivé en mode silencieux */
    if (! silent_mode) {
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }


    // À partir d'ici, beaucoup de choses à modifier dans la suite.

    while (courante != NULL) { //à modifier: condition de boucle
        int ret;

        switch (courante->command) {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
                ret = avance();
                if (ret == VICTOIRE)
                {
                    detruireSeq(seq);
                    return VICTOIRE;
                } /* on a atteint la cible */
                if (ret == RATE)
                {
                    detruireSeq(seq);
                    return RATE;
                };     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */

            case 'G':
                gauche();
                break;

            case 'D':
                droite();
                break;

            default:
                eprintf("Caractère inconnu: '%c'\n", courante->command);
                return RATE;
        }

        /* Affichage pour faciliter le debug */
        if (! silent_mode) {
            afficherCarte();
            printf ("Programme:");
            afficher(seq);
            printf ("\n");
            if (debug) stop();
        }

        courante = courante->suivant;
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */
    detruireSeq(seq);
    return CIBLERATEE;
}
