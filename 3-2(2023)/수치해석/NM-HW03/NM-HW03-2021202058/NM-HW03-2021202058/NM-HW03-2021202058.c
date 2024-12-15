#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>

// Define image dimensions
#define ORIGIN_WIDTH 256
#define ORIGIN_HEIGHT 256
#define RESULT_WIDTH 512
#define RESULT_HEIGHT 512
#define PADDING_VALUE 3
#define MATRIX_SIZE 49
#define NUM_PIXELS (ORIGIN_WIDTH * ORIGIN_HEIGHT)

// Define image array
unsigned char image[ORIGIN_HEIGHT][ORIGIN_WIDTH];
unsigned char paddedimage[ORIGIN_HEIGHT + 2 * PADDING_VALUE][ORIGIN_WIDTH + 2 * PADDING_VALUE];
unsigned char resultImage[ORIGIN_HEIGHT][ORIGIN_WIDTH];
int group_count[25];

char Mask_V[7][7] = { {1,2,2,0,-2,-2,-1},
                 {1,2,3,0,-3,-2,-1},
                 {1,3,4,0,-4,-3,-1},
                 {1,4,5,0,-5,-4,-1},
                 {1,3,4,0,-4,-3,-1},
                 {1,2,3,0,-3,-2,-1},
                 {1,2,2,0,-2,-2,-1}
};
char Mask_H[7][7] = { {-1,-1,-1,-1,-1,-1,-1},
                 {-2,-2,-3,-4,-3,-2,-2},
                 {-2,-3,-4,-5,-4,-3,-2},
                 {0,0,0,0,0,0,0},
                 {2,3,4,5,4,3,2},
                 {2,2,3,4,3,2,2},
                 {1,1,1,1,1,1,1}
};
char Mask_D135[7][7] = { {0,3,2,1,1,1,1},
                        {-3,0,4,3,2,1,1},
                        {-2,-4,0,5,4,2,1},
                        {-1,-3,-5,0,5,3,1},
                        {-1,-2,-4,-5,0,4,2},
                        {-1,-1,-2,-3,-4,0,3},
                         {-1,-1,-1,-1,-2,-3,0}
};
char Mask_D45[7][7] = { {-1,-1,-1,-1,-2,-3,0},
                        {-1,-1,-2,-3,-4,0,3},
                        {-1,-2,-4,-5,0,4,2},
                        {-1,-3,-5,0,5,3,1},
                        {-2,-4,0,5,4,2,1},
                        {-3,0,4,3,2,1,1},
                        {0,3,2,1,1,1,1},
};

// Function to compute PSNR between two images
double PSNR(unsigned char originalImage[RESULT_HEIGHT][RESULT_WIDTH], unsigned char generatedImage[RESULT_HEIGHT][RESULT_WIDTH])
{
    double mse = 0.0;

    // Compute Mean Squared Error (MSE)
    for (int i = 0; i < RESULT_HEIGHT; ++i)
    {
        for (int j = 0; j < RESULT_WIDTH; ++j)
        {
            mse += pow((double)originalImage[i][j] - generatedImage[i][j], 2);
        }
    }

    mse /= (double)(RESULT_HEIGHT * RESULT_WIDTH);

    // Compute PSNR
    double psnr = 10.0 * log10((255 * 255) / mse);

    return psnr;
}

void padImage()
{
    for (int i = PADDING_VALUE; i < ORIGIN_HEIGHT + PADDING_VALUE; i++)
    {
        for (int j = PADDING_VALUE; j < ORIGIN_WIDTH + PADDING_VALUE; j++)
        {
            int originalX;
            int originalY;

            if (j - PADDING_VALUE >= ORIGIN_WIDTH) 
            {
                originalX = ORIGIN_WIDTH - 1;
            }
            else 
            {
                originalX = j - PADDING_VALUE;
            }

            if (i - PADDING_VALUE >= ORIGIN_HEIGHT) 
            {
                originalY = ORIGIN_HEIGHT - 1;
            }
            else 
            {
                originalY = i - PADDING_VALUE;
            }
            paddedimage[i][j] = image[originalY][originalX];
        }
    }
}

