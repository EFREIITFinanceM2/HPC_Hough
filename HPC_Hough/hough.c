//
//  hough.c
//  HPC_Hough
//
//  Created by ZN-MAC on 14/11/21.
//  Copyright (c) 2014年 ZHANG Nan. All rights reserved.
//

#include "hough.h"

void hough(char* input, char* output){
    image* im=read_pgm(input);
    int RMAX =sqrt(pow(im->h, 2)+pow(im->w, 2));
    int **houghMatrix;
    houghMatrix=(int**)malloc(sizeof(int*)*WH);
    for (int i=0; i<WH; i++) {
        houghMatrix[i]=(int*)malloc(sizeof(int)*RMAX);
        for (int j=0; j<RMAX; j++) {
            houghMatrix[i][j]=0;
        }
    }
    
    double theta=PI/(2*WH);
    
    int max10[NUM_LINES]={0};
    int positioni[NUM_LINES];
    int positionj[NUM_LINES];

#pragma omp parallel
    {
#pragma omp for
    for (int i=0; i<im->h; i++) {
#pragma omp for
        for (int j=0; j<im->w; j++) {
            if (im->img[j*im->h+i]>THRESHOLD_HOUGH) {
                for (int l=0; l<WH; l++) {
                    int r=i*sin(theta*l)+j*cos(theta*l);
                    if (r<RMAX) {
                        houghMatrix[l][r]++;
                    }
                }
            }
        }
            //imSobelOut->img[j*h+i] =sobelFiltre(a1, a2, a3, b1, b2, b3, c1, c2, c3, SX, SY);
    }
#pragma omp for
    for (int i=0; i<WH; i++) {
        for (int j=0; j<RMAX; j++) {
            for (int k=0; k<NUM_LINES; k++) {
                if (max10[k]<houghMatrix[i][j]) {
                    for (int n=NUM_LINES-1; n>k; n--) {
                        max10[n]=max10[n-1];
                    }
                    max10[k]=houghMatrix[i][j];
                    positioni[k]=i;
                    positionj[k]=j;
                    break;
                }
            }
        }
    }
  /*
    for (int i=0; i<im->h; i++)
        for (int j=0; j<im->w; j++)
            im->img[j*im->h+i]=0;
    */
        
#pragma omp for
    int j=0;
    for (int k=0; k<NUM_LINES; k++) {
#pragma omp for
        for (int i=0; i<im->h; i++) {
            j=(positionj[k]-(i*sin(theta*positioni[k])))/cos(theta*positioni[k]);
            if (j<im->w && j>0) {
                im->img[j*im->h+i]=255;
            }
        }
    }
        
    }//end of parallel
    
    write_pgm(output, im);
    
}

//void