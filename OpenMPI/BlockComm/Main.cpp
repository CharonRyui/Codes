#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <cmath>
using namespace std;


// struct MPI_Status
// {
//     int MPI_SOURCE;
//     int MPI_TAG;
//     int MPI_ERROR;
// };

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Status status{};
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        int localValue[5] = {1, 2, 3, 4, 5};
        double outerMessage[4] = {};
        
        MPI_Send(&localValue, 4, MPI_INT, 1, 0, MPI_COMM_WORLD);cout << "here" << endl;
        MPI_Recv(&outerMessage, 3, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &status);
        std::cout << "I'm #" << rank << ". I got " << outerMessage[0] << " " << outerMessage[1]  << " " << outerMessage[2]<< endl;
        cout << "#" << rank << " " << status.MPI_SOURCE << " " << status.MPI_TAG << endl;;
    }
    else if (rank == 1)
    {
        double localValue[3] = {1.34, 3.14, M_PI};
        int outerMessage[5] = {};
        
        MPI_Recv(&outerMessage, 4, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);cout << "here1" << endl;
        MPI_Send(&localValue, 3, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        std::cout << "I'm #" << rank << ". I got " << outerMessage[0] << " " << outerMessage[1] << " " << outerMessage[2] << endl;
    }

    
    MPI_Finalize();
    return 0;
}

