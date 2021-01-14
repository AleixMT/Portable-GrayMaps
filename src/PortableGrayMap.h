// Includes
#include <stdio.h>
#include <stdbool.h>  // To use booleans
#include <stdlib.h>
#include <string.h>

// Type definition for the list itself
typedef struct PortableGrayMap {
    unsigned char * map;
    unsigned int cols;
    unsigned int rows;
} PortableGrayMap;


PortableGrayMap* create_pgm(unsigned int cols, unsigned int rows);
bool load_pgm(PortableGrayMap * image, char * filename);

unsigned char mitjana_pixels(PortableGrayMap image);
void binaritza_imatge(PortableGrayMap image, unsigned char llindar);
bool redueix_nivells(PortableGrayMap image, unsigned int parts);
void negativa_imatge(portableGrayMap image);