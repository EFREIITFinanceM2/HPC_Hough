//
//  hough.h
//  HPC_Hough
//
//  Created by ZN-MAC on 14/11/21.
//  Copyright (c) 2014年 ZHANG Nan. All rights reserved.
//

#ifndef __HPC_Hough__hough__
#define __HPC_Hough__hough__

#include <stdio.h>
#include "pgm.h"
#include <math.h>
#include <stdlib.h>

#define WH 100
#define THRESHOLD_HOUGH 100
#define PI 3.14
#define NUM_LINES 100

void hough(char* input, char* output);

#endif /* defined(__HPC_Hough__hough__) */
