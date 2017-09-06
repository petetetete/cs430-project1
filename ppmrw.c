// Include ppmrw header file
#include "ppmrw.h"

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

  // Validate conversion number
  if (convertToFormat != 3 && convertToFormat != 6) {
    fprintf(stderr, "Error: Invalid PPM format number, use 3 or 6\n");
    return 1;
  }

  FILE *inputFH;
  if (!(inputFH = fopen(inputFName, "r"))) {
    fprintf(stderr, "Error: No input file of name '%s' found\n", inputFName);
    return 1;
  }

  return 0;
}
