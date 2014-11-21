#include "pgm.h"
#include "pre_traitements.h"


/* Assombrissement  d'une image pour pouvoir voir les effets de la normalisation */
void assombrir_image(char * cheminEntree, char * cheminSortie, int val)
{
	int y=0, x=0;

	//création de la future image assombrie
	image * image = read_pgm(cheminEntree);

	for (y = 0; y < image->h; y++)
	{
		for (x = 0; x < image->w; x++)
		{
			//valeur du niveau de gris superieur à val => baisse le niveau de val 	
			if(image->img[y+x*(image->h)] > val)
			{
				image->img[y+x*(image->h)] = image->img[y+x*(image->h)] - val;
			}
			else //sinon : on met a 0 pour ne pas être en négatif
			{
				image->img[y+x*(image->h)] = 0;
			}
		}
	}
	write_pgm(cheminSortie, image);
	return;
}

void normalisation_image(char * chemin_entree, char * chemin_sortie)
{
	image * im = NULL;
	image * norma_train = NULL;
	int w=0,h=0,i=0;
	int taille_img=0;
	int pmin = 0, pmax=0;

	im = read_pgm(chemin_entree);

	w = im->w;
	h = im->h;
	taille_img = w*h;
	
	printf("\n  Creation d'une image normalisee: norma_train.pgm (h=%d,w=%d)...\n",h,w);
	norma_train = create_image(w,h,255);
	
	if( norma_train == NULL || chemin_entree == NULL || chemin_sortie == NULL)
		error("-- Problème normalisation -> pointeur NULL -- ");

	//On détermine les valeurs pmin et pmax de l'image de départ
	for(i=0; i< taille_img; i++)
	{     
			//Si la valeur du niveau de gris est inférieur à pmin, il devient pmin
			if(im->img[i]< pmin)
				pmin=im->img[i];   
			//Si la valeur du niveau de gris est supérieur à pmax, il devient pmax
			else if(im->img[i] > pmax)
				pmax=im->img[i];
	}

	// On applique la formule de normalisation avec les pmin et pmax trouvé
	for( i=0 ; i < taille_img; i++)
	{
		norma_train->img[i] = 255*(im->img[i]-pmin)/(pmax-pmin);
	}

	write_pgm(chemin_sortie,norma_train);
	
	return;
}

int mySobelFiltre(int a1,int a2, int a3,int b1, int b2,int b3,int c1, int c2, int c3, double SX[],double SY[]){
    return (int)sqrt(pow(a1*SX[0]+a2*SX[1]+a3*SX[2]+b1*SX[3]+b2*SX[4]+b3*SX[5]+c1*SX[6]+c2*SX[7]+c3*SX[8], 2)+pow(a1*SY[0]+a2*SY[1]+a3*SY[2]+b1*SY[3]+b2*SY[4]+b3*SY[5]+c1*SY[6]+c2*SY[7]+c3*SY[8],2));
}



