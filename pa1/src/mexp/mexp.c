#include<stdio.h>
#include<stdlib.h>

int main (int argc, char** argv){
    
    if (argc !=2){
        printf("Enter input \n");
        return EXIT_FAILURE;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("File is NULL \n");
        return EXIT_FAILURE;

    }

    int i, j, n, numberofTimes;
    fscanf(fp, "%d", &n);

    //allocate memory
    int **M = (int **)malloc(n * sizeof(int *));
    int **M1 = (int **)malloc(n * sizeof(int *));
    int **res = (int **)malloc(n * sizeof(int *));

    for (i = 0; i < n; i++){

        M[i] = (int *)malloc(n * sizeof(int));
        M1[i] = (int *)malloc(n * sizeof(int));
        res[i] = (int *)malloc(n * sizeof(int));

    }

    for (int i = 0; i < n; i++){
        for (int j =0; j < n; j++){

            fscanf(fp, "%d", &M[i][j]);
            M1[i][j] = M[i][j];

        }


    }

    fscanf(fp, "%d", &numberofTimes);

    for (int m = 0; m < numberofTimes -1; m++){

        for (int i = 0; i < n; i++){
            
            for (int j = 0; j < n; j++){

                res[i][j] = 0;
                
                for (int k = 0; k < n; k++){

                    res[i][j] += M[i][k] * M1[k][j];
                }
            }
        }

        for ( int i = 0; i < n; i++){

            for (int j = 0; j < n; j++){

                M[i][j] = res [i][j];

            }
        }

    }

    for (int i = 0; i < n; i++){

        for (j = 0; j < n; j++){
            printf("%d", M[i][j]);
            if (j < n-1){
                printf(" ");
            }

        }

        printf("\n");

    }

    for (i = 0; i < n; i++) {
    free(M[i]);
    free(M1[i]);
    free(res[i]);
    }
    
    free(M);
    free(M1);
    free(res);


    fclose(fp);

    return EXIT_SUCCESS;


}