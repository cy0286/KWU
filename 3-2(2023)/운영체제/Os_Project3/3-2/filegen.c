#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_PROCESSES 10000

int main(void) 
{
	srand(time(NULL)); // Initialize random number generator with current time

	if (mkdir("temp", 0777) == -1) // Create a temp directory
    	{
        	exit(1);
    	}

    	for (int i = 0; i < MAX_PROCESSES; i++) 
    	{
        	char filename[100];
        	snprintf(filename, sizeof(filename), "temp/%d", i);

        	FILE *f_write = fopen(filename, "w");
        	if (f_write == NULL) 
        	{
            		exit(1);
        	}

        	int random_num = 1 + (rand() % 9); // Generate a random number between 1 and 9

       		if (fprintf(f_write, "%d", random_num) < 0) 
        	{            
            		exit(1);
        	}

        	fclose(f_write);
    	}
    	return 0;
}


