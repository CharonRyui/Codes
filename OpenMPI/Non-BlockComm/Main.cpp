#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    const int buffer_size = 100;
    int buffer[buffer_size] {};
    int rank;
    MPI_Request request1{};
    MPI_Request request2{};
    MPI_Status status1{};
    MPI_Status status2{};
    int flag = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < buffer_size; i++) buffer[i] = (rank == 0 ? i * 2 : 0);
    MPI_Barrier(MPI_COMM_WORLD);

    double time = -MPI_Wtime();

    if (rank == 0)
    {
        MPI_Isend(buffer, buffer_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &request1);
        for (int i = 0; i < buffer_size; i++) 
        {
            if (flag != 0) MPI_Isend(buffer, buffer_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &request1);
            else MPI_Test(&request1, &flag, &status1);
            
            buffer[i] = -i;
        }
        if (flag == 0) MPI_Wait(&request1, &status1);
        MPI_Isend(buffer, buffer_size, MPI_INT, 1, 1, MPI_COMM_WORLD, &request2);
        MPI_Wait(&request2, &status2);
    }
    else 
    {
        MPI_Irecv(buffer, buffer_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
        for (int i = 0; i < buffer_size; i++)
        {
            if (flag != 0) MPI_Irecv(buffer, buffer_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
            else MPI_Test(&request1, &flag, &status1);
            cout << buffer[i] << " ";
        }
        if (flag == 0) MPI_Wait(&request1, &status1);
        else MPI_Irecv(buffer, buffer_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
        cout << endl;
        
        std::cout << "received" << status1.MPI_TAG << " with value" << buffer[10] << std::endl;
        MPI_Irecv(buffer, buffer_size, MPI_INT, 0, 1, MPI_COMM_WORLD, &request2);
        MPI_Wait(&request2, &status2);
        std::cout << "received" << status2.MPI_TAG << " with value" << buffer[10] << std::endl;
    }



    MPI_Finalize();
    return 0;
}