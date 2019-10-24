#include <iostream>
//#include <mpi.h>
#include <random>
#include <unistd.h>
//#define MCW MPI_COMM_WORLD

using namespace std;

void sort()
{
}

void swap(int *xp, int *yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)

    // Last i elements are already in place
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
}

void print(int nums[], int size)
{
  for (int i = 0; i < size; i++)
  {
    cout << nums[i] << " ";
  }
  cout << endl;
}

int main()
{
  int nums[] = {5, 9, 4, 8, 2};
  print(nums, 5);
  bubbleSort(nums, 5);
  print(nums, 5);

  return 0;
}