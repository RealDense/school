#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cmath>
#include <algorithm>
#define MCW MPI_COMM_WORLD

using namespace std;

enum pOs {pe, swtch, nothing};
enum tag {xoor, dest};
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

void pes(tag t, int sendTo[], process pro, bool kill){
	int rank, size;
	int tag;
	MPI_Status status;
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);
	int data = rank;
	//Dest

	if(t == xoor){
		tag = rank xor sendTo[rank];
		//cout<< tag<<endl;
	}else{
		tag = sendTo[rank];
	}

	if(kill){
		data = -1;
		MPI_Send(&data, 1, MPI_INT, pro.upperOut, 0, MCW);
		cout<<setw(4)<< left<< rank<<" sending KILL command\n";
	}

	else{
		cout << "Rank: "<< setw(4)<<left<< rank 
			<< right << setw(7)<< "Tag: "<< tag
			<< setw(20)<<"Sending to: "<< pro.upperOut
			<< setw(20)<< " Final Destination "<< sendTo[rank] << endl;
		//cout<<rank<<" sending to "<< pro.upperOut<<" with the tag "<< tag<<" to be recieved by "<<sendTo[rank]<<endl;
		MPI_Send(&data, 1, MPI_INT, pro.upperOut, tag, MCW);		
	}

	MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &status);
	if(data == -1){
		cout<<setw(4)<< left<< rank<<" has been TERMINATED\n";
	}else{
		cout<<"Rank: " << setw(4) << left<< rank
		<< right <<setw(10)<< "Recieved "<< data<<setw(9)<<"From: "<< status.MPI_SOURCE<< endl;
		if(data == sendTo[rank]){
			cout<< "Rank: "<< rank<<" SUCESS\n";
		}else{
			cout<< "Rank: "<< rank<<" FAILURE\n";
		}
		//cout<<rank<<" recieved "<< data<<" from "<< status.MPI_SOURCE<<endl;
	}
	//MPI_Barrier(MCW);
}

void switches(tag t, process pro){
	int rank, size;
	int sendTo;
	MPI_Status status;
	MPI_Comm_rank(MCW, &rank);
	MPI_Comm_size(MCW, &size);
	int data;

	bool killed = false;
	while(!killed){
		//data = -1;
		MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MCW, &status);
		if(data == -1){
			//Kill call
			cout<< setw(4) << left<<rank<<"   KILL code called\n";
			MPI_Send(&data, 1, MPI_INT, pro.upperOut, status.MPI_TAG, MCW);
			MPI_Send(&data, 1, MPI_INT, pro.lowerOut, status.MPI_TAG, MCW);
			killed = true;

		}else{
			if(t == xoor){
				bool fromTop = (status.MPI_SOURCE == pro.upperIn);
				
				if((status.MPI_TAG & (1<<pro.stage))){
					if(fromTop){
						//cout<<"Here\n";
						sendTo = pro.lowerOut;
					}else{
						sendTo = pro.upperOut;
					}
				}else{
					if(fromTop){
						//cout<<"Here\n";
						sendTo = pro.upperOut;
					}else{
						sendTo = pro.lowerOut;
					}
				}

			}else{ //destination
				//if tag == 1 send upper
				if(status.MPI_TAG & (1<<pro.stage)){
					sendTo = pro.upperOut;
				}else{
					sendTo = pro.lowerOut;
				}
			}
			cout << "Rank: "<< setw(4)<<left<< rank 
				<< right <<setw(20)<< "Recieved From: "<< status.MPI_SOURCE
				<< setw(10)<< "Tag: "<<status.MPI_TAG
				<< setw(20)<<"Sending to: "<<sendTo<< endl;
			MPI_Send(&data, 1, MPI_INT, sendTo, status.MPI_TAG, MCW);
		}
	}
	//MPI_Barrier(MCW);
	cout<<setw(4)<< left<< rank<<" has been TERMINATED\n";



}

void printExpected(int trial[], int num){

	cout<<"\tTHESE ARE THE EXPECTED RESULTS\n";
	for(int i = 0; i < num; i++){
		cout<<"Rank: "<<i<<"  should recieve: "<<trial[i]<<endl;
	}
	cout<<endl<<endl;
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

	int numPE = numOfPe(rank, size);
	int trial[numPE];

	for(int i = 0; i < numPE; i++){

		trial[i] = (i + numPE/2)%numPE;
	}
	//random_shuffle(trial[0], trial[numPE]);
	if(rank == 0)	printExpected(trial, numPE);
	

	MPI_Barrier(MCW);


	
	if(pro.ps == swtch){
		switches(xoor, pro);
	}


	if(pro.ps == pe){
		pes(xoor, trial, pro, false);
		//MPI_Barrier(MCW);
	}
	//MPI_Barrier(MCW);

	// for(int i = 0; i < numPE; i++){
	// 	trial[i] = numPE - 1 -i;
	// }
	// if(rank == 0){
	// 	cout<<"\n\n\tNEXT TEST\n\n";
	// 	printExpected(trial, numPE);
	// }

	// if(pro.ps == pe){
	// 	pes(xoor, trial, pro, false);
	// 	//MPI_Barrier(MCW);
	// }

	if(pro.ps == pe){
		pes(xoor, trial, pro, true);
	}

//	int pes = numOfPe(rank, size);
//	for(int i = 0; i < pes; i++){
//	}

//	print(rank, pro);

	
	MPI_Barrier(MCW);
	//cout<<"here\n";
	MPI_Finalize();
	//cout<<"    here\n";

	return 0;
}
