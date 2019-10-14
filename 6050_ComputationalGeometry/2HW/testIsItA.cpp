//Riley Densley
//HW2 6050
//
#include <iostream>
#include <algorithm>


using namespace std;

struct Lines{
	int x1;
	int x2;
	int y1;
	int y2;

};

void printL(Lines line){
	cout << line.x1 << " ";
	cout << line.y1 << " ";
	cout << line.x2 << " ";
	cout << line.y2 << " ";
}

Lines setLines(){
	Lines temp;
	cin >> temp.x1;
	cin >> temp.y1;
	cin >> temp.x2;
	cin >> temp.y2;
	return temp;
}

bool angle(int ix, int iy, int jx, int jy, int kx, int ky){
	//colinear?
	if((long(kx-ix)*(jy-iy) - long(ky-iy)*(jx-ix)) == 0){
		cout << "angle No" << endl;
		return false;
	}
	//dot produt >= 0 means 0 to 90 degrees
	if((long(jx-ix)*(kx-ix) + long(jy-iy)*(ky-iy)) >= 0){
		cout << "angle yes"<<endl;       
		return true;
	}
	cout << "angle no 2"<< endl;
	return false;
}

bool joined(Lines a, Lines b){
	//Check to see if lines are connected at one point
	if(a.x1 == b.x1 && a.y1 == b.y1){
		cout<<"joined 1 yes"<<endl;
		return angle(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2);
	}
	if(a.x2 == b.x1 && a.y2 == b.y1){
		cout<<"joined 2 yes"<<endl;
		return angle(a.x2, a.y2, a.x1, a.y1, b.x2, b.y2);
	}
	if(a.x1 == b.x2 && a.y1 == b.y2){
		cout<<"joined 3 yes"<<endl;
		return angle(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1);
	}
	if(a.x2 == b.x2 && a.y2 == b.y2){
		cout<<"joined 4 yes"<<endl;
		return angle(a.x2, a.y2, a.x1, a.y1, b.x1, b.y1);
	}
	cout << "joined no" << endl;
	return false;
}

bool ratio(Lines a, int x, int y){
	//Is the third line in
	if (x < min(a.x1, a.x2) || x > max(a.x1, a.x2) || y < min(a.y1, a.y2) || y > max(a.y1, a.y2)){
		cout<<"ratio no"<<endl;       
		return false;
	}
	long aX = abs(a.x1-a.x2);
	long aY = abs(a.y1-a.y2);
	long aXmin = min(abs(x-a.x2), abs(x-a.x1));
	long aYmin = min(abs(y-a.y2), abs(y-a.y1));
	long aXmax = max(abs(x-a.x2), abs(x-a.x1));
	long aYmax = max(abs(y-a.y2), abs(y-a.y1));
	if(aXmax <= 4* aXmin && aYmax <= 4*aYmin && long (x - a.x2)*(a.y1-a.y2) == long(y-a.y2)*(a.x1-a.x2)){
		cout<<aXmax<<"  "<<4*aXmin<<endl;
		cout<<aYmax <<"  "<<4*aYmin<<endl;
		cout<<"ratio yes"<<endl;       
		return true;
	}
	cout<<"ratio 2 no"<< endl;
	return false;

}

bool isItA(Lines a, Lines b, Lines c){
	if( joined(a,b)){
		if(ratio(a, c.x1, c.y1) && ratio(b, c.x2, c.y2)){
			cout<<"Is it A yes"<<endl;
			return true;
		}else if(ratio(b, c.x1, c.y1) && ratio(a, c.x2, c.y2)){
			cout<<"is it A 2 yes"<<endl;
			return true;
		}else{
			cout<<"is it A no"<<endl;
			return false;
		}
	}
	cout<<"is it A 2 no"<<endl;
	return false;
}

int main(){
	
	int numOfLines;
	cin >> numOfLines;

	for(int i = 0; i < numOfLines; i++){

		Lines a,b,c;
		a = setLines();
		b = setLines();
		c = setLines();
		if(i == 5){
			printL(a);
			cout<<"| ";
			printL(b);
			cout<<"| ";
			printL(c);
			cout<<endl;
		}

		else if(isItA(a,b,c) || isItA(b,c,a) || isItA(c,a,b)){
			cout<< "YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}



	return 0;
}
