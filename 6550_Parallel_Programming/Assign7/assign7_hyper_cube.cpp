
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

  int sendTo;
  int sum = rank;
  int recv = 0;

  for (int i = 0; i < 3; i++)
  {
    sendTo = rank ^ (1 << i);
    MPI_Send(&sum, 1, MPI_INT, sendTo, 0, MCW);
    MPI_Recv(&recv, 1, MPI_INT, sendTo, 0, MCW, MPI_STATUS_IGNORE);
    sum += recv;
    MPI_Barrier;
  }
  cout << rank << " Total sum: " << sum << endl;

  MPI_Barrier;
  MPI_Finalize();

  return 0;
}
