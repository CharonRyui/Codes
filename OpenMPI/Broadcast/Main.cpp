#include <iostream>
#include <mpi.h>
#include <iomanip>
using namespace std;
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buffer_size;
    double *buffer;
    double sum = 0;

    if (rank == 0)
    {
        cin >> buffer_size;
    }

    MPI_Bcast(&buffer_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    buffer = new double[buffer_size];

    if (rank == 0)
    {
        for (int i = 0; i < buffer_size; i++) 
        {
            cin >> buffer[i];
            sum += buffer[i];
        }
    }
    
    MPI_Bcast(buffer, buffer_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    
    if (rank == 1)
    {
        for (int i = 0; i < buffer_size; i++)
        {
            if (buffer[i] > 0) sum += buffer[i];
        }
    }
    else if (rank == 2)
    {
        for (int i = 0; i < buffer_size; i++)
        {
            if (buffer[i] < 0) sum += buffer[i];
        }
    }
    
    cout << setprecision(16) << sum << endl;

    delete [] buffer;

    

    MPI_Finalize();
    return 0;
}