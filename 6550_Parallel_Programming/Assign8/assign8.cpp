
#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <random>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD
const int WORLDSIZE = 1024;

using namespace std;

struct miniMap
{
  int mapRow[WORLDSIZE];
};

bool valid_pos(int pos, int maxSize)
{
  return pos >= 0 && pos < maxSize;
}

bool valid_pos(int row, int col, int batch)
{
  return valid_pos(row, batch + 2) && valid_pos(col, WORLDSIZE);
}

void oneDay(int **mm, int batch)
{
  int nextMap[batch + 2][WORLDSIZE];

  for (int i = 1; i <= batch; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      if (!valid_pos(i, j, batch))
        continue;
      int k = 0;
      if (valid_pos(i - 1, j - 1, batch))
        k += mm[i - 1][j - 1];
      if (valid_pos(i - 1, j, batch))
        k += mm[i - 1][j];
      if (valid_pos(i - 1, j + 1, batch))
        k += mm[i - 1][j + 1];
      if (valid_pos(i, j - 1, batch))
        k += mm[i][j - 1];
      if (valid_pos(i, j + 1, batch))
        k += mm[i][j + 1];
      if (valid_pos(i + 1, j - 1, batch))
        k += mm[i + 1][j - 1];
      if (valid_pos(i + 1, j, batch))
        k += mm[i + 1][j];
      if (valid_pos(i + 1, j + 1, batch))
        k += mm[i + 1][j + 1];

      if (mm[i][j] == 1 && k < 2)
        nextMap[i][j] = 0;
      else if (mm[i][j] == 1 && k > 3)
        nextMap[i][j] = 0;
      else if (mm[i][j] == 0 && k == 3)
        nextMap[i][j] = 1;
      else
        nextMap[i][j] = mm[i][j];
    }
  }

  for (int i = 1; i <= batch; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      mm[i][j] = nextMap[i][j];
    }
  }
}

void combine(int **bigMap, int **temp, int batch, int rank)
{
  for (int i = 0; i < batch; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      bigMap[i + (batch * rank)][j] = temp[i + 1][j];
    }
  }
  // return zero;
}

void showMap(int **bigMap, int day)
{
  cout << "\n\n\n------------------ DAY: " << day << "--------------------" << endl;
  for (int i = 0; i < WORLDSIZE; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      cout << (bigMap[i][j] == 1 ? "X" : "-");
    }
    cout << endl;
  }
}

void copyRow(int mm[][], int row[], bool top, int batch)
{
  int r = batch + 1;
  if (top)
  {
    r = 0;
  }
  for (int i = 0; i < WORLDSIZE; i++)
  {
    mm[r][i] = row[i];
  }
}

int main(int argc, char **argv)
{
  cout << "here 10\n";

  int rank, size;
  int data;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);
  int days = 25;
  int batch = WORLDSIZE;

  int x = 0;
  int y = 0;

  batch = WORLDSIZE / size;
  cout << "here 7\n";

  int mm[batch + 2][WORLDSIZE];

  for (int i = 0; i < batch + 2; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      mm[i][j] = 0;
      if (rand() % 5 == 0 && 0 < i < batch + 1)
      {
        mm[i][j] = 1;
      }
    }
  }

  for (int day = 0; day < days; day++)
  {
    miniMap top, bottom;
    copyRow(mm, top, true, batch);
    copyRow(mm, bottom, false, batch);

    //send top row
    if (rank - 1 >= 0)
    {
      MPI_Send(&top, sizeof(miniMap), MPI_BYTE, rank - 1, 0, MCW);
    }
    //send bottom row
    if (rank + 1 < size)
    {
      MPI_Send(&bottom, sizeof(miniMap), MPI_BYTE, rank + 1, 0, MCW);
    }
    //get top row
    if (rank - 1 >= 0)
    {
      MPI_Recv(&bottom, sizeof(miniMap), MPI_BYTE, rank - 1, 0, MCW);
    }
    //get bottom row
    if (rank + 1 < size)
    {
      MPI_Recv(&top, sizeof(miniMap), MPI_BYTE, rank + 1, 0, MCW);
    }

    copyRow(mm, top, true, batch);
    copyRow(mm, bottom, false, batch);

    // One day
    oneDay(mm, batch);

    MPI_Send(&mm, sizeof(mm), MPI_BYTE, 0, 0, MCW);

    // receive maps
    if (rank == 0)
    {
      int bigMap[WORLDSIZE][WORLDSIZE];
      // miniMap temp;
      int temp[batch + 2][WORLDSIZE];
      for (int i = 0; i < size; i++)
      {
        MPI_Send(&temp, sizeof(mm), MPI_BYTE, i, 0, MCW);
        bigMap = combine(bigMap, temp, batch, i);
      }
      showMap(bigMap, day);
    }

    // display maps

    MPI_Barrier;
  }

  MPI_Finalize();

  return 0;
}

// _____ Parallel stuff for Riley _______
//             WorkerEnvelope rec;
//             MPI_Recv(&rec, sizeof(WorkerEnvelope), MPI_BYTE, completedProcess, 0, MCW, MPI_STATUS_IGNORE);

//             int iOffset = (rec.chunkId % chunksInARow) * CHUNK_SIZE;
//             int jOffset = ((rec.chunkId / chunksInARow) * CHUNK_SIZE);
//             int iMax = std::min(iOffset + CHUNK_SIZE, IMAGE_SIZE);
//             int jMax = std::min(jOffset + CHUNK_SIZE, IMAGE_SIZE);
//             for (int i = iOffset; i < iMax; ++i) {
//                 for (int j = jOffset; j < jMax; ++j) {
//                     image[i][j] = rec.data[i-iOffset][j-jOffset];
//                     if(image[i][j] > max){
//                         max = image[i][j];
//                     }
//                     if(image[i][j] < min){
//                         min = image[i][j];
//                     }
//                 }
//             }

void doSomething(std::vector<int> some)
{
}

int main()
{
  std::vector<int> josh;
  doSomething(josh);
}
