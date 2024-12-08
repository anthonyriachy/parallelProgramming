#include "MonteCarloMethod.h"
#include <omp.h>
#include <cstdlib>

double MonteCarloMethod(long long int num_points, int num_threads, string type) {
    if (type == "parallel") {
        long long int total_points_in = 0;
        omp_set_num_threads(num_threads);

        #pragma omp parallel
        {
            long long int thread_points_in = 0;

            #pragma omp for
            for (long long int i = 0; i < num_points; i++) {
                double x = (double)rand() / RAND_MAX;
                double y = (double)rand() / RAND_MAX;
                if ((x * x) + (y * y) <= 1.0) {
                    thread_points_in++;
                }
            }

            #pragma omp atomic
            total_points_in += thread_points_in;
        }

        double pi = 4.0 * ((double)total_points_in / num_points);
        return pi;
    }
    else {
        long long int total_points_in = 0;
        for (long long int i = 0; i < num_points; i++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if ((x * x) + (y * y) <= 1.0) {
                total_points_in++;
            }
        }
        double pi = 4.0 * ((double)total_points_in / num_points);
        return pi;
    }
    
}
