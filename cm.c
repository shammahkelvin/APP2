//
// Created by shamm on 03/11/2026.
//
#include <stdio.h>
#include "cm.h"
/*Problem : Un crepier fait une pile de crepes. Elles n'ont pas toutes la meme taille... Le crepier veut
          absolument les ordonner : la plus grande en bas et de plus en plus petites au fur et à mesure qu'on monte.
          Seule operation possible : glisser la spatule du crepier sous une crepe et retourner toutes les crepes qui se trouvent au dessus (d'un seul coup).*/

/* Solution :
 * crepes: sequence d'entiers
 * limite <- Nil
 * tant que limite /= crepes.tete
 *    max <- recherche_max(crepes, limite)
 *    retourner_tas(crepes, max)
 *    retourner_tas(crepes, precedent(limite))
 *    limite <- precedent(limite)
 *
 * fonction retourner_tas(crepes, pos)
 *    dernier <- crepes.tete
 *    debut, reste <- separation(crepess, pos)
 *    inverse_ordre(debut)
 *    crepes.tete <- pos
 *    derniere.suivant <- reste
 *
 * fonction separation_apres(crepes, pos)
 *    //coupe la liste chainee apres la cellule "pos"
 *    reste <- position.suivant
 *    debut <- crepes.tete
 *    position.suivant <- Nil
 *
 * fonction inverse_ordre(debut)
 *    autre <- Nil
 *    tant que debut /= Nil
 *        suiv <- debut.suivant
 *        debut.suivant <- autre
 *        autre <- debut
 *        debut <- suiv
 *
 * fonction rechercher_max(crepes, limite)
 *    max <- crepes.tete
 *    cel <- crepes.tete
 *    tant que cel /= limite
 *        si cel.valeur > max.valeur
 *            max <- cel
 *        cel <- cel.suivant
 *
 * fonction precedent(crepes, pos)
 *    si pos = crepes.tete
 *        retourner Nil
 *    cel <- crepes.tete
 *    tant que cel.suivant /= pos
 *        cel <- cel.suivant
 *        assert cel /= Nil // cas où pos n'est dans LC
 *    retourner cel
 *
 *
 *
 *

 */


void main()
{
    printf("Hello World!\n");
}