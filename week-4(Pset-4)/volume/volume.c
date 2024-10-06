// Modifies the volume of an audio file
#include <cs50.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        fclose(input);
        return 1;
    }

    float factor = atof(argv[3]);

    // Ensure factor is non-negative
    if (factor < 0)
    {
        printf("Factor must be non-negative.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);

    // Read samples from input file, adjust volume, and write to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        // Adjust sample value and ensure it is within the 16-bit range
        float scaled = buffer * factor;
        if (scaled > 32767)
            scaled = 32767;
        if (scaled < -32768)
            scaled = -32768;

        buffer = (int16_t) scaled;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
