#ifndef PRE_TRAITEMENTS_H
#define PRE_TRAITEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"

/* Macro-constantes */
#define ASSOMBRISSEMENT 120
#define TRESHOLD_SOBEL 150.0

/* Assombrissement  d'une image pour pouvoir voir l'effet sur la sortie de la normalisation */
void assombrir_image(char * cheminEntree, char * cheminSortie, int val);

/* normalisation de l'image pour que l'intensité des pixels soit maximale */
void normalisation_image(char * chemin_entree, char * chemin_sortie);

/* filtre de Sobel */
void sobel(char * chemin_entree, char * chemin_sortie);

#endif