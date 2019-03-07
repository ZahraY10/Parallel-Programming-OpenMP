#pragma optimize( "2", on )
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

// Adds an additional library so that timeGetTime() can be used
const long int VERYBIG = 100000;
// ***********************************************************************
int main(void)
{
	int i;
	long int j, k, sum;
	double sumx, sumy, total;
	long starttime, elapsedtime;
	// -----------------------------------------------------------------------
	// Output a start message
	printf("Parallel Timings for %ld iterations\n\n", VERYBIG);
	// repeat experiment several times
	for (i = 0; i<6; i++)
	{
		// get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
		starttime = omp_get_wtime();
		// reset check sum & running total
		sum = 0;
		total = 0.0;
		// Work Loop, do some work by looping VERYBIG times
		#pragma omp parallel private(sumx, sumy, k)
		{
			printf("Thread Num: %d\n", omp_get_num_threads());
			double private_total = 0;
			long int private_sum = 0;	
			#pragma omp for	
			for (j = 0; j < VERYBIG; j++)
			{
				// increment check sum				
				private_sum += 1;
				// Calculate first arithmetic series
				sumx = 0.0;
				for (k = 0; k<j; k++)
					sumx = sumx + (double)k;
				// Calculate second arithmetic series
				sumy = 0.0;
				for (k = j; k > 0; k--)
					sumy = sumy + (double)k;			
				if (sumx > 0.0){				
					private_total = private_total + 1.0 / sqrt(sumx);
				}								
				if (sumy > 0.0) {
					private_total = private_total + 1.0 / sqrt(sumy);				
				}
			}
			#pragma omp atomic 
			total += private_total;
			#pragma omp atomic
			sum += private_sum;
		}
		// get ending time and use it to determine elapsed time
		elapsedtime = omp_get_wtime() - starttime;
		// report elapsed time
		printf("Time Elapsed % 10d mSecs Total = %lf Check Sum = %ld\n",
			(int)elapsedtime, total, sum);
	}
	// return integer as required by function header
	return 0;
}
// **********************************************************************
//j, k, sumx, sumy --> private!
