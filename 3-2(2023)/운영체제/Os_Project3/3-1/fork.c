#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#define MAX_PROCESSES 8
//#define MAX_PROCESSES 64
#define MAX_ELEMENTS (MAX_PROCESSES * 2)

int array[MAX_ELEMENTS];
int array2[MAX_PROCESSES];

void main(void)
{
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	FILE *file = fopen("temp.txt", "r");
	if (file == NULL)
	{
		printf("Error opening file");
	}
	
	// Read data from file into the array
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		if(fscanf(file, "%d", &array[i]) != 1)
		{
			printf("Error reading file");
			fclose(file);
			exit(1);
		}
	}
	
	// Process the data in parallel using fork and waitpid
	for (int num_proc = MAX_PROCESSES; num_proc >= 1; num_proc /= 2)
	{
		for(int i = 0; i < num_proc; i++)
		{
			if(!fork())
			{
				int index = i*2;
				int sum = array[index] + array[index + 1];
				exit(sum);
			}
		}
		
		// Wait for child processes to complete and save their results
       		for (int i = 0; i < num_proc; i++)
        	{
            		waitpid(array2[i], &array[i], 0);
			// Extract the exit status from child processes and store in array
 			array[i] = array[i] >> 8;
        	}
	}

	clock_gettime(CLOCK_MONOTONIC, &end);
	double elapsed_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    
	printf("value of fork : %d\n", array[0]);
	printf("%lf\n", elapsed_time / 1e6);
}

