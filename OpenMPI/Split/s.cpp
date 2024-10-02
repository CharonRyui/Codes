#include <mpi.h>
#include <iostream>

int main(int argc, char **argv) {
    
    MPI_Init(&argc, &argv);
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm new_world;
    int new_rank;
    
    if (rank < 4) {
        MPI_Comm_split(MPI_COMM_WORLD, 0, rank, &new_world);
        MPI_Comm_rank(new_world, &new_rank);
        std::cout << "My previous rank is " << rank << ". And in the new world, the rank is " << new_rank << std::endl;
    } else if (rank != 7) {
        MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &new_world);
        MPI_Comm_rank(new_world, &new_rank);
        std::cout << "My previous rank is " << rank << ". And in the new world, the rank is " << new_rank << std::endl;
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &new_world); // 使用相同的color值以保持一致性
        MPI_Comm_rank(new_world, &new_rank); // 即使rank是7，也应该获取新通信器的rank，即使它是MPI_UNDEFINED
    }

    MPI_Finalize();
    return 0;
}