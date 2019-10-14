#include <iostream>

using namespace std;

void convertDecimalToBinary(int n){
	char binaryNumber[] = "00000000";
	int remainder;
	int i =1;
	int step = 1;
	//if(n == 0) return 0;
	for(int i = 7; i>=0; --i){ //(n != 0){
		if(n == 0) break;
		if(remainder = n%2){
			binaryNumber[i] = '1';
		}else{
			binaryNumber[i] = '0';
		}
		n /=2;
		//binaryNumber[i] = char(remainder);
	}
	cout << binaryNumber;
	//return binaryNumber;
	
}

int main(){
	//string


	cout<< "0 is : ";
	convertDecimalToBinary(0);
	cout<<endl;
	cout<< "3 is : ";
	convertDecimalToBinary(3);
	cout<<endl;
	cout<< "8 is : ";
	convertDecimalToBinary(8);
	cout<<endl;
	cout<< "4 is : ";
	convertDecimalToBinary(4);
	cout<<endl;
	cout<< "5 is : ";
	convertDecimalToBinary(5);
	cout<<endl;



	return 0;
}
