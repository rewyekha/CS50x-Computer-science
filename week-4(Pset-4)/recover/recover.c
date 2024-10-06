#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

// Define the JPEG signature
const uint8_t JPEG_HEADER[4] = {0xff, 0xd8, 0xff};
const uint8_t JPEG_HEADER_MASK = 0xf0;
const uint8_t JPEG_HEADER_PREFIX = 0xe0;

// Function prototypes
bool is_jpeg_start(const uint8_t buffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];
    FILE *img = NULL;
    int img_count = 0;
    bool in_jpeg = false;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JPEGs from the data
        // Check for JPEG start
        if (is_jpeg_start(buffer))
        {
            // If we are currently writing a JPEG, close it
            if (in_jpeg)
            {
                fclose(img);
            }
            else
            {
                in_jpeg = true;
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03i.jpg", img_count++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(card);
                return 1;
            }
        }
        // If we are in a JPEG, write to the file
        if (in_jpeg)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }
    // Close the last file if open
    if (in_jpeg)
    {
        fclose(img);
    }

    // Close the memory card
    fclose(card);
    return 0;
}

// Function to check if the buffer contains a JPEG start signature
bool is_jpeg_start(const uint8_t buffer[BLOCK_SIZE])
{
    return buffer[0] == JPEG_HEADER[0] && buffer[1] == JPEG_HEADER[1] &&
           buffer[2] == JPEG_HEADER[2] && (buffer[3] & JPEG_HEADER_MASK) == JPEG_HEADER_PREFIX;
}
