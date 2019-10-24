#include <iostream>
#include <random>
#include <unistd.h>
#include <cmath>
#include <fstream>

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

int mandelbrot(Complex c, int maxIters)
{
  int i = 0;
  Complex z;
  z = c;
  while (i < maxIters && z.r * z.r + z.i * z.i < 2)
  {
    z = z * z + c;
    i++;
  }
  return i;
}

int main(int argc, char **argv)
{
  int rank, size;
  int data;
  int maxIters = 255;
  int rows = 4096;
  int cols = 4096;
  // double tl[2] = {1, -1.5};
  // double br[2] = {-1, .5};
  double tl[2] = {.365, -.627};
  double br[2] = {.17, .008};

  double width = abs(br[0] - tl[0]);

  ofstream fout;
  fout.open("mandelout2.ppm");
  fout << "P2\n"
       << rows << " " << cols << endl
       << "255\n";

  double stepC = double((br[1] - tl[1]) / cols);
  double stepR = double((tl[0] - br[0]) / rows);

  Complex current;

  for (double row = tl[0]; row > br[0]; row -= stepR)
  {
    for (double col = tl[1]; col < br[1]; col += stepC)
    {
      current.i = row;
      current.r = col;
      int mand = mandelbrot(current, maxIters);
      if (mand >= maxIters)
      {
        //fout black
        fout << "0 ";
      }
      else
      {
        //fout other gray
        fout << mand << " ";
      }
    }
    fout << endl;
  }
  fout.close();

  return 0;
}
