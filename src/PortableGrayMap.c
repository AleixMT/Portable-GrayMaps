#include "PortableGrayMap.h"


/**
 * Allocates the space required for the data structure.
 *
 * Aborts program if the memory allocation fails.
 * @return Pointer to new data structure.
 */
PortableGrayMap* create_pgm(unsigned int cols, unsigned int rows)
{
    PortableGrayMap* image = (PortableGrayMap*) malloc(sizeof(PortableGrayMap));
    if (image == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for the data. Aborting... \n");
        exit(1);
    }

    image->map = malloc(sizeof(unsigned int) * cols * rows);
    if (image->map == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for the data. Aborting... \n");
        exit(1);
    }
    image->cols = cols;
    image->rows = rows;

    return image;
}


/**
 * Loads an image with the filename provided by parameter.
 *
 * Un fitxer que conté una imatge PGM té les especificacions següents:
 * - La primera línia conté el text “P2”, és a dir, el caràcter “P” i el caràcter “2”. Amb això s’indica que el fitxer és un PGM en mode ASCII.
 * - La segona línia conté un número que indica quantes columnes (NC) té la imatge (amplada) i un número que indica quantes files (NF) té la imatge (alçada).
 * - La tercera línia indica quin és el valor màxim de píxel que es podria trobar. Com que treballarem amb imatges de 256 tons diferents, aquest sempre serà 255.
 * - Tot seguit hi ha NC x NF valors que conformen els píxels de la imatge en forma de llista.
 *
 * @param image. Out data. Makes image variable point to a data structure containing the image.
 * @param filename
 * @return
 */
bool load_pgm(PortableGrayMap * image, char * filename)
{
    FILE * file_pointer = fopen(filename, "r");

    // First line
    char * firstline = malloc(sizeof(char) * 3);
    if ((fscanf(file_pointer, "%c%c", & firstline[0], & firstline[1])) != 2) return false;
    if (firstline[0] != 'P' || firstline[1] != '2') return false;
    if (fgets(firstline, 3, file_pointer) == NULL) return false;

    fclose(file_pointer);
    return true;
}

