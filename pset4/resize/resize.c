/**
 * Resizes a BMP.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // resize factor
    int n = atoi(argv[1]);

    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer less than 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //adjust headers

    // remember original width and height
    int widthIn = bi.biWidth;
    int heightIn = bi.biHeight;

    //resize width and height;
    bi.biWidth *= n;
    bi.biHeight *= n;

    //calculate original padding
    int paddingIn = (4 - (widthIn * sizeof(RGBTRIPLE)) % 4) % 4;

    //calculate output padding
    int paddingOut = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //resize biSizeImage
    bi.biSizeImage = (bi.biWidth + paddingOut) * sizeof(RGBTRIPLE) * abs(bi.biHeight);

    //resize bfSize
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(heightIn); i < biHeight; i++)
    {
        // array to store pixels in
        RGBTRIPLE pixels[widthIn];

        // iterate over pixels in scanline and store values
        for (int j = 0; j < widthIn; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store value in array
            pixels[j] = triple;
        }

        // repeat vertically
        for (int k = 0; k < n; k++)
        {
            // for each value in array,
            for (int j = 0; j < widthIn; j++)
            {
                //  print n times to resize horizontally
                for (int p = 0; p < n; p++)
                {
                    fwrite(&pixels[j], sizeof(RGBTRIPLE), 1, outptr);
                }
                // add output padding
                for (int k = 0; k < paddingOut; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        // skip over input padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
