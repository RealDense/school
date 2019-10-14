

#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cmath>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

enum illiacMeshICF {plus1,minus1,plusn,minusn,up,down,lft,rght};
enum pm2iICF {pls,mins};


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

int pm2i(const char *m, enum pm2iICF pORm, int i, int data){
	int send, rank, size;
	int mult = 1;
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);

	if(pORm == mins) mult = -1;

	if(mask(m)){
		send = rank + (pow(2,i)*mult);
		if (send >= size) send = send%size;
		if (send < 0) send = send + size;
		MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
		MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
	}
	
	return data;

}

int cube(const char *m, int i, int data){
    //TODO:  write your code here
    int rank, send, size;
    /*
    MPI_Comm_rank(MCW, &rank);
    if(mask(m)){	
	send = (rank xor (1<<i));
	MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
	MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

	    
    }else{
	//return data;	    
    }
    */
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    int shift = pow(2,i) * 2;
    if (mask(m)){
		if(rank%shift < shift/2){
			return pm2i(m, pls, i, data);
		}else{
			return pm2i(m, mins, i, data);
		}	
    }
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

    if(!rank) cout<<"\ncube 0:\n";
    data = cube(m,0,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\ncube 1:\n";
    data = cube(m,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\ncube 2:\n";
    data = cube(m,2,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    const char *m1="XXXXXXX0";
    if(!rank) cout<<"\ncube 1:\n";
    data = cube(m1,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m1,running);
    MPI_Barrier(MCW);

    MPI_Finalize();

    return 0;
}


