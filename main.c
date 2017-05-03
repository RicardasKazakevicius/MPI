#include <stdio.h>
//#include <mpi.h>
#include <time.h>

int main(int argc, char **argv) {
	int n = 100000; // array size
	long array[n];
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int intervalSize = n / size;
	
	long arr[intervalSize];
	int numberWithMostIterations = 0;
	int mostIterations = 0;
	int number;
	int iterations;
	
	for (int i = 0; i < n; ++i) {
		array[i] = i + 1;
	}
	
	time_t start = time(0);
	int index = 0;
	
	if (rank == 0) {
		for (int i = 1; i < size; ++i) {
			for (int j = 0; j < intervalSize; ++j) {
				arr[j] = array[index];
				++index;
			}
			MPI_Send(arr, 1, MPI_LONG, 0, 123, MPI_COMM_WORLD);
		}
	} else { 		MPI_Status status;
		for (int i = 1; i < size; ++i) {
			if (rank == i) {
				MPI_Recv( arr, 1, MPI_LONG, 0, 123, MPI_COMM_WORLD, &status);
				for (int j = 0; j < sizeof(arr)/sizeof(int); j++) {
				
					number = arr[j];
					iterations = 0;

					while (number != 1) {
						if ((number % 2) == 0) {
							number = number / 2;
						} else {
							number = (3 * number) + 1;
						}
						++iterations;
					}
					printf("%d \n", iterations);
					if (iterations > mostIterations) {
						mostIterations = iterations;
						numberWithMostIterations = arr[j];
					}
				}
			}
		}
	}

	MPI_Finalize();
	
	time_t end = time(0);
	printf("Time: %d   Number with most iterations: %d \n", end-start, numberWithMostIterations);
	
	return 0;
}