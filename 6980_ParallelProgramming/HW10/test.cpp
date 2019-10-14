#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int size = 16;
	int size2 = 8;

	cout<<log2(size)<<endl<<log2(size2)<<endl;


	for(int i = 0; i < 16; i++){
		cout<<i<<"  ";

		//if(i xor (1<<0)) cout<<"yes ";
		//else cout<<"no  ";
		//if(i and (1<<3)) cout<<"yes ";
		//else cout<<"no  ";
		if((i & (1<<0))) cout<<"yes ";
		else cout<<"no  ";
		if((i & (1<<1))) cout<<"yes ";
		else cout<<"no  ";
		if(i & (1<<2)) cout<<"yes ";
		else cout<<"no  ";
		cout<<endl;
	}


	return 0;
}
