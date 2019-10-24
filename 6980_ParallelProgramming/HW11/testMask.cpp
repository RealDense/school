#include <iostream>
#include <iomanip>

using namespace std;

char * makeMask(int n, int j){
    char m [8];

    for( int i = 0; i <8; i++){
            m[i] = "X";
    }

    for( int i = 7; i >= 0; i--){
        if(i == 7-n-j){
            m[7-i] = "1";
        }
    }

    return m;


}

int main(){
    const char *m = "XXXXXXXX";

    cout<< m<<endl;
    char * n;
    n = makeMask(4, 1);
    cout<<n<<endl;


    return 0;
}