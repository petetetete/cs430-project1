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
  output->pixels = malloc(output->width * output->height * 4);

  return 0;
}


int main(int argc, char *argv[]) {

  // Handle the -h help flag
  // Use stdout and a return code of 0 because the program was used correctly
  if (argc == 2 && strcmp(argv[1], "-h") == 0) {
    fprintf(stdout, USAGE_MESSAGE);
    return 0;
  }

  // Check for the appropriate number of parameters
  // Use stderr and a return code of 1 because the program was used incorrectly
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

  // Clean up program
  fclose(inputFH);

  return 0;
}
