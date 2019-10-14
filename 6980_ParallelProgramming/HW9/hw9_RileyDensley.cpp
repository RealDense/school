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
	int mult =1;
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

int illiacMesh(const char *m, illiacMeshICF icf, int data){
    int rank,size,dest;
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    int n;
    n=sqrt(size);
    if(n*n!=size){
        cout<<"error: number of processes is not an even power of 2. ";
        cout<<"Quitting. ";
        exit(1);
    }

    //TODO: write your code here

    int send, receive;
    if(mask(m)){
    	if(icf == plus1){
		    //do stuff
		    return pm2i(m, pls, 0, data);
    	}else if(icf == minus1){
		    //dostuff
		    return pm2i(m, mins, 0, data);
    	}else if(icf == plusn){
		    //do stuff
		    return pm2i(m, pls, sqrt(n), data);
    	}else if(icf == minusn){
		    //do stuff
		    return pm2i(m, mins, sqrt(n), data);
	}


   	 MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
   	 MPI_Recv(&data, 1, MPI_INT, receive, 0, MCW, MPI_STATUS_IGNORE);
    }else{
	    //did not mask
    }
    return data;
}

void printRunning(const char* m, int running[64]){
    int rank,size;
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 
    int n;
    n=sqrt(size);
    //cout<<m<<": ";
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<setw(3)<<running[i*n+j]<<" ";
        }
        cout<<endl;
    }
}
using namespace std;

int main(int argc, char **argv){

    int rank, size;
    int data;
    int running[64];
    const char *m="XXXXXXXX";
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

    if(!rank) cout<<"\nplus 1:\n";
    data = illiacMesh(m,plus1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nminus 1:\n";
    data = illiacMesh(m,minus1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nplus n:\n";
    data = illiacMesh(m,plusn,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nminus n:\n";
    data = illiacMesh(m,minusn,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    MPI_Finalize();

    return 0;
}


