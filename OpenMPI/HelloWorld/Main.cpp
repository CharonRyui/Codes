#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char *argv[])
{
    MPI_Init(NULL, NULL);
    
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout << "Hello world, from process #" << rank << ". And he size is" << size << endl; 

    MPI_Finalize();
    
    return 0;
}