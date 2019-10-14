#include <iostream>
#include <mpi.h>
#include <random>
#include <unistd.h>
#define MCW MPI_COMM_WORLD

using namespace std;

struct Complex
{
  double r;
  double i;
};

Complex operator+(Complex s, Complex t)
{
  Complex v;
  v.r = s.r + t.r;
  v.i = s.i + t.i;
  return v;
}

Complex operator*(Complex s, Complex t)
{
  Complex v;
  v.r = s.r * t.r - s.i * t.i;
  v.i = s.r * t.i + s.i * t.r;
  return v;
}

int mangelbrot(Complex c, int maxIters)
{
  int i = 0;
  Complex z;
  z = c;
  while (i < maxIters && z.r * z.r + z.i * z.i < 4)
  {
  }
}

int main(int argc, char **argv)
{
  int rank, size;
  int data;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);
  MPI_Status mystatus;
  srand(time(NULL));

  //initialize Array of random numbers
  int subSize = rand() % 10 + 5;

  //Process 0 starts the game
  //Master
  // if (rank == 0)
  // {
  //     int toSortMaster[arraySize];
  //     for (int i = 0; i < arraySize; i++)
  //     {
  //         toSortMaster[i] = rand() % 50;
  //     }
  //     cout << "To sort Master array \n";
  //     print(toSortMaster, arraySize);

  //     for (int i = 1; i < size; i++)
  //     {
  //         //initialize array for sending
  //         int sendingArray[subSize];
  //         cout << "Sent section to array " << i << endl;
  //         for (int j = 0; j < subSize; j++)
  //         {
  //             sendingArray[j] = toSortMaster[((i - 1) * subSize) + j];
  //         }
  //         MPI_Send(sendingArray, subSize, MPI_INT, i, 0, MCW);
  //     }

  //     //receive arrays and order them
  //     int sortedSize = 0;
  //     int *masterSorted;
  //     for (int i = 1; i < size; i++)
  //     {
  //         MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &mystatus);
  //         int quantity;
  //         MPI_Get_count(&mystatus, MPI_INT, &quantity);

  //         int sortedSlave[quantity];
  //         MPI_Recv(&sortedSlave, quantity, MPI_INT, mystatus.MPI_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

  //         int *temp = masterSorted;
  //         masterSorted = new int[sortedSize + quantity];
  //         merge(temp, sortedSize, sortedSlave, quantity, masterSorted);
  //         sortedSize += quantity;
  //     }
  //     cout << "Master sorted array\n";
  //     print(masterSorted, sortedSize);
  // }
  // else
  // {
  //     //Slave
  //     //Sorting Processes
  //     MPI_Probe(0, MPI_ANY_TAG, MCW, &mystatus);
  //     int quantity;
  //     MPI_Get_count(&mystatus, MPI_INT, &quantity);
  //     int toSortSlave[quantity];
  //     MPI_Recv(&toSortSlave, quantity, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);
  //     //Sort this Array
  //     //sleep(rank);
  //     cout << rank << " sorting job is  ";
  //     print(toSortSlave, quantity);
  //     bubbleSort(toSortSlave, quantity);

  //     cout << rank << " sorted is  ";
  //     print(toSortSlave, quantity);

  //     MPI_Send(&toSortSlave, quantity, MPI_INT, 0, 0, MCW);
  // }

  MPI_Finalize();

  return 0;
}
