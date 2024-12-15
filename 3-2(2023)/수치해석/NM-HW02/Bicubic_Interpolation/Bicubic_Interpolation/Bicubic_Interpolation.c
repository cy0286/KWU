#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

// Define image dimensions
#define ORIGIN_WIDTH 128
#define ORIGIN_HEIGHT 128
#define RESULT_WIDTH 512
#define RESULT_HEIGHT 512

// Cubic polynomial function for Bicubic Interpolation
double cubicPolynomial(double t)
{
    if (t < 0)
    {
        t = -t; // Ensure t is non-negative
    }
    if (t < 1)
    {
        return (1.5 * t * t * t - 2.5 * t * t + 1.0); // Cubic polynomial formula for the first segment
    }
    else if (t < 2)
    {
        return (-0.5 * t * t * t + 2.5 * t * t - 4.0 * t + 2.0); // Cubic polynomial formula for the second segment
    }
    else
    {
        return 0.0; // Return 0 for values
    }
}

// Function to perform Bicubic Interpolation
void BicubicInterpolation(const unsigned char originImage[ORIGIN_WIDTH][ORIGIN_HEIGHT], unsigned char resultImage[RESULT_WIDTH][RESULT_HEIGHT])
{
    for (int y = 0; y < RESULT_HEIGHT; y++)
    {
        for (int x = 0; x < RESULT_WIDTH; x++)
        {
            // Calculate normalized coordinates
            double p = (double)x / (double)(RESULT_WIDTH - 1) * (ORIGIN_WIDTH - 1);
            double q = (double)y / (double)(RESULT_HEIGHT - 1) * (ORIGIN_HEIGHT - 1);

            // Find the nearest pixel position
            int x0 = (int)p - 1;
            int y0 = (int)q - 1;

            // Calculate subpixel position
            double dx = p - (double)x0;
            double dy = q - (double)y0;

            double result = 0.0;

            // Iterate over a 4x4 pixel grid
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    int xi = x0 + i;
                    int yj = y0 + j;

                    if (xi >= 0 && xi < ORIGIN_WIDTH && yj >= 0 && yj < ORIGIN_HEIGHT)
                    {
                        double weight_x = cubicPolynomial(dx - i);
                        double weight_y = cubicPolynomial(dy - j);

                        // Calculate the final weight as the product of weight_x and weight_y
                        double weight = weight_x * weight_y;

                        result += originImage[yj][xi] * weight;
                    }
                }
            }
            resultImage[y][x] = (unsigned char)result;
        }
    }
}

// Function to calculate PSNR between two images
double calculatePSNR(const unsigned char originalImage[RESULT_WIDTH][RESULT_HEIGHT], const unsigned char resultImage[RESULT_WIDTH][RESULT_HEIGHT])
{
    double mse = 0.0; // Initialize the Mean Squared Error
    int imageSize = RESULT_WIDTH * RESULT_HEIGHT; // Calculate the image size

    // Iterate through all pixels of the images to compute MSE
    for (int i = 0; i < RESULT_HEIGHT; i++)
    {
        for (int j = 0; j < RESULT_WIDTH; j++)
        {
            mse += pow(originalImage[i][j] - resultImage[i][j], 2);
        }
    }
    mse /= imageSize;
    if (mse == 0.0)
    {
        return 100.0;
    }
    double maxPixelValue = 255.0;  // Set the maximum pixel value of the image
    double psnr = 10.0 * log10((maxPixelValue * maxPixelValue) / mse);
    return psnr;
}

int main()
{
    // Create the result directory
    mkdir("dataset/result", 0755);

    // Define file paths
    const char* lrimageFiles[] =
    {
        "dataset/lr/Barbara_128x128_yuv400_8bit.raw",
        "dataset/lr/Couple_128x128_yuv400_8bit.raw",
        "dataset/lr/Lena_128x128_yuv400_8bit.raw"
    };

    const char* gtImageFiles[] =
    {
        "dataset/gt/Barbara_512x512_yuv400_8bit.raw",
        "dataset/gt/Couple_512x512_yuv400_8bit.raw",
        "dataset/gt/Lena_512x512_yuv400_8bit.raw"
    };

    // Image processing loop
    for (int imageIndex = 0; imageIndex < 3; imageIndex++)
    {
        // Open the low-resolution image
        FILE* inputFile = fopen(lrimageFiles[imageIndex], "rb");
        if (inputFile == NULL)
        {
            printf("Failed to open image file %d.\n", imageIndex + 1);
            return 1;
        }

        // Read the low-resolution image
        unsigned char originImage[ORIGIN_WIDTH][ORIGIN_HEIGHT];
        fread(originImage, 1, ORIGIN_WIDTH * ORIGIN_HEIGHT, inputFile);
        fclose(inputFile);

        // Perform Bicubic Interpolation
        unsigned char resultImageBC[RESULT_WIDTH][RESULT_HEIGHT];
        BicubicInterpolation(originImage, resultImageBC);

        // Open the ground truth image
        FILE* gtFile = fopen(gtImageFiles[imageIndex], "rb");
        if (gtFile == NULL)
        {
            printf("Failed to open ground truth image file %d.\n", imageIndex + 1);
            return 1;
        }

        // Read the ground truth image
        unsigned char gtImage[RESULT_WIDTH][RESULT_HEIGHT];
        fread(gtImage, 1, RESULT_WIDTH * RESULT_HEIGHT, gtFile);
        fclose(gtFile);

        // Calculate PSNR for the  Bicubic Interpolation result
        double psnrBC = calculatePSNR(gtImage, resultImageBC);
        printf("Bicubic Interpolation PSNR for image %d: %.2f dB\n", imageIndex + 1, psnrBC);

        // Save the Bicubic Interpolation result to a file
        char resultFileNameBC[50];
        sprintf(resultFileNameBC, "dataset/result/Bicubic_Interpolation_%d.raw", imageIndex + 1);

        FILE* outputFileBC = fopen(resultFileNameBC, "wb");
        if (outputFileBC == NULL)
        {
            printf("Failed to create result image files for Bicubic interpolation of image %d.\n", imageIndex + 1);
            return 1;
        }

        for (int i = 0; i < RESULT_HEIGHT; i++)
        {
            for (int j = 0; j < RESULT_WIDTH; j++)
            {
                unsigned char pixelBC = resultImageBC[i][j];
                fwrite(&pixelBC, 1, 1, outputFileBC);
            }
        }
        fclose(outputFileBC);
    }
    return 0;
}