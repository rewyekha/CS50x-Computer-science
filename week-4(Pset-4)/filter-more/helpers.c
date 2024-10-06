#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the RGB values
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;

            // Compute the average value
            BYTE average = round((red + green + blue) / 3.0);

            // Set the pixel to the average value
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store the blurred result
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int count = 0;

            // Iterate over the 3x3 box centered at (i, j)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the neighboring pixel is within the bounds of the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Add the RGB values of the neighboring pixel
                        red_sum += image[ni][nj].rgbtRed;
                        green_sum += image[ni][nj].rgbtGreen;
                        blue_sum += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average RGB values
            temp[i][j].rgbtRed = round(red_sum / (float) count);
            temp[i][j].rgbtGreen = round(green_sum / (float) count);
            temp[i][j].rgbtBlue = round(blue_sum / (float) count);
        }
    }

    // Copy the blurred result back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary image to store the edge detection result
    RGBTRIPLE temp[height][width];

    // Sobel operator kernels
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over each pixel (excluding the borders)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_x = 0, green_x = 0, blue_x = 0;
            int red_y = 0, green_y = 0, blue_y = 0;

            // Apply Sobel operators
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the neighboring pixel is within the bounds of the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Compute the gradients
                        red_x += image[ni][nj].rgbtRed * gx[di + 1][dj + 1];
                        green_x += image[ni][nj].rgbtGreen * gx[di + 1][dj + 1];
                        blue_x += image[ni][nj].rgbtBlue * gx[di + 1][dj + 1];

                        red_y += image[ni][nj].rgbtRed * gy[di + 1][dj + 1];
                        green_y += image[ni][nj].rgbtGreen * gy[di + 1][dj + 1];
                        blue_y += image[ni][nj].rgbtBlue * gy[di + 1][dj + 1];
                    }
                }
            }

            // Compute the magnitude of the gradients
            int red = round(sqrt(red_x * red_x + red_y * red_y));
            int green = round(sqrt(green_x * green_x + green_y * green_y));
            int blue = round(sqrt(blue_x * blue_x + blue_y * blue_y));

            // Clamp the values to be within [0, 255]
            temp[i][j].rgbtRed = red > 255 ? 255 : red;
            temp[i][j].rgbtGreen = green > 255 ? 255 : green;
            temp[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }

    // Copy the edge detection result back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
