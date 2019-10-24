
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

bool valid_pos(int pos)
{
  return pos >= 0 && pos < WORLDSIZE;
}

bool valid_pos(int row, int col) { return valid_pos(row) && valid_pos(col); }

int oneDay(miniMap c, int batch)
{
  int nextMap[batch][WORLDSIZE];

  for (int i = c.x; i < c.x * batch; i++)
  {
    for (int j = c.y; j < c.y * batch; j++)
    {
      if (!valid_pos(i, j))
        continue;
      int k = 0;
      if (valid_pos(i - 1, j - 1))
        k += c.mapPart[i - 1][j - 1];
      if (valid_pos(i - 1, j))
        k += c.mapPart[i - 1][j];
      if (valid_pos(i - 1, j + 1))
        k += c.mapPart[i - 1][j + 1];
      if (valid_pos(i, j - 1))
        k += c.mapPart[i][j - 1];
      if (valid_pos(i, j + 1))
        k += c.mapPart[i][j + 1];
      if (valid_pos(i + 1, j - 1))
        k += c.mapPart[i + 1][j - 1];
      if (valid_pos(i + 1, j))
        k += c.mapPart[i + 1][j];
      if (valid_pos(i + 1, j + 1))
        k += c.mapPart[i + 1][j + 1];

      if (c.mapPart[i][j] == 1 && k < 2)
        nextMap.mapPart[i][j] = 0;
      else if (c.mapPart[i][j] == 1 && k > 3)
        nextMap.mapPart[i][j] = 0;
      else if (c.mapPart[i][j] == 0 && k == 3)
        nextMap.mapPart[i][j] = 1;
      else
        nextMap.mapPart[i][j] = c.mapPart[i][j];
    }
  }
  nextMap.x = c.x;
  nextMap.y = c.y;
  return nextMap;
}

miniMap copy(miniMap c, miniMap t)
{
  t.x = c.x;
  t.y = c.y;
  return t;
}

miniMap combine(miniMap zero, miniMap other, int batch)
{
  for (int i = other.x; i < other.x * batch; i++)
  {
    for (int j = other.y; j < other.y * batch; j++)
    {
      zero.mapPart[i][j] = other.mapPart[i][j];
    }
  }
  return zero;
}

void showMap(miniMap zero, int day)
{
  cout << "\n\n\nDAY: " << day << endl;
  for (int i = 0; i < WORLDSIZE; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      cout << (zero.mapPart[i][j] == 1 ? "X" : "-");
    }
    cout << endl;
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

  int mm[batch][WORLDSIZE];

  for (int i = 0; i < batch; i++)
  {
    for (int j = 0; j < WORLDSIZE; j++)
    {
      mm[i][j] = 0;
      if (rand() % 5 == 0)
      {
        mm[i][j] = 1;
      }
    }
  }

  for (int day = 0; day < days; day++)
  {
    //send top row
    miniMap top, bottom;
    top.mapRow = mm[0];
    bottom.mapRow = mm[batch - 1];

    if (rank - 1 >= 0)
    {

      MPI_Send(&top, sizeof(miniMap), MPI_BYTE, rank - 1, 0, MCW);
    }
    //send bottom row
    //get top row
    //get bottom row
    if (rank == 0)
    {
      //send out map
      for (int i = 1; i < size; i++)
      {
        cout << "here 1\n";
        MPI_Send(&myMap, sizeof(miniMap), MPI_BYTE, i, 0, MCW);
        cout << "here 2\n";
      }
    }
    else
    {
      //receive map
      miniMap temp;
      cout << "here 3\n";
      MPI_Recv(&temp, sizeof(miniMap), MPI_BYTE, 0, 0, MCW, MPI_STATUS_IGNORE);
      cout << "here 4\n";
      myMap = copy(myMap, temp);
      cout << "here 5\n";
    }

    // One day
    myMap = oneDay(myMap, batch);

    // receive maps
    if (rank == 0)
    {
      miniMap temp;
      for (int i = 1; i < size; i++)
      {
        MPI_Send(&temp, sizeof(miniMap), MPI_BYTE, i, 0, MCW);
        myMap = combine(myMap, temp, batch);
      }
      showMap(myMap, day);
    }
    else
    {
      MPI_Send(&myMap, sizeof(miniMap), MPI_BYTE, 0, 0, MCW);
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
