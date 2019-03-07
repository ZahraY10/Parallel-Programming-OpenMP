/*
Yasaman mirmohammad
zahra yousefi

multicore
lab1
*/
#pragma optimize( "2", on )
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 100000;

int main(void)
{
    struct timespec starttime, endtime;


	long int i, j, k, sum;
	double sumx, sumy, total;



	printf("Parallel Timings for %ld iterations\n\n", VERYBIG);

	for (i = 0; i < 6; i++)
	{

		clock_gettime(CLOCK_REALTIME, &starttime);

		sum = 0;
		total = 0.0;

        #pragma omp parallel shared(sum, total) private(sumx, sumy, k, j)
		{
            int tid;
            tid = omp_get_thread_num();
            int start = VERYBIG / omp_get_num_threads() * tid;
            int end = VERYBIG / omp_get_num_threads() * (tid + 1);

            long int psum = 0;
            double ptotal = 0;
            for (j = start; j < end; j++)
		    {

                psum += 1;

                sumx = 0.0;
                for (k = 0; k < j; k++)
                    sumx = sumx + (double)k;

                sumy = 0.0;
                for (k = j; k > 0; k--)
                    sumy = sumy + (double)k;
                if (sumx > 0.0) ptotal += 1.0 / sqrt(sumx);
                if (sumy > 0.0) ptotal += 1.0 / sqrt(sumy);
            }
            #pragma omp critical
            {
                sum += psum;
                total += ptotal;
            }
        }

		clock_gettime(CLOCK_REALTIME, &endtime);
		long int elapsedtime = endtime.tv_sec - starttime.tv_sec;

		printf("Time Elapsed %10ld Secs Total = %lf Check Sum = %ld\n",
			elapsedtime, total, sum);
	}

	return 0;
}

