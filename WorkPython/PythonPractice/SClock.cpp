#include <iostream>

using namespace std;

string SPADE = "\xe2\x99\xa0";
string HEART = "\xe2\x99\xa5";
string CLUBS = "\xe2\x99\xa3";
string DIMON = "\xe2\x99\xa6";

string SUITS [] = {SPADE,HEART,CLUBS,DIMON};

struct Card(s,v){
	string suit = s;
	string value = v;
}

Card makeDeck(){
	string vals [] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

	Card d [52];

	

	return d
}


int main(){
	 

	


	for( int i = 0; i <4; i++){
		 
		cout<<i<<'\t'<<SUITS[i]<<endl;
	}


	//string a = "\xe2\x99\xa5";
	//cout<<SPADE<<endl;

	return 0;
}
