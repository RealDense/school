



#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cmath>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

enum illiacMeshICF {plus1,minus1,plusn,minusn,up,down,lft,rght};
enum pm2iICF {pls,mins};
enum ShuffExICF {shffle,xchange}; 
int mask(const char *m){
    /* m[7] corresponds to 0th bit */
    // return 1 if you match the mask
    // return 0 if you don't
    int rank, r, size;
    bool match=true;
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    r=rank;
    for(int bit=7;bit>=0;--bit){
        if(m[bit]!='X'){
            if(r%2==0&&m[bit]=='1')match=false;
            if(r%2==1&&m[bit]=='0')match=false;
        }
        r/=2;
    }
    if(match){
        return 1;
    }else{
        return 0;
    }
}

int shuffleExchange(const char *m, ShuffExICF icf, int data){

    // TODO: write your code here
    int rank, send, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    if(icf == shffle){
	send = (rank<<1);
	if(send >= size){
		send = (send xor (1<<(int) (log2(size))));
		send = (send xor 1<<0);
	}
	//cout<<rank<<"  "<<send<<endl;

    }
    if(icf ==xchange){
	send = (rank xor 1<<0);

    }
    MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
    MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

    return data;
     
}

void printRunning(const char* m, int running[64]){
    int rank,size;
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    cout<<m<<": ";
    for(int i=0;i<size;++i){
            cout<<setw(3)<<running[i];
    }
    cout<<endl;
}

int main(int argc, char **argv){

    int rank, size;
    int data;
    int running[64];
    const char *m="XXXXXXXX";
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

    if(!rank) cout<<"\nshuffle:\n";
    data = shuffleExchange(m,shffle,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nexchange:\n";
    data = shuffleExchange(m,xchange,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    MPI_Finalize();

    return 0;
}


