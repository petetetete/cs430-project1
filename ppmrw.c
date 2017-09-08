// Include ppmrw header file
#include "ppmrw.h"


int getNextString(char *output, FILE *file) {

  char symbol;
  output[0] = 0; // Initialize input
  int isComment = 0; // Flag as to whether or not we're looking at a comment

  // Skip leading white space and comments
  while (1) {
    symbol = fgetc(file);

    // If we hit an EOF before a non-whitespace character
    if (symbol == EOF) {
      return NO_STRING_FOUND;
    }

    // Reset flag because we can no longer be in a comment
    else if (symbol == '\n') {
      isComment = 0;
    }

    // Save first non-whitespace character we hit that isn't in a comment
    else if (!isspace(symbol) && !isComment) {

      if (symbol == '#') {
        isComment = 1;
      }
      else {
        snprintf(output, STRING_MAX_BUFFER, "%s%c", output, symbol);
        break;
      }
      
    }
  }

  // Copy all characters to the output until we hit another whitespace or EOF
  while ((symbol = fgetc(file)) != EOF && !isspace(symbol)) {
    snprintf(output, STRING_MAX_BUFFER, "%s%c", output, symbol);
  }

  // If we instantly hit EOF after skipping whitespace, there was no real string
  if (symbol == EOF && output[0] == '\0') {
    return NO_STRING_FOUND;
  }
  else {
    return 0;
  }

}


int readPPM(PPMImage *output, FILE *file) {

  // Temporary variables used to store strings that are found
  char width[STRING_MAX_BUFFER];
  char height[STRING_MAX_BUFFER];
  char maxColorValue[STRING_MAX_BUFFER];

  // Temporary variables to store the r, g, b values in
  char red[STRING_MAX_BUFFER];
  char green[STRING_MAX_BUFFER];
  char blue[STRING_MAX_BUFFER];
  char alpha[STRING_MAX_BUFFER];

  // Get meta data from PPM file
  getNextString(output->magicNumber, file);
  getNextString(width, file);
  getNextString(height, file);
  getNextString(maxColorValue, file);

  // TODO: Handle errors of getting strings, and ensuring that data is accurate

  // Save strings into PPMImage object
  output->width = atoi(width);
  output->height = atoi(height);
  output->maxColorValue = atoi(maxColorValue);

  // Allocate memory for pixel array on object
  output->pixels = malloc(output->width*output->height*4);

  // If the magic number is P6, read the binary straight into the array
  if (strcmp(output->magicNumber, "P6") == 0) {
    fread(output->pixels, output->width*output->height*4, 1, file);
  }
  else {
    for (int i = 0; i < output->width*output->height; i++) {

      getNextString(red, file);
      getNextString(green, file);
      getNextString(blue, file);
      getNextString(alpha, file);

      output->pixels[i].r = atoi(red);
      output->pixels[i].g = atoi(green);
      output->pixels[i].b = atoi(blue);
      output->pixels[i].a = atoi(alpha);
    }
  }

  return 0;
}


int writePPM(PPMImage *image, FILE *file, int newFormat) {

  // Populate header
  fprintf(file, "P%d\n", newFormat);
  fprintf(file, "%d %d\n", image->width, image->height);
  fprintf(file, "%d\n", image->maxColorValue);

  if (newFormat == 6) {
    fwrite(image->pixels, image->width*image->height*4, 1, file);
  }
  else {
    for (int i = 0; i < image->width*image->height; i++) {
      fprintf(file, "%d %d %d %d\n",
        image->pixels[i].r,
        image->pixels[i].g,
        image->pixels[i].b,
        image->pixels[i].a);
    }
  }

}


int main(int argc, char *argv[]) {

  // Check for the appropriate number of parameters
  if (argc != 4) {
    fprintf(stderr, USAGE_MESSAGE);
    return 1;
  }

  // Save command line parameters
  int convertToFormat = atoi(argv[1]);
  char *inputFName = argv[2];
  char *outputFName = argv[3];

  // Initialize variables to be used in program
  FILE *inputFH;
  FILE *outputFH;

  // Validate conversion number
  if (convertToFormat != 3 && convertToFormat != 6) {
    fprintf(stderr, "Error: Invalid PPM format number, use 3 or 6\n");
    return 1;
  }

  // Validate input file name
  if (!(inputFH = fopen(inputFName, "r"))) {
    fprintf(stderr, "Error: No input file of name '%s' found\n", inputFName);
    return 1;
  }

  PPMImage *input = malloc(sizeof(PPMImage));
  readPPM(input, inputFH);

  outputFH = fopen(outputFName, "w");
  writePPM(input, outputFH, convertToFormat);

  // Clean up program
  fclose(inputFH);
  fclose(outputFH);

  return 0;
}
