#include "PortableGrayMap.h"
int main(int nargs, char* args[])
{
    PortableGrayMap * image = (PortableGrayMap *) malloc(sizeof(PortableGrayMap));
    load_pgm(image, "baboon.pgm");
}


