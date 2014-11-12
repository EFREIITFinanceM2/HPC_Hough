//
//  main.c
//  HPC_Hough
//
//  Created by ZN-MAC on 14/11/11.
//  Copyright (c) 2014年 ZHANG Nan. All rights reserved.
//

#include <stdio.h>
#include "pgm.h"
#include <math.h>

int mySobelFiltre(int a1,int a2, int a3,int b1, int b2,int b3,int c1, int c2, int c3, double SX[],double SY[]){
    return (int)sqrt(pow(a1*SX[0]+a2*SX[1]+a3*SX[2]+b1*SX[3]+b2*SX[4]+b3*SX[5]+c1*SX[6]+c2*SX[7]+c3*SX[8], 2)+pow(a1*SY[0]+a2*SY[1]+a3*SY[2]+b1*SY[3]+b2*SY[4]+b3*SY[5]+c1*SY[6]+c2*SY[7]+c3*SY[8],2));
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //test merge
    printf("Hello, World!\n");
    
    image* im = read_pgm("train.pgm");
    write_pgm("outputFile.bmp", im);
    
    int a1,a2,a3,b1,b2,b3,c1,c2,c3;
    a1=a2=a3=b1=b2=b3=c1=c2=c3=0;
    int h=im->h;
    int w=im->w;
    
    image* imSobelOut=create_image(im->w, im->h, im->colors);
    double SX[9]={0};
    double SY[9]={0};
    SX[0]=SX[6]=1/2;
    //SX[0]=SX[6]=0;
    SX[3]=2;
    //SX[3]=1/2;
    SX[2]=SX[8]=-1/2;
    //SX[2]=SX[8]=0;
    SX[5]=-2;
    //SX[5]=-1/2;
    SY[0]=SY[2]=1/2;
    //SY[0]=SY[2]=0;
    SY[1]=2;
    //SY[1]=1/2;
    SY[6]=SY[8]=-1/2;
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
    }*/
    write_pgm("test.bmp", im);

    

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
    
    return 0;
}

