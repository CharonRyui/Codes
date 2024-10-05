#include <mpi.h>
#include <iostream>

int main(int argc, char **argv) {
    
    MPI_Init(&argc, &argv);
    int color;
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int new_rank;
    MPI_Comm NEW_WORLD;
    MPI_Comm COMM14;
    int rank14;

    if (rank == 1 || rank == 4) {
        MPI_Comm_split(MPI_COMM_WORLD, 3, rank, &COMM14);
        MPI_Comm_rank(COMM14, &rank14);
        std::cout << "My rank in COMM14 is " << rank14 << std::endl;
    } else MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &COMM14);

    if (rank < 4) {
        MPI_Comm_split(MPI_COMM_WORLD, 0, rank, &NEW_WORLD);
        MPI_Comm_rank(NEW_WORLD, &new_rank);
    } else if (rank != 7) {
        MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &NEW_WORLD);
        MPI_Comm_rank(NEW_WORLD, &new_rank);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &NEW_WORLD);
    }

    std::cout << "My previous rank is " << rank << ". And in the new world, the rank is " << new_rank << std::endl;

    MPI_Finalize();
    return 0;
}