#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

  // Check for the appropriate number of parameters
  if (argc != 4) {
    printf("Usage: ppmrw convert_to_number input_file output_file\n");
    printf("  convert_to_number: PPM format to convert to (3 or 6)\n");
    printf("  input_file: input PPM file name\n");
    printf("  output_file: out PPM file name\n");
    return 1;
  }

  // Save command line parameters
  int convertToFormat = atoi(argv[1]);
  char *inputFName = argv[2];
  char *outputFName = argv[3];

  // Validate conversion number
  if (convertToFormat != 3 && convertToFormat != 6) {
    printf("Error: Invalid PPM format number, use 3 or 6");
    return 1;
  }

  return 0;
}