// Function to multiply two matrices (dot product)
void matrixDotProduct(double matrix1[MATRIX_SIZE][MATRIX_SIZE], double matrix2[MATRIX_SIZE][MATRIX_SIZE], double result[MATRIX_SIZE][MATRIX_SIZE]) 
{
    for (int i = 0; i < MATRIX_SIZE; ++i) 
    {
        for (int j = 0; j < MATRIX_SIZE; ++j) 
        {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) 
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Function to find the inverse of a matrix using Gaussian elimination
int matrixInverse(double matrix[MATRIX_SIZE][MATRIX_SIZE], double inverse[MATRIX_SIZE][MATRIX_SIZE]) 
{
    // Initialize the inverse matrix as the identity matrix
    for (int i = 0; i < MATRIX_SIZE; ++i) 
    {
        for (int j = 0; j < MATRIX_SIZE; ++j) 
        {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform Gaussian elimination to obtain the inverse
    for (int k = 0; k < MATRIX_SIZE; ++k) 
    {
        double pivot = matrix[k][k];

        if (pivot == 0.0) 
        {
            return 0; 
        }

        // Scale the row to make the pivot equal to 1
        for (int j = 0; j < MATRIX_SIZE; ++j) 
        {
            matrix[k][j] /= pivot;
            inverse[k][j] /= pivot;
        }

        // Eliminate other rows
        for (int i = 0; i < MATRIX_SIZE; ++i) 
        {
            if (i != k) 
            {
                double factor = matrix[i][k];
                for (int j = 0; j < MATRIX_SIZE; ++j) {
                    matrix[i][j] -= factor * matrix[k][j];
                    inverse[i][j] -= factor * inverse[k][j];
                }
            }
        }
    }
    return 1;
}

int main()
{
	double XT[MATRIX_SIZE][MATRIX_SIZE];
	double XTX[MATRIX_SIZE][MATRIX_SIZE];
	double XTX_inverse[MATRIX_SIZE][MATRIX_SIZE];

	unsigned char h[ORIGIN_HEIGHT][ORIGIN_WIDTH];
	unsigned char v[ORIGIN_HEIGHT][ORIGIN_WIDTH];
	unsigned char d[ORIGIN_HEIGHT][ORIGIN_WIDTH];

	unsigned char y1[NUM_PIXELS];
	unsigned char y2[NUM_PIXELS];
	unsigned char y3[NUM_PIXELS];

	int index = 0;

	// Create the result directory
	mkdir("dataset/result", 0755);

	// Define file paths
	const char* lrimageFiles[] =
	{
		"dataset/lr/Barbara_256x256_yuv400_8bit.raw",
		"dataset/lr/Couple_256x256_yuv400_8bit.raw",
		"dataset/lr/Lena_256x256_yuv400_8bit.raw"
	};

	const char* gtImageFiles[] =
	{
		"dataset/gt/Barbara_512x512_yuv400_8bit.raw",
		"dataset/gt/Couple_512x512_yuv400_8bit.raw",
		"dataset/gt/Lena_512x512_yuv400_8bit.raw"
	};

	for (int i = 0; i < 3; ++i)
	{
		// Read the image
		FILE* lrFile = fopen(lrimageFiles[i], "rb");
		if (lrFile == NULL)
		{
			printf("Error opening file: %s\n", lrimageFiles[i]);
			return 1;
		}
		fread(image, sizeof(unsigned char), ORIGIN_WIDTH * ORIGIN_HEIGHT, lrFile);
		fclose(lrFile);

		// Pad the image
		padImage();

		// Save or do something with the padded image
		char resultFileName1[100];
		sprintf(resultFileName1, "dataset/result/padded_image_%d.raw", i);
		FILE* resultFile1 = fopen(resultFileName1, "wb");
		fwrite(paddedimage, sizeof(unsigned char), (ORIGIN_WIDTH + 2 * PADDING_VALUE) * (ORIGIN_HEIGHT + 2 * PADDING_VALUE), resultFile1);
		fclose(resultFile1);

		int A, D = 0;

		// Process 256x256 pixel blocks
		for (int blockY = 0; blockY < ORIGIN_HEIGHT; blockY++)
		{
			for (int blockX = 0; blockX < ORIGIN_WIDTH; blockX++)
			{
				int maxResult1 = INT_MIN;
				int minResult1 = INT_MAX;

				// Apply Mask_V and Mask_H, then sum the results
				for (int m = 0; m < 7; ++m)
				{
					for (int n = 0; n < 7; ++n)
					{
						int valV = paddedimage[blockY + m][blockX + n] * Mask_V[m][n];
						int valH = paddedimage[blockY + m][blockX + n] * Mask_H[m][n];
						int result = valV + valH;

						if (result > maxResult1)
							maxResult1 = result;

						if (result < minResult1)
							minResult1 = result;
					}
				}

				// Calculate the difference and group
				int diff = maxResult1 - minResult1;
				int group = diff / 5;

				// Map the group to 0, 1, 2, 3, 4
				int mappedGroup = group % 5; // A

				A = mappedGroup;
				//printf("A Group: %d\n", A);


				int maxResult2 = INT_MIN;
				int selectedMask = 0; // Variable to store the selected mask

				// Apply Mask_V, Mask_H, Mask_D135, and Mask_D45, then find the maximum result
				for (int maskIndex = 0; maskIndex < 4; ++maskIndex)
				{
					int result = 0;

					// Select the mask based on maskIndex
					char(*currentMask)[7][7] = NULL;
					switch (maskIndex)
					{
					case 0:
						currentMask = &Mask_V;
						break;
					case 1:
						currentMask = &Mask_H;
						break;
					case 2:
						currentMask = &Mask_D135;
						break;
					case 3:
						currentMask = &Mask_D45;
						break;
					}

					// Apply the selected mask and calculate the result
					for (int m = 0; m < 7; ++m)
					{
						for (int n = 0; n < 7; ++n)
						{
							int val = paddedimage[blockY + m][blockX + n] * (*currentMask)[m][n];
							result += val;
						}
					}

					// Update maxResult and selectedMask if the current result is greater
					if (result > maxResult2)
					{
						maxResult2 = result;
						selectedMask = maskIndex + 1;
					}
				}

				// Set D based on the selected mask
				switch (selectedMask)
				{
				case 1:
					D = 1;
					break;
				case 2:
					D = 2;
					break;
				case 3:
					D = 3;
					break;
				case 4:
					D = 4;
					break;
				default:
					D = 0;
					break;
				}
				//printf("D Group: %d\n", D);

				int result = 5 * A + D;
				resultImage[blockY][blockX] = (unsigned char)result;
				//printf("%d ", result);
				group_count[result]++;
			}
			//printf("\n");
		}
		//printf("\n");
		for (int group = 0; group < 25; ++group)
		{
			for (int blockY = 0; blockY < ORIGIN_HEIGHT; blockY++)
			{
				for (int blockX = 0; blockX < ORIGIN_WIDTH; blockX++)
				{
					int currentGroup = resultImage[blockY][blockX];
					if (currentGroup == group)
					{
						int i = group_count[group];

						unsigned char block[7][7];
						for (int m = 0; m < 7; ++m)
						{
							for (int n = 0; n < 7; ++n)
							{
								block[m][n] = paddedimage[blockY + m][blockX + n];
							}
						}

						// Multiply each pixel by i
						for (int m = 0; m < 7; ++m)
						{
							for (int n = 0; n < 7; ++n)
							{
								block[m][n] *= i;
							}
						}

						// Flatten the 2D block into a 1D array
						unsigned char X[MATRIX_SIZE];
						for (int m = 0; m < 7; ++m)
						{
							for (int n = 0; n < 7; ++n)
							{
								X[m * 7 + n] = block[m][n];
							}
						}

						// Compute X^T
						for (int m = 0; m < MATRIX_SIZE; ++m)
						{
							for (int n = 0; n < MATRIX_SIZE; ++n)
							{
								XT[n][m] = X[m * MATRIX_SIZE + n];
							}
						}

						// Compute (X^T)X
						matrixDotProduct(XT, X, XTX);

						// Compute the inverse of (X^T)X
						matrixInverse(XTX, XTX_inverse);

						h[blockY][blockX] = paddedimage[blockY][blockX + 1];  // Right pixel
						v[blockY][blockX] = paddedimage[blockY + 1][blockX];  // Below pixel
						d[blockY][blockX] = paddedimage[blockY + 1][blockX + 1];  // Diagonal pixel

						y1[index] = h[blockY][blockX];
						y2[index] = v[blockY][blockX];
						y3[index] = d[blockY][blockX];

						index++;	
						
					}
				}
			}
		}
	}
	return 0;
}
