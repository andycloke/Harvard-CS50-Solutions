/**
 * recovers JPEGs from a file
 **/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure correct image
    if (argc != 2)
    {
        fprintf(stderr, "Usage ./recover forensicimage\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file (memory card)
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 1;
    }

    // bSize
    int bSize = 512;

    // counter for jpg filenames
    int counter = 0;

    // storage for buffer
    unsigned char* buffer = malloc(bSize);


    // output pointer;
    FILE *img = NULL;

    // repeat until end of card (when number of bytes returned will < bSize)
    while (fread(buffer, 1, bSize, inptr) == bSize)
    {

        // start of new JPEG?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if jpegs already found, close them
            if (counter)
            {
                fclose(img);
            }

            char *filename = NULL;

            // create name for new file
            sprintf(filename, "%03i.jpg", counter);

            // create output file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not create %s.jpg \n", filename);
                return 1;
            }

            // increment counter
            counter++;
        }

        // if we have hit jpegs, write to output file
        if (img != NULL)
        {
        fwrite(buffer, bSize, 1, img);
        }
    }

    // free buffer
    free(buffer);

    // close input file
    fclose(inptr);

    // close output jpg if there is one
    if (img != NULL)
    {
        fclose(img);
    }
}
