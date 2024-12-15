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

void SixPointInterpolation(const unsigned char originImage[ORIGIN_WIDTH][ORIGIN_HEIGHT], unsigned char resultImage[RESULT_WIDTH][RESULT_HEIGHT])
{
    // Define the interpolation coefficients
    double weights[6] = { 1.0, -5.0, 20.0, 20.0, -5.0, 1.0 };

    // Perform Six-Tap Linear Interpolation
    for (int y = 0; y < RESULT_HEIGHT; y++)
    {
        for (int x = 0; x < RESULT_WIDTH; x++)
        {
            // Map the coordinates in the result image to the coordinates in the original image
            double x_original = x * (ORIGIN_WIDTH - 1) / (double)(RESULT_WIDTH - 1);
            double y_original = y * (ORIGIN_HEIGHT - 1) / (double)(RESULT_HEIGHT - 1);

            // Determine the relevant data points for interpolation
            int x1 = (int)x_original;
            int y1 = (int)y_original;
            int x2 = x1 + 1;
            int y2 = y1 + 1;

            // Perform six-tab linear interpolation
            double interpolatedValue = 0.0;
            if (x2 < ORIGIN_WIDTH && y2 < ORIGIN_HEIGHT)
            {
                double dx = x_original - x1;
                double dy = y_original - y1;

                double p1 = originImage[y1][x1];
                double p2 = originImage[y1][x2];
                double p3 = originImage[y2][x1];
                double p4 = originImage[y2][x2];
                double p5 = originImage[y1][x1 + 2];
                double p6 = originImage[y2][x1 + 2];

                // Apply the weights for interpolation
                interpolatedValue = weights[0] * p1 + weights[1] * p2 + weights[2] * p3 + weights[3] * p4 + weights[4] * p5 + weights[5] * p6;

                // Normalize the interpolated value
                interpolatedValue /= 32.0;
            }

            // Store the interpolated value in the result image
            resultImage[y][x] = (unsigned char)interpolatedValue;
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

        // Perform Six-Tap Linear Interpolation
        unsigned char resultImageLinear[RESULT_WIDTH][RESULT_HEIGHT];
        SixPointInterpolation(originImage, resultImageLinear);

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

        // Calculate PSNR for the Six-Tap Linear Interpolation result
        double psnrLinear = calculatePSNR(gtImage, resultImageLinear);
        printf("Six-Tap Linear Interpolation PSNR for image %d: %.2f dB\n", imageIndex + 1, psnrLinear);

        // Save the Six-Tap Linear Interpolation result to a file
        char resultFileNameLinear[50];
        sprintf(resultFileNameLinear, "dataset/result/Six-Tap_Linear_Interpolation_%d.raw", imageIndex + 1);

        FILE* outputFileLinear = fopen(resultFileNameLinear, "wb");
        if (outputFileLinear == NULL)
        {
            printf("Failed to create result image files for Six-Tap Linear interpolation of image %d.\n", imageIndex + 1);
            return 1;
        }
        for (int i = 0; i < RESULT_HEIGHT; i++)
        {
            for (int j = 0; j < RESULT_WIDTH; j++)
            {
                unsigned char pixelLinear = resultImageLinear[i][j];
                fwrite(&pixelLinear, 1, 1, outputFileLinear);
            }
        }
        fclose(outputFileLinear);
    }
    return 0;
}