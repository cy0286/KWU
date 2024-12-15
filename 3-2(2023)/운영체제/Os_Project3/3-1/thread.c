#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#define MAX_PROCESSES 8
//#define MAX_PROCESSES 64
#define MAX_ELEMENTS (MAX_PROCESSES * 2)

pthread_mutex_t mutex;
int array[MAX_ELEMENTS];
int array2[MAX_PROCESSES]; // Array to store thread results

void* thread_func(void* arg) 
{
    	int index = *(int*)arg;
    	int start_index = index * 2;
    
    	int result = array[start_index] + array[start_index + 1];
    
    	// Store the result in the results array
    	array2[index] = result;
    
    	return NULL;
}

void main(void) 
{	
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

    	// Initialize the mutex
    	if (pthread_mutex_init(&mutex, NULL) != 0) 
    	{
        	printf("Mutex initialization failed");
    	}
    
    	
    
    	FILE *file = fopen("temp.txt", "r");
    	if (file == NULL)
    	{
        	printf("Error opening file");
    	}
    
    	// Read data from the file into the array
    	for (int i = 0; i < MAX_ELEMENTS; i++)
    	{
        	if (fscanf(file, "%d", &array[i]) != 1)
       		{
            		printf("Error reading file");
            		fclose(file);
            		exit(1);
        	}
    	}

    	int thread_index[MAX_PROCESSES]; // Store thread index
    	pthread_t threads[MAX_PROCESSES]; // Store thread ID

    	for (int i = 0; i < MAX_PROCESSES; i++) // Create threads by iterating
    	{
        	thread_index[i] = i; // Store the current thread index
        	pthread_create(&threads[i], NULL, thread_func, &thread_index[i]);
    	}

    	for (int i = 0; i < MAX_PROCESSES; i++) // Wait for each thread to complete
    	{
        	pthread_join(threads[i], NULL);
    	}
    
    	// Cleanup the mutex
    	pthread_mutex_destroy(&mutex);

    	clock_gettime(CLOCK_MONOTONIC, &end);
	double elapsed_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    	int sum = 0;
    	for (int i = 0; i < MAX_PROCESSES; i++)
    	{
        	sum += array2[i]; // Sum the results
    	}
    
    	printf("value of thread: %d\n", sum);
    	printf("%lf\n", elapsed_time / 1e6);
}


