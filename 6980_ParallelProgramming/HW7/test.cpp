#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
	int size = 16;
	//int = 7;
	//
	//
	cout<<sqrt(size)<<endl;
	cout<<"rank   <<1"<<endl;
	for (int i = 0; i <size; i++){
		int send = (i<<1);
		cout<<i<<"    "<<send;	

		if(send >= size){
			send = (send xor (1<<(int) (sqrt(size))));
			send = (send xor 1<<0);
		}
		cout<<"    "<<send;
		cout<<endl;
	}





	return 0;

}
