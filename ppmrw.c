// Include ppmrw header file
#include "ppmrw.h"


int getNextString(char *output, FILE *fileHandle) {

  char symbol;

  // Skip leading white space
  while (1) {
    symbol = fgetc(fileHandle);

    // If we hit an EOF before a non-whitespace character
    if (symbol == EOF) {
      return NO_STRING_FOUND;
    }

    // Save first non-whitespace character we hit
    else if (!isspace(symbol)) {
      snprintf(output, STRING_MAX_BUFFER, "%s%c", output, symbol);
      break;
    }
  }

  // Copy all characters to the output until we hit another whitespace or EOF
  while ((symbol = fgetc(fileHandle)) != EOF && !isspace(symbol)) {
    sprintf(output, "%s%c", output, symbol);
  }

  // If we instantly hit EOF after skipping whitespace, there was no real string
  if (symbol == EOF) {
    return NO_STRING_FOUND;
  }

  // String successfully found
  else {
    return 0;
  }

}

int main(int argc, char *argv[]) {

  // Check for the appropriate number of parameters
  if (argc != 4) {

    // Print usage message to stderr because they mis-used the program
    fprintf(stderr, "Usage: ppmrw convert_to_number input_file output_file\n"
                    "  convert_to_number: PPM format to convert to (3 or 6)\n"
                    "  input_file: input PPM file name\n"
                    "  output_file: out PPM file name\n");
    return 1;
  }

  // Save command line parameters
  int convertToFormat = atoi(argv[1]);
  char *inputFName = argv[2];
  char *outputFName = argv[3];

  // Initialize variables to be used in program
  FILE *inputFH;
  char *magicNumber;

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

  // Test finding magic number
  magicNumber = malloc(sizeof(char) * STRING_MAX_BUFFER);
  getNextString(magicNumber, inputFH);
  printf(magicNumber);


  // Clean up program
  fclose(inputFH);

  return 0;
}
