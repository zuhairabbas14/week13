#include <stdio.h>
#include <stdlib.h>

#define MARKED 1
#define UNMARKED 0

int main(void) {

    FILE *input_file = fopen("input.txt", "r");

    int x;
    fscanf(input_file, "%d", &x);
    int total_processes;
    fscanf(input_file, "%d", &total_processes);

    int *E = malloc(sizeof(int) * x);
    int *A = malloc(sizeof(int) * x);
    int **C = malloc(sizeof(int *) * total_processes);
    int **R = malloc(sizeof(int *) * total_processes);
    char *P = malloc(sizeof(char) * total_processes);


    for (int i = 0; i < x; ++i) {

        fscanf(input_file, "%d", E + i);
    }

    for (int i = 0; i < x; ++i) {

        fscanf(input_file, "%d", A + i);
    }

    

    for (int j = 0; j < total_processes; ++j) {

        C[j] = malloc(sizeof(int *) * x);
    }

    for (int k = 0; k < total_processes; ++k) {

        for (int i = 0; i < x; ++i) {

            fscanf(input_file, "%d", C[k] + i);
        }
    }

    for (int j = 0; j < total_processes; ++j) {

        R[j] = malloc(sizeof(int *) * x);
    }

    for (int k = 0; k < total_processes; ++k) {

        for (int i = 0; i < x; ++i) {

            fscanf(input_file, "%d", R[k] + i);
        }
    }

    
    for (int n = 0; n < total_processes; ++n) {

        P[n] = UNMARKED;
    }

    while (1) {

        int selected = -1;
        for (int i = 0; i < total_processes && selected == -1; ++i) {

            fflush(stdout);

            if (!P[i]) {

                int all = 1;
                for (int j = 0; j < x && all; ++j) {

                    if (A[j] < R[i][j]) {
                        all = 0;
                    }
                }

                if (all) {
                    selected = i;
                }
            }
        }

        if (selected != -1) {

            P[selected] = MARKED;
            for (int i = 0; i < x; ++i) {

                A[i] += C[selected][i];
            }

        } 

        else {

            break;
        }
    }

    int done = 1;
    for (int l = 0; l < total_processes && done; ++l) {

        done = P[l];
    }

    if (done) {

        FILE *result = fopen("output_ok", "w+");
        fprintf(result, "No deadlock is detected");
    } 
    else {

        FILE *result = fopen("output_dl", "w+");
        fprintf(result, " numbers of processes that are deadlocked:\n");

        for (int i = 0; i < total_processes; ++i) {

            if (!P[i]) {
                fprintf(result, "%d ", i + 1);
            }
        }
    }
}
