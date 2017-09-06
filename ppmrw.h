#ifndef PPMRW_H
#define PPMRW_H

// Error code constants
#define NO_STRING_FOUND -1

// Numeric constants
#define STRING_MAX_BUFFER 32

// String constants
#define USAGE_MESSAGE "\
Usage: ppmrw convert_to_number input_file output_file\n\
  convert_to_number: PPM format to convert to (3 or 6)\n\
  input_file: input PPM file name\n\
  output_file: out PPM file name\n"

// Include standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
