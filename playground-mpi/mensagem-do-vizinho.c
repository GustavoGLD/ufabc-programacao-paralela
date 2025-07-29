#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int msg = rank * 10;

    int right = (rank + 1) % size;
    int left = (rank - 1 + size) % size;

    int recv;
    if (rank % 2 == 0) {
        MPI_Send(&msg, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&recv, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&msg, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    }

    printf("Processo %d recebeu %d\n", rank, recv);

    MPI_Finalize();
    return 0;
}
