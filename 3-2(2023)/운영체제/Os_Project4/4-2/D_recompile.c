#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <time.h>
#include <assert.h>
#include <string.h>

uint8_t* Operation;
uint8_t* compiled_code;
int segment_id;

void sharedmem_init(); // Access shared memory
void sharedmem_exit();
void drecompile_init(); // memory mapping start 
void drecompile_exit(); 
void* drecompile(uint8_t *func); // optimization part

int main(void)
{
	int (*func)(int a);
	int i;

	struct timespec start, end;

	sharedmem_init();
	drecompile_init();

	func = (int (*)(int a))drecompile(Operation);
	clock_gettime(CLOCK_MONOTONIC, &start);
	i = func(1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("result: %d \n", i);
	drecompile_exit();
	sharedmem_exit();
	double elapsed_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    printf("total execution time: %.9lf sec\n", elapsed_time / 1e9);
	return 0;
}

void sharedmem_init()
{
	int size;
	size = PAGE_SIZE;
	
	segment_id = shmget(1234, size, IPC_CREAT | S_IRUSR | S_IWUSR);
	Operation = (uint8_t*)shmat(segment_id, NULL, 0);
}

void sharedmem_exit()
{
	shmdt(Operation);
	shmctl(segment_id, IPC_RMID, NULL);
}

void drecompile_init()
{
	//compiled_code = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);
	compiled_code = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	assert(compiled_code != MAP_FAILED);
}

void drecompile_exit()
{
	msync(compiled_code, PAGE_SIZE, MS_ASYNC);
	munmap(compiled_code, PAGE_SIZE);
}

void* drecompile(uint8_t* func)
{	

#ifdef dynamic
	
	int i = 0;
    int j = 0;
	int z = 0;
    int total_add = 0;
    int total_sub = 0;
    int total_imul = 1;
    int total_div = 1;

	while (func[i] != 0xc3) // End condition
	{ 
        if (func[i] == 0x83) 
		{
            if (func[i + 1] == 0xc0) // ADD
			{  
                while (func[i] == 0x83 && func[i + 1] == 0xc0) 
				{
                    total_add += func[i + 2];
                    i += 3;
                }
				compiled_code[j++] = 0x83;  // Copy
                compiled_code[j++] = 0xc0;
                compiled_code[j++] = total_add;
				total_add = 0; // Initialization
            } 
			else if (func[i + 1] == 0xe8) // SUB
			{  
                while (func[i] == 0x83 && func[i + 1] == 0xe8) 
				{
                    total_sub += func[i + 2];
                    i += 3;
                }
				compiled_code[j++] = 0x83; // Copy
                compiled_code[j++] = 0xe8;
                compiled_code[j++] = total_sub;
				total_sub = 0; // Initialization
            }
			continue;
        } 
		else if (func[i] == 0x6b && func[i + 1] == 0xc0) // MUL
		{  
            while (func[i] == 0x6b && func[i + 1] == 0xc0) 
			{
                total_imul *= func[i + 2];
                i += 3;
            }
			compiled_code[j++] = 0x6b; // Copy
            compiled_code[j++] = 0xc0;
            compiled_code[j++] = total_imul;
			total_imul = 1; // Initialization
			continue;
        }
		else if (func[i] == 0xf6 && func[i + 1] == 0xf2) //DIV
		{
			while (func[i] == 0xf6 && func[i + 1] == 0xf2) 
			{
                total_div *= 2;
                i += 2;
            }
			compiled_code[j++] = 0xb2; // Copy
            compiled_code[j++] = total_div;

			compiled_code[j++] = 0xf6;
            compiled_code[j++] = 0xf2;
			
            compiled_code[j++] = 0xb2;
            compiled_code[j++] = 0x02;
			//compiled_code[j++] = total_div;
			total_div = 1; // Initialization
			continue;
		}
        compiled_code[j++] = func[i++];
    }
    compiled_code[j] = 0xc3;  // End condition
	mprotect(compiled_code, PAGE_SIZE, PROT_READ | PROT_EXEC);

	return compiled_code;
#endif

	memcpy(compiled_code, func, PAGE_SIZE);	
	mprotect(compiled_code, PAGE_SIZE, PROT_READ | PROT_EXEC);
	return compiled_code;
}
