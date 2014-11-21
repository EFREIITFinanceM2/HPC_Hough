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
    
    double theta=M_1_PI/WH;

    for (int i=0; i<im->h; i++) {
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
    for (<#initialization#>; <#condition#>; <#increment#>) {
        <#statements#>
    }
}

void