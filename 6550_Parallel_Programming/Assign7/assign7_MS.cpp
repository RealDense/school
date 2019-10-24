
#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <random>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int main(int argc, char **argv)
{

  int rank, size;
  int data;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);

  // MPI_Status mystatus;
  // srand(time(NULL));

  // //initialize Array of random numbers
  // int subSize = rand() % 10 + 5;

  //pass all to the left log2(size)

  //pass all down log2(size)
  int sendTo = (rank + 1) % size;
  // int recvFrom = (rank - 1 + size) % size;

  if (rank == 0)
  {
    data = rank;
    for (int i = 1; i < size; i++)
    {
      MPI_Send(&data, 1, MPI_INT, i, 0, MCW);
      MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
    }
    cout << "Total sum: " << data << endl;
  }
  else
  {

    MPI_Recv(&data, 1, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);
    data += rank;
    MPI_Send(&data, 1, MPI_INT, 0, 0, MCW);
  }

  // cout << "I am " << rank << " of " << size << "; got a message from " << data << endl;
  MPI_Barrier;
  MPI_Finalize();

  return 0;
}
