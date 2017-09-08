# Project 1 - Images
A simple PPM image converter program written in C.

This program uses a command line interface and allows users to convert to and from the binary and ascii PPM formats (P3 and P6). By allowing the user to specify the input file, the output file, and the desired format, the program is able to parse and convert any P3 or P6 file.

The program also features robust error handling for both the command line parameters and the PPM image format.


## Usage
Get a local copy of the repository by downloading the zip or using `git clone`. This includes a makefile which allows you to simply `make` the project as long as you are in a *UNIX-like* environment.

Then, depending on your operating system/environment, you can run the program by using one of the following commands:

```
./ppmrw.exe 3 input.ppm output.ppm
```
```
ppmrw 3 input.ppm output.ppm
```


## Author
Peter Huettl - [ph289@nau.edu](mailto:ph289@nau.edu)

![test](examples/in-p3.png)
