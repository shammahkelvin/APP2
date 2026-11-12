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

int interprete (sequence_t* seq, bool debug)
{
    assert(seq != NULL);

    cellule_t *courante = seq->tete;
    pile_t pile_calcul = { NULL };

    if (! silent_mode) {
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }

    while (courante != NULL) {
        int ret;
        int a;
        int b;

        if (courante->type == TOKEN_NOMBRE) {
            empiler(&pile_calcul, courante->value);
        } else if (courante->type == TOKEN_OPERATEUR) {
            if (!depiler(&pile_calcul, &b) ||
                !depiler(&pile_calcul, &a)) {
                eprintf("Pas assez de valeurs pour l'opérateur '%c'\n",
                        courante->command);
                detruirePile(&pile_calcul);
                detruireSeq(seq);
                return RATE;
            }

            switch (courante->command) {
                case '+':
                    empiler(&pile_calcul, a + b);
                    break;
                case '-':
                    empiler(&pile_calcul, a - b);
                    break;
                case '*':
                    empiler(&pile_calcul, a * b);
                    break;
                default:
                    eprintf("Opérateur inconnu: '%c'\n",
                            courante->command);
                    detruirePile(&pile_calcul);
                    detruireSeq(seq);
                    return RATE;
            }
        } else {
            switch (courante->command) {

            case 'A':
                ret = avance();
                if (ret == VICTOIRE)
                {
                    detruirePile(&pile_calcul);
                    detruireSeq(seq);
                    return VICTOIRE;
                } /* on a atteint la cible */
                if (ret == RATE)
                {
                    detruirePile(&pile_calcul);
                    detruireSeq(seq);
                    return RATE;
                }
                break;

            case 'G':
                gauche();
                break;

            case 'D':
                droite();
                break;

            default:
                eprintf("Caractère inconnu: '%c'\n", courante->command);
                detruirePile(&pile_calcul);
                detruireSeq(seq);
                return RATE;
            }
        }

        if (! silent_mode) {
            afficherCarte();
            printf ("Programme:");
            afficher(seq);
            printf ("\n");
            if (debug) stop();
        }

        courante = courante->suivant;
    }

    detruirePile(&pile_calcul);
    detruireSeq(seq);
    return CIBLERATEE;
}
