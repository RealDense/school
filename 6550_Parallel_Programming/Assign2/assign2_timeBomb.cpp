
#include <iostream>
#include <mpi.h>
#include <random>
#include <unistd.h>
#define MCW MPI_COMM_WORLD

using namespace std;

int whoToThrowItTo()
{
    int rank, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    while (true)
    {
        int reciever = rand() % size;
        if (reciever != rank)
        {
            return reciever;
        }
    }
}

int main(int argc, char **argv)
{

    int rank, size;
    int data;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    //Process 0 starts the game
    int timer;
    int thrownTo;
    srand(time(NULL));
    if (rank == 0)
    {
        timer = 10 + rand() % 20;
        thrownTo = whoToThrowItTo();
        cout << rank << " started the game with the bomb at " << timer << " and threw it to " << thrownTo << endl;
        MPI_Send(&timer, 1, MPI_INT, thrownTo, 0, MCW);
    }

    bool gameOver = false;

    while (!gameOver)
    {

        MPI_Recv(&timer, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
        sleep(.5);
        if (timer == 0)
        {
            cout << rank << " EXPLODED!!!\n   Sending end of game command\n";
            timer = -1;
            for (int i = 0; i < size; i++)
            {
                if (i != rank)
                {
                    MPI_Send(&timer, 1, MPI_INT, i, 0, MCW);
                }
            }
            gameOver = true;
            break;
        }
        else if (timer < 0)
        {
            gameOver = true;
            cout << rank << " was told the game is over\n";
            break;
        }

        thrownTo = whoToThrowItTo();
        cout << rank << " received the bomb with a timer of " << timer << ". Sent the bomb to " << thrownTo << endl;
        timer--;
        MPI_Send(&timer, 1, MPI_INT, thrownTo, 0, MCW);
    }

    MPI_Finalize();

    return 0;
}
