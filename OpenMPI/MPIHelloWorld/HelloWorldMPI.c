#include <stdio.h>
#include <mpi.h>
int main() {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    printf("Process %d of %d: Hello World!\n", world_rank, world_size);
    MPI_Finalize();
}