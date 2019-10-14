
#include <iostream>
#include <mpi.h>
//#include "/usr/local/include/mpi.h"
#define MCW MPI_COMM_WORLD

using namespace std;

int mask(const char *m){
    /* m[7] corresponds to 0th bit */
    // TODO: write your code here
    // return 1 if you match the mask
    // return 0 if you don't

    /* incorrect code follows */
    int rank;
    MPI_Comm_rank(MCW, &rank);

    char binaryDigit;
    int remainingRank = rank;
    for(int i = 7; i>=0; --i){
	    if(remainingRank%2){
		    binaryDigit = '1';
	    }else{
		    binaryDigit = '0';
	    }
	    if(m[i] != binaryDigit && m[i] != 'X'){
		return 0;
	    }
	    remainingRank /=2;
    }
    //cout<<rank<<endl;
    //if(rank == 1) return 0;
    return 1;
}

void printRunning(const char* m, int running[64]){
    int size;
    MPI_Comm_size(MCW, &size); 
    cout<<m<<": ";
    for(int i=size-1;i>=0;--i)cout<<running[i];
    cout<<endl;
}
    
int main(int argc, char **argv){
    int running[64];

    int rank, size;
    int localrunning;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank); 
    MPI_Comm_size(MCW, &size); 

    const char *m1 = "XXXXXXXX";
    localrunning = mask(m1);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m1,running);

    const char *m2 = "XXXXXXX0";
    localrunning = mask(m2);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m2,running);

    const char *m3 = "XXXXXXX1";
    localrunning = mask(m3);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m3,running);

    const char *m4 = "XXXXXX00";
    localrunning = mask(m4);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m4,running);

    const char *m5 = "XXXXX1X1";
    localrunning = mask(m5);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m5,running);

    const char *m6 = "XXXXX110";
    localrunning = mask(m6);
    MPI_Gather(&localrunning,1,MPI_INT,running,1,MPI_INT,0,MCW);
    if(rank==0)printRunning(m6,running);

    MPI_Finalize();

    return 0;
}

