//!/usr/bin/env python
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

int const ROWS = 801;
int const COLS = 801;
int const TOTALGRAINS = 10000000;
int const TOTALLOOPS = 50000;

string FILENAME = "sandpiles2.ppm";

string color0 = "225 225 0 ";
string color1 = "0 185 63 ";
string color2 = "0 104 225 ";
string color3 = "122 0 229 ";

struct Color {
	int r;
	int g;
	int b;
};


class Pile{
public:
	//constructor
	Pile(int size);
	//
	//deconstructor
	~Piles();

	void print();

	void timeUpdate();

	int size;
	int piles[][];
private:

};

Pile::Pile(int size) {
	this.size = size;
	this.piles[size][size];
	for( int i =0; i < this.size; i++){
		for( int j =0; j < this.size; j++){
			cout<<sandpiles[i][j];
		}
		cout<<endl;
	}
}

/*
bool topple(int (&sandpiles)[ROWS][COLS]){
	//return sandpiles;
	int nextpiles[ROWS][COLS] = {{0}};
	int comparepiles[ROWS][COLS] = {{0}};
	bool same = true;

	for( int i =0; i < ROWS; i++){
		for( int j =0; j < COLS; j++){
			int num = sandpiles[i][j];
			if (num < 4){
				nextpiles[i][j] = sandpiles[i][j];
				comparepiles[i][j] = sandpiles[i][j];
			}
		}
	}

	for( int i =0; i < ROWS; i++){
		for( int j =0; j < COLS; j++){
			int num = sandpiles[i][j];
			if (num >= 4){
				nextpiles[i][j] += num - 4;
				if(i+1 < ROWS){
					nextpiles[i+1][j] += 1;
				}
				if(i-1 >= 0){
					nextpiles[i-1][j] += 1;
				}
				if(j+1 < COLS){
					nextpiles[i][j+1] += 1;
				}
				if(j-1 >= 0){
					nextpiles[i][j-1] += 1;
				}
			}
		}
	}

	
	for( int i =0; i < ROWS; i++){
		for( int j =0; j < COLS; j++){
			sandpiles[i][j] = nextpiles[i][j];
			if (sandpiles[i][j] != comparepiles[i][j]){
				same = false;
			}
		}
	}

	return same;
}
*/

/*
void setup(int (&sandpiles)[ROWS][COLS]){
	sandpiles[ROWS/2][COLS/2]=TOTALGRAINS;

	//return piles;
	return;
}
*/

int main(){

	ifstream fin;
	ofstream fout;


	int sandpiles[ROWS][COLS] = {{0}};

	setup(sandpiles);
	bool done = false;
	int count = 0;

	while(!done){
		//if(!(count % 5000)){
		//	cout<< sandpiles[ROWS/2][COLS/2]<<endl;
		//}
		done = topple(sandpiles);
		count ++;
	}


	/*
	fout.open(FILENAME);
	fout << "P3\n" << ROWS << " " << COLS << endl << "255\n";
	for( int i =0; i < ROWS; i++){
		for( int j =0; j < COLS; j++){
			if (sandpiles[i][j] == 0) { fout << color0; }
			else if (sandpiles[i][j] == 1) { fout << color1; }
			else if (sandpiles[i][j] == 2) { fout << color2; }
			else{ fout << color3; }
			
		}
		fout << endl;
	}

	fout.close();
	*/


	for( int i =0; i < sandpile.size; i++){
		for( int j =0; j < sandpiles.size; j++){
			cout<<sandpiles[i][j];
		}
		cout<<endl;
	}

	//cout<<sandpiles[ROWS/2][COLS/2]<<endl;
	cout<<count;
 
	return 0;
}

