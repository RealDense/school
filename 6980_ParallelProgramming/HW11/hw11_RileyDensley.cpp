
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

int cube(const char *m, int i, int data){
    //TODO:  write your code here
    int rank, send;
    MPI_Comm_rank(MCW, &rank);
    if(mask(m)){	
	send = (rank xor (1<<i));
	MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
	MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);

	    
    }else{
	//return data;	    
    }
    return data;
}


int pm2i(const char *m, enum pm2iICF pORm, int i, int data){
    //TODO: write your code here
    /*
    int send, rank, size;
    int mult = 1;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    if(pORm == mins) mult = -1;
    if(mask(m)){
	//cout<<(2**i)<<endl;
	send = rank + (pow(2,i)*mult);
	if(send >= size) send = send%size;
	if(send < 0) send = send + size;
	MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
	MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
    }
    */

   int rank, size, n, tempData;
   MPI_Comm_rank(MCW, &rank);
   MPI_Comm_size(MCW, &size);
   n = log2(size);
   tempData = data;
   
   char pm = '1';
   if(pORm == mins) pm = '0';
   for(int j = n-1; j>=i; j--){
       char mask[8] = {'X','X','X','X','X','X','X','X'};
       for(int k = i; k < j; k++){
           mask[7-k] = pm;
       }
       tempData = cube(mask,j,tempData);
       MPI_Barrier(MCW);
          
   }
   if(mask(m)){
       return tempData;
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

    if(!rank) cout<<"\nplus 2^0:\n";
    data = pm2i(m,pls,0,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nplus 2^1:\n";
    data = pm2i(m,pls,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nplus 2^2:\n";
    data = pm2i(m,pls,2,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nminus 2^0:\n";
    data = pm2i(m,mins,0,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nminus 2^1:\n";
    data = pm2i(m,mins,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    if(!rank) cout<<"\nminus 2^2:\n";
    data = pm2i(m,mins,2,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m,running);
    MPI_Barrier(MCW);

    const char *m1="XXXXXXX0";
    if(!rank) cout<<"\nplus 2^1:\n";
    data = pm2i(m1,pls,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m1,running);
    MPI_Barrier(MCW);

    const char *m2="XXXXXXX1";
    if(!rank) cout<<"\nplus 2^1:\n";
    data = pm2i(m2,pls,1,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m2,running);
    MPI_Barrier(MCW);

    const char *m3="XXXXXX00";
    if(!rank) cout<<"\nplus 2^2:\n";
    data = pm2i(m3,pls,2,rank);
    MPI_Gather(&data,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m3,running);
    MPI_Barrier(MCW);

    MPI_Finalize();

    return 0;
}


