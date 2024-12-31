#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
     int *A = (int*)malloc(N * sizeof(int));
     if (A == NULL) {
         return NULL;
     }

     srand(time(0));

     for(int i = 0; i < N; i++) {
         A[i] = rand() % (10 * N + 1);	
     }
     return A;
}

void SortArray(int *A, int N)
{
    bool swapped = true;
    while(swapped == true) {
        swapped = false;
	for(int i = 1; i < N; i++) {
	    if(A[i-1] > A[i]) {
	        int a = A[i-1];
		int b = A[i];
		A[i-1] = b;
		A[i] = a;
		swapped = true;
	    }
	}
    }
}

void DeallocateArray(int *A)
{
    free(A);
}

int main()
{
    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

/* For fun:
 *  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
 *                    256000, 512000, 1024000 }; 
 */

    for (int i = 0 ; i < 8 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;

	(void)gettimeofday(&startTime, NULL);
	int *A = AllocateArray(sizes[i]);
	(void)gettimeofday(&endTime, NULL);
	alloc_time = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

	(void)gettimeofday(&startTime, NULL);
	SortArray(A, sizes[i]);
	(void)gettimeofday(&endTime, NULL);
	sort_time = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;

	(void)gettimeofday(&startTime, NULL);
	DeallocateArray(A);
	(void)gettimeofday(&endTime, NULL);
	dealloc_time = (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec) / 1000000.0;
        
        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}
