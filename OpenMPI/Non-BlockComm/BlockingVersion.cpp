#include <iostream>
#include <mpi.h>

// This file is provided as an example of blocking scenario. Please don't modify it !
int main(int argc, char **argv) {

  MPI_Init(&argc, &argv);
  const int buffer_count = 1000000;
  int buffer[buffer_count];
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Initialising buffer :
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);

  MPI_Barrier(MPI_COMM_WORLD);
  // Starting the chronometer
  double time = -MPI_Wtime(); // This command helps us measuring time. We will see more about it later !
  // Simulate working
  if (rank == 0) {
    // sleep(3);
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    // sleep(6);
    
    // Modifying the buffer for second step
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;
    
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD);
  }
  else {
    // sleep(5);
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // sleep(3);
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  time += MPI_Wtime();
  
  // This line gives us the maximum time elapsed on each process.
  // We will see about reduction later on !
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0)
    std::cout << "Total time for blocking scenario : " << final_time << "s" << std::endl;

  MPI_Finalize();
}