void sobel(char * chemin_entree, char * chemin_sortie)
{
	image * im = NULL;
	image * img_sobel = NULL;
	//int w=0,h=0;
	int x=0,y=0;
	double norme_gradient;
	int gx,gy;
	
	im = read_pgm(chemin_entree);
	printf("\n* Creation de la sortie du filtre de Sobel: sobel.pgm (h=%d,w=%d)...\n",im->h,im->w);
	img_sobel = create_image(im->w,im->h,255);

	
	/* TO DO ! */
    
    int a1,a2,a3,b1,b2,b3,c1,c2,c3;
    a1=a2=a3=b1=b2=b3=c1=c2=c3=0;
    int h=im->h;
    int w=im->w;
    
    image* imSobelOut=create_image(im->w, im->h, im->colors);
    double SX[9]={0};
    double SY[9]={0};
    SX[0]=SX[6]=1;
    //SX[0]=SX[6]=0;
    SX[3]=2;
    //SX[3]=1/2;
    SX[2]=SX[8]=-1;
    //SX[2]=SX[8]=0;
    SX[5]=-2;
    //SX[5]=-1/2;
    SY[0]=SY[2]=1;
    //SY[0]=SY[2]=0;
    SY[1]=2;
    //SY[1]=1/2;
    SY[6]=SY[8]=-1;
    //SY[6]=SY[8]=0;
    SY[7]=-2;
    //SY[7]=-1/2;
    
    
    /*
     for (int i=0; i<im->h; i++) {
     for (int j=0; j<im->w; j++) {
     if (im->img[j*h+i]<120){
     im->img[j*h+i]=0;
     }
     else{
     imSobelOut->img[j*h+i]=255;
     }
     //imSobelOut->img[j*h+i] =sobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
     }
     }
     write_pgm("test.bmp", im);*/
    
    
    
    for (int j=1; j<im->w-1; j++) {
        a1=a2=a3=0;
        b1=im->img[(j-1)*h];
        b2=im->img[j*h];
        b3=im->img[(j+1)*h];
        c1=im->img[(j-1)*h+1];
        c2=im->img[j*h+1];
        c3=im->img[(j+1)*h+1];
        imSobelOut->img[j*h] = mySobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
    }
    
    for (int j=1; j<im->w-1; j++) {
        int i=h-1;
        a1=im->img[(j-1)*h+(i-1)];
        a2=im->img[j*h+(i-1)];
        a3=im->img[(j+1)*h+(i-1)];
        b1=im->img[(j-1)*h+i];
        b2=im->img[j*h+i];
        b3=im->img[(j+1)*h+i];
        c1=c2=c3=0;
        imSobelOut->img[j*h+i] = mySobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
    }
    
    
    for (int i=1; i<im->h-1; i++) {
        int j=0;
        a1=b1=c1=0;
        a2=im->img[j*h+(i-1)];
        a3=im->img[(j+1)*h+(i-1)];
        //b1=im->img[(j-1)*h+i];
        b2=im->img[j*h+i];
        b3=im->img[(j+1)*h+i];
        //c1=im->img[(j-1)*h+i+1];
        c2=im->img[j*h+i+1];
        c3=im->img[(j+1)*h+i+1];
        imSobelOut->img[j*h+i] = mySobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
    }
    
    
    for (int i=1; i<im->h-1; i++) {
        int j=w-1;
        a3=b3=c3=0;
        a1=im->img[(j-1)*h+(i-1)];
        a2=im->img[j*h+(i-1)];
        //a3=im->img[(j+1)*h+(i-1)];
        b1=im->img[(j-1)*h+i];
        b2=im->img[j*h+i];
        //b3=im->img[(j+1)*h+i];
        c1=im->img[(j-1)*h+i+1];
        c2=im->img[j*h+i+1];
        //c3=im->img[(j+1)*h+i+1];
        imSobelOut->img[j*h+i] = mySobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
    }
    
    for (int i=1; i<im->h-1; i++) {
        for (int j=1; j<im->w-1; j++) {
            a1=im->img[(j-1)*h+(i-1)];
            a2=im->img[j*h+(i-1)];
            a3=im->img[(j+1)*h+(i-1)];
            b1=im->img[(j-1)*h+i];
            b2=im->img[j*h+i];
            b3=im->img[(j+1)*h+i];
            c1=im->img[(j-1)*h+i+1];
            c2=im->img[j*h+i+1];
            c3=im->img[(j+1)*h+i+1];
            imSobelOut->img[j*h+i] =mySobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
        }
    }
    
    for (int i=0; i<im->h; i++) {
        for (int j=0; j<im->w; j++) {
            if (imSobelOut->img[j*h+i]<100){
                imSobelOut->img[j*h+i]=0;
            }
            else{
                imSobelOut->img[j*h+i]=255;
            }
            //imSobelOut->img[j*h+i] =sobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
        }
    }
    
    write_pgm("sobelOuptFile.bmp", imSobelOut);
    

	//write_pgm(chemin_sortie,img_sobel);

	return;
}