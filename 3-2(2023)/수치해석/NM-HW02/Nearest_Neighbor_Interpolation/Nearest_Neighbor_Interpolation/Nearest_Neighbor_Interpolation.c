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

// Function to perform Nearest Neighbor Interpolation
void NearestNeighborInterpolation(const unsigned char originImage[ORIGIN_WIDTH][ORIGIN_HEIGHT], unsigned char resultImage[RESULT_WIDTH][RESULT_HEIGHT])
{
    for (int i = 0; i < RESULT_HEIGHT; i++)
    {
        for (int j = 0; j < RESULT_WIDTH; j++)
        {
            resultImage[i][j] = originImage[i * ORIGIN_HEIGHT / RESULT_HEIGHT][j * ORIGIN_WIDTH / RESULT_WIDTH];
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

        // Perform Nearest Neighbor Interpolation
        unsigned char resultImageNN[RESULT_WIDTH][RESULT_HEIGHT];
        NearestNeighborInterpolation(originImage, resultImageNN);

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

        // Calculate PSNR for the Nearest Neighbor Interpolation result
        double psnrNN = calculatePSNR(gtImage, resultImageNN);
        printf("Nearest Neighbor PSNR for image %d: %.2f dB\n", imageIndex + 1, psnrNN);

        // Save the Nearest Neighbor Interpolation result to a file
        char resultFileNameNN[50];
        sprintf(resultFileNameNN, "dataset/result/Nearest_Neighbor_%d.raw", imageIndex + 1);

        FILE* outputFileNN = fopen(resultFileNameNN, "wb");
        if (outputFileNN == NULL)
        {
            printf("Failed to create result image files for Nearest Neighbor interpolation of image %d.\n", imageIndex + 1);
            return 1;
        }

        for (int i = 0; i < RESULT_HEIGHT; i++)
        {
            for (int j = 0; j < RESULT_WIDTH; j++)
            {
                unsigned char pixelNN = resultImageNN[i][j];
                fwrite(&pixelNN, 1, 1, outputFileNN);
            }
        }
        fclose(outputFileNN);
    }
    return 0;
}