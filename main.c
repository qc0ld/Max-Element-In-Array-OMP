#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



void create_file_graph(double*array_time, int max_thread){
    FILE *file_graph = fopen("data.txt", "w");
    
    for (int i = 0; i < max_thread; i++){
        fprintf(file_graph, "%d) %f\n", i + 1, array_time[i]);
    }

    fclose(file_graph);
}


int main()
{
    const int count = 10000000;
    const int random_seed = 920215;
    const int max_threads = 16;
    int max = -1;

    srand(random_seed);

    int *array = 0;
    array = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) { array[i] = rand(); }


    double *time_array = 0;
    time_array = (double *)malloc((max_threads) * sizeof(double));
    for (int i = 0; i < max_threads; i++) { time_array[i] = 0; }


    for (int threads = 1; threads <= max_threads; threads++)
    {
        double start_time = omp_get_wtime();

        #pragma omp parallel num_threads(threads) shared(array, count) reduction(max : max) default(none)
        {
        #pragma omp for
            for (int i = 0; i < count; i++)
            {
                if (array[i] > max)
                {
                    max = array[i];
                };
            }
        }

        double end_time = omp_get_wtime();
        double result = end_time - start_time;
        time_array[threads - 1] = result;

        printf("Threads: %d, Execution time: %f seconds\n", threads, result);
        printf("Max is: %d;\n", max);
    }
    
    create_file_graph(time_array, max_threads);

    free(array);
    free(time_array);

    system("python3 graph.py");
 
    return 0;
}