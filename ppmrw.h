#ifndef PPMRW_H
#define PPMRW_H

// Include standard libraries
#include <stdlib.h>
#include <stdio.h>

// Define types to be used in ppmrw.c 
typedef struct Pixel Pixel;

struct Pixel {
  unsigned char r, g, b, a;
};

#endif  // PPMRW_H
