#include "image.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

/* NOTE: this function assumes that the given .bmp file is tricolor 24-bit with a 54 byte header
 * This is the case ~95% of the time
 * No resolution data is returned and must be gotten another way for supplying said info to the shader
 * The returned data is dynamic and must be freed by the programmer after it has been used
 */
char* getBMPData(const char* filename) {
	std::ifstream inp;
	char header[54];

	inp.open(filename, std::ios::binary);
	if (!inp) {
		std::cout << "ERROR: failed to open bitmap file " << filename << std::endl;
		return NULL;
	}

	inp.read(header, 54); //read header

	unsigned int width = (3 * *(int*)&header[0x12]);
	unsigned int height = *(int*)&header[0x16];
	unsigned int start = *(int*)&header[0x0A];

	inp.seekg(start - 54, std::ios::cur); //eat up gap

	unsigned int padSize = (width % 4); //bitmap padding amount
	unsigned int padStart = width - padSize; //start of padding per line

	char* data = new char[(width * height) - (height * padSize) + 1];
	data[(width * height) - (height * padSize)] = '\0';

	for (unsigned int h = 0; h < height; h++) {
		for (unsigned int w = 0; w < width; w++) {
			if (w < padStart) {
				inp.get(data[(width * h) + w]);
			}
		}
	}

	inp.close();
	return data;
}


/* This function returns either the width or height of a BMP based on the dim parameter
 * 0/'w'/'W' = width
 * 1/'h'/'H' = height
 */
unsigned int getBMPDimension(const char* filename, const char dim) {
	std::ifstream inp;
	char header[54];
	unsigned int size;

	inp.open(filename);
	if (!inp) {
		std::cout << "ERROR: failed to open bitmap file " << filename << std::endl;
		return NULL;
	}

	inp.read(header, 54); //eat up header

	switch (dim) {
		case 0:
		case 'w':
		case 'W':
			size = *(int*)&header[0x12];
			break;
		case 1:
		case 'h':
		case 'H':
			size = *(int*)&header[0x16];
			break;
		default:
			size = 0; //you messed up
			break;
	}

	inp.close();
	return size;
}