#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"
#include "pre_traitements.h"

#define PI 3.1415

int main( void )
{
	//permet de générer une image assombrie pour voir l'intérêt de la normalisation
	printf("* Assombrissement de l'image train.pgm...\n");
	assombrir_image("train.pgm","train_noirci.pgm", ASSOMBRISSEMENT);
	printf("  Assombrissement de l'image reussie.\n\n");

	//normalisation de l'image norcie
	printf("* Normalisation de l'image noircie...\n");
	normalisation_image("train_noirci.pgm", "train_normalise.pgm");
	printf("  Creation de l'image normalisee reussie.\n");

	//Application du filtre de Sobel sur l'image normalisée
	printf("* Creation de la sortie du filtre de Sobel...\n");
	sobel("train_normalise.pgm", "train_sobel.pgm");
	printf("  Creation de l'image filtre de Sobel reussie.\n");

	system("PAUSE");

	return 0;
}