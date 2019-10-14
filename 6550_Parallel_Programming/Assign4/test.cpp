#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cmath>
//#include "/usr/local/include/mpi.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << log2(16) << endl;
  // int sendTo;

  // for (int j = 0; j < 8; j++)
  // {
  //   for (int i = 2; i >= 0; i--)
  //   {
  //     sendTo = (j xor (1 << i));
  //     bool biggerRank = (j & (1 << i));

  //     cout << i << "   " << j << (biggerRank ? "" : " not") << " bigger than " << sendTo << endl;
  //   }
  // }

  return 0;
}