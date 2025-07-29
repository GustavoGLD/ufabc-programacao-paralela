#include <mpi.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char msg[100];

    if (rank == 0) {
        strcpy(msg, "BOM DIAAAAAAAAAAA!!!!!!\n");
    }
    
    MPI_Bcast(msg, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("P%d: %s", rank, msg);

    MPI_Finalize();
    return 0;
}
