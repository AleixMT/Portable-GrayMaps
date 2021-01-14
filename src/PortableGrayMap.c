#include "PortableGrayMap.h"


/**
 * Allocates the space required for the data structure.
 *
 * Aborts program if the memory allocation fails.
 * @return Pointer to new data structure.
 */
PortableGrayMap* createPGM(unsigned int cols, unsigned int rows)
{
    PortableGrayMap* image = (PortableGrayMap*) malloc(sizeof(PortableGrayMap));
    if (image == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for the data. Aborting... \n");
        exit(1);
    }

    image->map = (unsigned char *) malloc(sizeof(unsigned char) * cols * rows);
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

// char = 1 Byte = 8 bits --> 2 ^ 8 = 256 ; int = 4 Byte --> 2 ^ 32 = ....
bool load_pgm(PortableGrayMap * image, char * filename)
{
    FILE * file_pointer = fopen(filename, "r");
    if (file_pointer == NULL)
    {
        printf("\nNo es pot obrir");
        exit(1);
    }


    // First line
    char * firstline = malloc(sizeof(char) * 100);
    fgets(firstline, 3, file_pointer);
    if (firstline[0] != 'P' || firstline[1] != '2') return false;

    // Second line
    unsigned int cols, rows;
    if ((fscanf(file_pointer, "%i %i", &cols, &rows)) != 2) return false;
    image = create_pgm(cols, rows);


    // Third line
    unsigned int max_value;
    if ((fscanf(file_pointer, "%i", &max_value)) != 1) return false;
    if (max_value != 255) return false;

    unsigned char temp;
    for (unsigned int r = 0; r < image->rows; r++)
    {
        for (unsigned int c = 0; c < image->cols; c++)
        {
            fscanf(file_pointer, "%hhu", &temp);
            (image->map)[r * image->cols + c] = temp;
        }
    }

    fclose(file_pointer);
    return true;
}

unsigned char mitjana_pixels(PortableGrayMap image)
{
    unsigned int acumulador = 0;
    for (unsigned int r = 0; r < image.rows; r++)
    {
        for (unsigned int c = 0; c < image.cols; c++)
        {
            acumulador += image.map[r * image.cols + c];
        }
    }
    return acumulador / (image.cols * image.rows);
}

void binaritza_imatge(PortableGrayMap image, unsigned char llindar)
{
    for (unsigned int r = 0; r < image.rows; r++)
    {
        for (unsigned int c = 0; c < image.cols; c++)
        {
            if (image.map[r * image.cols + c] > llindar)
            {
                image.map[r * image.cols + c] = 255;
            }
            else
            {
                image.map[r * image.cols + c] = 0;
            }
        }
    }
}


/**
 * 0 --> 0 * 64 = 0
 * 7 --> 0 = 0
 * 63 / 64 * 64 = 0 * 64 = 0
 * 64 / 64 * 64 = 1 * 64 = 64
 * 127 / 64 * 64 = 1 * 64 = 64
 * 128 / 64 * 64 = 2 * 64 = 128 = mida_parts * 2
 * ...
 * 255 --> 3
 *
 * @param image
 * @param parts
 * @return
 */
bool redueix_nivells(PortableGrayMap image, unsigned int parts)
{
    if (256 % parts != 0) return false;
    unsigned int mida_parts = 256 / parts;

    for (unsigned int r = 0; r < image.rows; r++)
    {
        for (unsigned int c = 0; c < image.cols; c++)
        {
            image.map[r * image.cols + c] / mida_parts * mida_parts
        }
    }

    return true;
}

void negativa_imatge(portableGrayMap image)
{
    for (unsigned int i = 0; i < image.cols * image.rows; i++)
    {
        image.map[i] = 255 - image.map[i];
    }
}
/**
char matriz[3][5];
char matriz[12];

matriz[1][2] = matriz[2 * NUMCOLUMNAS + 1] = matriz[filai * NUMCOLUMNAS + columnaj]
matriz[11] = matriz[2 * NUMCOLUMNAS + 1] = matriz[1][2]
[][][][][]
[][][][][]
[][x][][][]

=
        [][][][][],[][][][][],[][][][][]
// r * image->cols + c
**/
