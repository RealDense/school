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

/*
class Sandpile{
public:
	//constructor
	Sandpile(int rows, int cols);
	//
	//deconstructor
	~Sandpiles();

	void print();

	void timeUpdate();

private:
	int rows;
	int cols;

};

Sandpile::Sandpile(int row, int col) {
	rows = row;
	cols = col;
*/

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

void setup(int (&sandpiles)[ROWS][COLS]){
	sandpiles[ROWS/2][COLS/2]=TOTALGRAINS;

	//return piles;
	return;


}

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
	//cout<<sandpiles[ROWS/2][COLS/2]<<endl;
	cout<<count;
 
	return 0;
}

/*
//constants
//FPS = 500
WIDTH = 400
HEIGHT = 400
CELLWIDTH = 4
CELLHEIGHT = 4
//WINCENTER = [WINSIZE[0]/2, WINSIZE[1]/2]
//screen = pygame.display.set_mode((WIDTH, HEIGHT))

sandpiles = []

//             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)
BGCOLOR = BLACK


COLOR0    = (225, 225,   0)
COLOR1    = (  0, 185,  63)
COLOR2    = (  0, 104, 225)
COLOR3    = (122,   0, 229)




def main():

	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((WIDTH, HEIGHT))

	setup()
	
	while True:
		runGame()


def setup():
	for i in range(HEIGHT/CELLHEIGHT):
		sandpiles.append([])
		for j in range(WIDTH/CELLWIDTH):
			sandpiles[i].append(0)
	#print (sandpiles)
	sandpiles[(HEIGHT/CELLHEIGHT)/2+20][(WIDTH/CELLWIDTH)/2+20]=100000
	sandpiles[(HEIGHT/CELLHEIGHT)/2-20][(WIDTH/CELLWIDTH)/2+20]=100000
	sandpiles[(HEIGHT/CELLHEIGHT)/2+20][(WIDTH/CELLWIDTH)/2-20]=100000
	sandpiles[(HEIGHT/CELLHEIGHT)/2-20][(WIDTH/CELLWIDTH)/2-20]=100000
	

def terminate():
	pygame.quit()
	sys.exit()

def runGame():

	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()



	
	DISPLAYSURF.fill(BLACK)
	drawpiles()
	pygame.display.update()
//	FPSCLOCK.tick(FPS)

	tumble()

def tumble():
	nextpiles = []
	for i in range(HEIGHT/CELLHEIGHT):
		nextpiles.append([])
		for j in range(WIDTH/CELLWIDTH):
			nextpiles[i].append(0)

	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			num = sandpiles[i][j]
			if num >= 4:
				nextpiles[i][j] += num - 4
				if i+1 < len(nextpiles):
					nextpiles[i+1][j] += 1
				if i-1 >= 0:				
					nextpiles[i-1][j] += 1
				if j+1 < len(nextpiles[i]):
					nextpiles[i][j+1] += 1
				if i-1 >= 0:
					nextpiles[i][j-1] += 1
			else:
				nextpiles[i][j] += num

	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			sandpiles[i][j] = nextpiles[i][j]

def drawpiles():
	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			if sandpiles[i][j] == 0:
				color = COLOR0	
			elif sandpiles[i][j] == 1:
				color = COLOR1	
			elif sandpiles[i][j] == 2:
				color = COLOR2	
			else:
				color = COLOR3	

			pygame.draw.rect(DISPLAYSURF, color, (j*CELLWIDTH, i*CELLHEIGHT, CELLWIDTH, CELLHEIGHT))


if __name__ =='__main__':
	main()
*/
