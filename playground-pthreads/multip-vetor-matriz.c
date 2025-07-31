#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int len_linhas, len_cols;
double *vetor_saida, *matriz_entrada, *vetor_entrada;

void *pth_mat_vector(void *rank) {
    long my_rank = (long) rank;
    int i, j;

    int len_linhas_local = len_linhas / thread_count;
    int my_first_row = my_rank * len_linhas_local;
    int my_last_row = (my_rank + 1) * len_linhas_local - 1;

    for (i = my_first_row; i <= my_last_row; i++) {
        vetor_saida[i] = 0.0;
        for (j = 0; j < len_cols; j++) {
            vetor_saida[i] += matriz_entrada[i * len_cols + j] * vetor_entrada[j];
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;

    if (argc != 4) {
        fprintf(stderr, "Uso: %s <n_threads> <m> <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    thread_count = strtol(argv[1], NULL, 10);
    len_linhas = strtol(argv[2], NULL, 10);
    len_cols = strtol(argv[3], NULL, 10);

    matriz_entrada = malloc(len_linhas * len_cols * sizeof(double));
    vetor_entrada = malloc(len_cols * sizeof(double));
    vetor_saida = malloc(len_linhas * sizeof(double));
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (int i = 0; i < len_linhas * len_cols; i++) {
        matriz_entrada[i] = 1.0;
    }

    for (int i = 0; i < len_cols; i++) {
        vetor_entrada[i] = 1.0;
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, pth_mat_vector, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    printf("Vetor resultado:\n");
    for (int i = 0; i < len_linhas; i++) {
        printf("%lf ", vetor_saida[i]);
    }
    printf("\n");

    free(matriz_entrada);
    free(vetor_entrada);
    free(vetor_saida);
    free(thread_handles);

    return 0;
}
