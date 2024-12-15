#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>
#include <sys/resource.h>

#define MAX_PROCESSES 10000

int main(void) 
{
   	struct timespec start, end;
   	struct sched_param sp;
    	int num;
    	int value;
	char file[100];
	char read_buf[100];		
	
    	printf("CPU Scheduling\n");
    	printf("1. SCHED_OTHER\n");
    	printf("2. SCHED_FIFO\n");
    	printf("3. SCHED_RR\n");
    	printf("Enter scheduling number ");
    	scanf(" %d", &num);

    	if (num == 1)
    	{
        	printf("Enter a nice value(-20, 0, 19) : ");
        	scanf("%d", &value);
    	} 
    	else 
    	{
        	printf("Enter a priority value(1, 50, 99) : ");
        	scanf("%d", &value);
    	}
	
	clock_gettime(CLOCK_MONOTONIC, &start);

    	// Fork the processes and set scheduling for child processes
    	for (int i = 0; i < MAX_PROCESSES; i++)
    	{
        	if(!fork())
       		{
            		if(num == 1)
			{
				setpriority(PRIO_PROCESS, getpid(), value);
			}
			else if(num == 2)
			{
				sp.sched_priority = value;
				sched_setscheduler(0, SCHED_FIFO, &sp);
			}
			else if(num == 3)
			{
				sp.sched_priority = value;
				sched_setscheduler(0, SCHED_RR, &sp);
			}
			
			sprintf(file,"./temp/%d", i);
      			FILE* f_read = fopen(file, "r");
      			fscanf(f_read,"%s\n",read_buf);
      			fclose(f_read);
			
			exit(0);
	        } 
	}

    	// Parent process waits for all child processes to finish
    	for (int i = 0; i < MAX_PROCESSES; i++)
    	{
        	wait(NULL);
    	}

    	clock_gettime(CLOCK_MONOTONIC, &end);
    	double elapsed_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    	printf("%lf\n", elapsed_time / 1e6);

    	return 0;
}


