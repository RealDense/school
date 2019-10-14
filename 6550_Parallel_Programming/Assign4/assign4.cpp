
#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
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
  MPI_Status mystatus;

  int temp;
  bool biggerRank;
  int sendTo;

  int initialSet[size];
  for (int i = 0; i < size; i++)
  {
    initialSet[i] = size - 1 - i;
  }

  random_shuffle(&initialSet[0], &initialSet[size - 1]);
  if (rank == 0)
  {
    for (int i = 0; i < size; i++)
    {
      cout << initialSet[i] << "  ";
    }
    cout << endl;
  }

  data = initialSet[rank];

  // MPI_Send(&rank, 1, MPI_INT, (rank + 1) % size, 0, MCW);
  // MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

  // cout << "I am " << rank << " of " << size << "; got a message from " << data << endl;

  for (int j = 0; j < log2(size); j++)
  {
    for (int i = j; i >= 0; i--)
    {
      bool ascending = true;
      if (rank & (1 << (j + 1)))
      {
        ascending = false;
      }
      biggerRank = (rank & (1 << i));
      sendTo = (rank xor (1 << i));
      MPI_Send(&data, 1, MPI_INT, sendTo, 0, MCW);
      MPI_Recv(&temp, 1, MPI_INT, sendTo, 0, MCW, MPI_STATUS_IGNORE);

      if (ascending)
      {
        data = (biggerRank == data > temp) ? data : temp;
      }
      else
      {
        data = (biggerRank == data < temp) ? data : temp;
      }
    }
  }
  //cout << "Rank " << rank << " has " << data << endl;
  MPI_Barrier;

  //Send all values back to 0 for cout
  if (rank == 0)
  {
    initialSet[0] = data;
    for (int i = 1; i < size; i++)
    {
      MPI_Recv(&temp, 1, MPI_INT, i, 0, MCW, MPI_STATUS_IGNORE);
      initialSet[i] = temp;
    }
    for (int i = 0; i < size; i++)
    {
      cout << initialSet[i] << "  ";
    }
    cout << endl;
  }
  else
  {
    MPI_Send(&data, 1, MPI_INT, 0, 0, MCW);
  }

  // cout << rank << " I have " << data << endl;

  MPI_Finalize();

  return 0;
}
