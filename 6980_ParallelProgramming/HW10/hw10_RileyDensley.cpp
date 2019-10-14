



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

int pm2i(const char *m, enum pm2iICF pORm, int i, int data) {
	//TODO: write your code here
	int send, rank, size;
	int mult = 1;
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);
	if (pORm == mins) mult = -1;
	if (mask(m)) {
		//cout<<(2**i)<<endl;
		send = rank + (pow(2, i)*mult);
		if (send >= size) send = send % size;
		if (send < 0) send = send + size;
		MPI_Send(&data, 1, MPI_INT, send, 0, MCW);
		MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
	}
	return data;

}

int shuffleExchange(const char *m, ShuffExICF icf, int data){

    // TODO: write your code here
    int rank, send, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    int n = log2(size);
    int aData;
    int tempData;
    const char *evenM = "XXXXXXX0";
    const char *tempM = "XXXXXXXX";
    if(icf == shffle){

	    //data = pm2i(m, pls, 0, data);
	    // Step 1
	    if(mask(evenM)){
	    	aData = data;
	    }else{
		//data = aData;
	    }
	    //Step 2
	    if(mask(evenM)){
	    	data = pm2i(m, pls, 0, data);
	    }else{
		pm2i(m,pls,0,data);
	    }
    	    MPI_Barrier(MCW);
	    //Step 3
	    for(int j = 1; j<n; j++){
		    //step 4
		    if(rank & (1<<(j)) && mask(evenM)){
			    tempData = aData;
			    aData = data;
			    data = tempData;
		    }
		    //Step 5
		    //tempData = pm2i(m, pls, j, data);
		    if(mask(evenM)){

		    	data = pm2i(m, pls, j, data);
		    }else{
			pm2i(m, pls, j, data);
		    }
    		    MPI_Barrier(MCW);
	    }
	    //Step 6
	    //data = pm2i(m, pls, 0, data);
	    if(mask(evenM)){
	    	pm2i(m, pls, 0, data);
	    }else{
		data = pm2i(m,pls,0,data);
	    }
    	    MPI_Barrier(MCW);
	    //Step 7i
	    if(mask(evenM)){
		    //data = pm2i(m, pls, 0, data);
		    data = aData;
	    }
    	    MPI_Barrier(MCW);
	    return data;
    }

    
    if(icf ==xchange){
		if (rank % 2 < 1) {
			return pm2i(m, pls, 0, data);
		}
		else {
			return pm2i(m, mins, 0, data);
		}
	}
     
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


