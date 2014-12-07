#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"
#include "pre_traitements.h"
#include "hough.h"

#define PI 3.1415

int main( void )
{
	//permet de générer une image assombrie pour voir l'intérêt de la normalisation
	printf("* Assombrissement de l'image train.pgm...\n");
	assombrir_image("train.pgm","train_noirci.bmp", ASSOMBRISSEMENT);
	printf("  Assombrissement de l'image reussie.\n\n");

	//normalisation de l'image norcie
	printf("* Normalisation de l'image noircie...\n");
	normalisation_image("train_noirci.bmp", "train_normalise.bmp");
	printf("  Creation de l'image normalisee reussie.\n");

	//Application du filtre de Sobel sur l'image normalisée
	printf("* Creation de la sortie du filtre de Sobel...\n");
	sobel("train_normalise.bmp", "train_sobel.bmp");
	printf("  Creation de l'image filtre de Sobel reussie.\n");
    
    printf("* HOUGH.\n");
    hough("train_sobel.bmp", "hough.bmp");

	system("PAUSE");

	return 0;
}