#ifndef PPMRW_H
#define PPMRW_H

// Error code constants
#define NO_STRING_FOUND -1

// Numeric constants
#define STRING_MAX_BUFFER 32

// Include standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> // isspace

// Define types to be used in ppmrw.c 
typedef struct Pixel Pixel;

struct Pixel {
  unsigned char r, g, b, a;
};

/**
 * Gets next series of ASCII characters from a file handle
 * while ignoring leading whitespace
 * 
 * @param  output     character pointer to memory to save output
 * @param  fileHandle file to be parsed for next string
 * @return            success status of function, NO_STRING_FOUND on error
 */
int getNextString(char *output, FILE *fileHandle);

#endif  // PPMRW_H
