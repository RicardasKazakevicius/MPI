#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int n = 100; // array size
	long array[n];
	
	int rank, size;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comn_rank(MPI_COM_WORLD, &rank);
	MPI_Comn_size(MPI_COM_WORLD, &size);
	
	printf("I am proces %d of %d ", rank, size);
	
	MPI_Finalize();
	
	for (int i = 0; i < n; ++i) {
		array[i] = i;
	}
	
	return 0;
}