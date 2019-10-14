
#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cmath>
#define MCW MPI_COMM_WORLD

using namespace std;

enum pOs {pe, swtch, nothing};
struct process {
	pOs ps;
	int stage;
	int upperIn;
	int upperOut;
	int lowerIn;
	int lowerOut;
};

//int getRank(){
//	int rank;
//	MPI_Comm_rank(MCW, &rank);
//	return rank;
//}

//int getSize(){
//	int size;
//	MPI_Comm_size(MCW, &size);
//	return size;
//}

int numOfPe(int rank, int size){
	int n = 2;

	while(true){
		if(pow(2, n) + pow(2, n-1) * log2(pow(2, n)) > size){
			//n = log2(n);
			break;
		}
		n ++;
	}
	n--;
	return pow(2,n);
}

int whatStage(int rank, int size){
	int stage;
	int n = numOfPe(rank, size);
	int switchLimit = n + (n/2) * log2(n);

	if(rank < n){
		return -1;
	}
	return (log2(n)-((rank-n)/(n/2)+1));


	//return stage;

}

pOs whatProcess(int rank, int size){
	int n = numOfPe(rank, size);

	if(rank < n){
		//cout<<"I am " << rank << " and a PE" <<endl;
		return pe;
	}else if(rank < n + (n/2) * log2(n)){
		//cout<<"I am " << rank << " and a switch" <<endl;
		return swtch;
	}else{
		//cout<<"I am " << rank << " and nothing" <<endl;
		return nothing;
	}

}

int sendTo(process pro, int size, int rank, bool upper){
	int n = numOfPe(rank, size);
	int m = n/2;

	if(pro.ps == pe){
		if(rank < n / 2){
			return rank + 2 * m;
		}else{
			return rank + m;
		}
	}

	if(pro.ps == swtch){
		if(pro.stage == 0){
			if(upper){
				return rank%m * 2;
			}else{
				return rank%m * 2 + 1;
			}
		}
		else{
			if(rank % (int) (pow(2,pro.stage)) < pow(2,pro.stage-1) ){
				if(upper){
					return rank + m;
				}else{
					return rank + m + pow(2,pro.stage-1);
				}
			}else{
				if (upper){
					return rank + m - pow(2,pro.stage-1);
				}else{
					return rank + m;
				}
			}
		}
	}
	return -1;
}

int getFrom(process pro, int size, int rank, bool upper){
	int n = numOfPe(rank, size);
	int m = n/2;

	if(pro.ps == pe){
		//cout<< rank << "  " << rank/2<< endl;
		return rank/2 + n + m * log2(n/2);
		//if(rank%2 == 0){
		//	return rank/2 + pow(2, m);
		//}else{
		//	return (rank - 1)/2 + pow(2,m);
		//}
	}

	if(pro.ps == swtch){
		if(pro.stage == log2(m)){
			if(upper){
				return rank%m;
			}else{
				return rank%m + m;
			}
		}
		else{
			if(rank % (int) (pow(2,pro.stage+1)) < pow(2,pro.stage) ){
				if(upper){
					return rank - m;
				}else{
					return rank - m + pow(2, pro.stage);
				}
			}else{
				if (upper){
					return rank - m - pow(2,pro.stage);
				}else{
					return rank - m ;
				}
			}
		}
	}
	return -1;
}


process whatAmI(int rank, int size){
	process pro;
	pro.ps = whatProcess(rank, size);
	if(pro.ps == swtch){
		pro.stage = whatStage(rank, size);
	}

	pro.upperOut = sendTo(pro, size, rank, true);
	pro.upperIn = getFrom(pro, size, rank, true);
	pro.lowerOut = sendTo(pro, size, rank, false);
	pro.lowerIn = getFrom(pro, size, rank, false);
	

	return pro;
}


void print(int rank, process pro){
	if(pro.ps == pe){
		cout<<"I am " << rank << " and a PE" <<endl;
		cout<<"\tUpper send: "<<pro.upperOut<<endl;
		cout<<"\tUpper receive: "<<pro.upperIn<<endl;
		//return pe;
	}else if(pro.ps == swtch){
		cout<<"I am " << rank << " and a switch in stage "<<pro.stage <<endl;
		cout<<"\tUpper send: "<<pro.upperOut<<endl;
		cout<<"\tLower send: "<<pro.lowerOut<<endl;
		cout<<"\tUpper receive: "<<pro.upperIn<<endl;
		cout<<"\tLower receive: "<<pro.lowerIn<<endl;

		//return swtch;
	}else{
		cout<<"I am " << rank << " and nothing" <<endl;
		//return nothing;
	}



}


int main(int argc, char **argv){
	int rank, size;
	int data;
	int running[64];
	const char *m="XXXXXXXX";

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);

	process pro = whatAmI(rank, size);

	MPI_Barrier(MCW);
	print(rank, pro);
	MPI_Barrier(MCW);


	return 0;
}
