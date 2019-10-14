#include <iostream>
//#include <mpi.h>
#include <random>
#include <unistd.h>
//#define MCW MPI_COMM_WORLD

using namespace std;

int main()
{
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int b[5];
  int *p = a;
  p += 4;
  b = p;

  //b = *a[4];
  cout << b[0] << endl;

  return 0;
}