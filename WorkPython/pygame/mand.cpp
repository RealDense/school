#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

//Riley Densley
//A01227345
//S002

using namespace std;

const int MAXITERS = 255;

struct Complex {
	double r;
	double i;
};

struct Color {
	int r;
	int g;
	int b;
};

double magnitude(Complex c) {
	return sqrt(pow(c.r, 2) + pow(c.i, 2));
}

Complex operator+(Complex c1, Complex c2) {
	Complex c3;
	c3.r = c1.r + c2.r;
	c3.i = c1.i + c2.i;
	return c3;
}

Complex operator*(Complex c1, Complex c2) {
	Complex c3;
	c3.r = c1.r*c2.r - c1.i*c2.i;
	c3.i = c1.r*c2.i + c1.i*c2.r;
	return c3;
}

double interpolate(double y1, double x1, double y2, double x2, double xj) {
	double ydist, xdist, xjdist, yjdist, yj;
	ydist = y2 - y1;
	xdist = x2 - x1;
	xjdist = xj - x1;
	yjdist = ydist*(xjdist / xdist);
	yj = y1 + yjdist;
	
	return yj;
}

int mandelbrot(Complex c) {
	int i = 0;
	Complex z;
	z = c;
	while (magnitude(z)<2 && i<MAXITERS) {
		z = z*z + c;
		i++;
	}
	return i;
}

int main() {
	ifstream fin;
	ofstream fout;
	Complex c1, c2, man;
	Color fire; fire.r = 255 ;fire.g = 215 ;fire.b= 0 ;
	Color blue; blue.r = 0;blue.g = 0;blue.b = 100;
	Color brot;
	double stepR, stepC, step;
	int rows = 512, cols = 512;
	int k;
	
	// color firebrick 178 34 34
	// color gold 255 215 0
	
	//step = 4/512;

	fin.open("mandelinput.txt");
	fin >> c1.r >> c1.i >> c2.r >> c2.i;
	

	stepR = (c2.i - c1.i) / rows;
	stepC = (c2.r - c1.r) / cols;

	fout.open("mandeloutput.ppm");
	fout << "P3\n"<<rows<< " " << cols<<endl<<"255\n";
	

	/*for (int j = 0;j < rows;j++) {
		for (int i = 0;i < cols;i++) {
			if (mandelbrot(man) == 255) {
				fout << "0 0 0 ";
			}
			else {
				k = mandelbrot(man);
				fout << k << " " << k << " 0 ";
			}
			man.r += step;
		}
		fout << endl;
		man.r = -1.5;
		man.i -= step;
	}*/

	for (double j = c1.i; j != c2.i; j += stepR) {
		for (double i = c1.r; i != c2.r; i += stepC) {
			man.i = j;
			man.r = i;
			if (mandelbrot(man) == 255) {
				fout << "0 0 0 ";
			}
			else {
				k = mandelbrot(man)%16;
				brot.r = interpolate(blue.r, 0, fire.r, 16, k);
				brot.g = interpolate(blue.g, 0, fire.g, 16, k);
				brot.b = interpolate(blue.b, 0, fire.b, 16, k);
				fout << brot.r << " " << brot.g << " " << brot.b << " ";
			
			}
		}
		fout << endl;
	}
	fout.close();

	return 0;
} 
//--------Grade 10,    by Kaige------ 
