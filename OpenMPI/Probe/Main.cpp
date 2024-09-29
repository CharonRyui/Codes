#include <mpi.h>
#include <iostream>


void probing_process(int &int_sum, float &float_sum) {
  MPI_Status status;
  
  // 1- Probe the incoming message
  MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  // 2- Get the tag and the source
  int tag = status.MPI_TAG;
  int source = status.MPI_SOURCE;
  int count;

  // Printing the message
  std::cout << "Received a message from process " << source << " with tag " << tag << std::endl;

  // 3- Add to int_sum or float_sum depending on the tag of the message
  if (tag == 0)
  {
    int recvNum;
    MPI_Get_count(&status, MPI_INT, &count);
    MPI_Recv(&recvNum, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
    int_sum += recvNum;
  }
  else if (tag == 1)
  {
    float recvNum;
    MPI_Get_count(&status, MPI_FLOAT, &count);
    MPI_Recv(&recvNum, count, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
    float_sum += recvNum;
  }
}
