// Includes
#include <stdio.h>
#include <stdbool.h>  // To use booleans
#include <stdlib.h>

// Type definition for the list itself
typedef struct PortableGrayMap {
    unsigned char * Map;
    unsigned int cols;
    unsigned int rows;
} PortableGrayMap;

