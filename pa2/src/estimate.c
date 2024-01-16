#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// subtract row A from row B
void subRow (double ** matrix, int a, int b, double multiplyBy, int columns){

    if (matrix == NULL){
        return;
    }
    
    //int i;

    for (int i = 0; i < columns; i++){
        matrix[b][i] = (matrix[b][i] - (multiplyBy * matrix[a][i]));

    }

}

// divide a row by a double denom
void divRow (double ** matrix, int row, double denom, int columns){

    if (matrix == NULL){
        return;
    }

    //int i;
    
    for (int i =0; i<columns; i++){
        matrix[row][i] = (matrix[row][i])/denom;

    }

}

/*invert matrix*/
double ** invertMatrix (double ** matrix, int row, int col){

    if(row != col){
        printf("Error: Row != Column \n");
        return NULL;
    }
    if(matrix == NULL){
        printf("Error: Matrix Null \n");
        return NULL;
    }
    
    double ** inverse = (double **)malloc(sizeof(double *)*row);
    if (!inverse){
        return NULL;
    }


    for (int i = 0; i < row; i++){
        inverse[i] = (double *)malloc(sizeof(double) * col);
        if (!inverse[i]){
            return NULL;
        }

    }

    /*Identity Matrix*/
    for (int i = 0; i < row; i++){
        for (int j = 0; j < row; j++){
            
            if (i ==j){
                inverse[i][j] = 1;
            }
            else{
                inverse[i][j] = 0;
            }

        }
    }
    
    double divideBy =1;
    double subtractBy = 1;

// Make into an upper triangular; Go Row by Row
// Lin Algebra Row Reduction Notes (Notablility)
    
    for (int i = 0; i < row; i++){
        // Make Row i start with 1
        divideBy = matrix[i][i];
        divRow(matrix, i, divideBy, row);
        divRow(inverse, i, divideBy, row);

        // Subtract Row i from Rows j
        for (int j = i+1; j < row; j++){

            subtractBy = matrix[j][i];
            subRow (matrix, i, j, subtractBy, row);
            subRow(inverse, i, j, subtractBy, row);

        }

    }

// Turn the left matrix into an identity matrix
    for (int i = row - 1; i > 0; i --){
        for (int j = i-1; j>= 0; j--){

            subtractBy= matrix[j][i];
            subRow(matrix, i, j, subtractBy, row);
            subRow(inverse, i, j, subtractBy, row);

        }
    }

    return inverse;
   

}

//free mem 
void freeMatrix(double **matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

// multiply two (double) matrices and returns double
double ** multiple(double ** a, double ** b, int rowA, int colA, int rowB, int colB){

    double total = 0;

    if (colA != rowB){
        return NULL;
    }

    //alloc
    double ** prod = (double **)malloc(sizeof(double *) * rowA);
    if (!prod){
        return NULL;
    }
 
    for (int i = 0; i < rowA; i++){
        prod[i] = (double *)malloc(sizeof(double)* colB);
        if (!prod[i]){
            for (int j = 0; j < i; j++) {
                free(prod[j]);
            }
            free(prod);
            return NULL;
        }
    }

    int y,z;
    
    for (int x = 0; x < rowA; x++){ 
        for (y = 0; y < colB; y++){ 
            for (z = 0; z < colA; z++){ //CHECK BACK IF ERROR!!!!

                total = total + a[x][z] * b[z][y]; //CHECK BACK IF ERROR!!!
            }

            prod[x][y] = total;
            total = 0;
        }
    }

    return prod;

}

// get transpose of a matrix
// check LinAlgebra Notes 
double ** transpose (double** matrix, int rows, int col){

    if (!matrix){
        return NULL;
    }

    int i, j;

    double ** res = (double **)malloc(sizeof(double *) * col);
    if (!res){
        return NULL;
    }

    for (i = 0; i < col; i++){

        res[i] = (double *)malloc(sizeof(double) * rows);
        
        if (!res[i]){
            return NULL;
        }

    }

    //insert values into res 
    for (i = 0; i < rows; i++){
        for (j = 0; j < col; j++){
            
            res[j][i] = matrix[i][j];

        }
    }

    return res;

}

int main (int argc, char** argv){

    int size1, size2=0;
	
    if (argc!=3) return 1;
	if (!argv[2]) return 1;
	
    for (size1=0; argv[1][size1]!='\0'; size1++) {};
	for (size2=0; argv[2][size2]!='\0'; size2++) {};
	size1++; size2++;

    char * file1 = (char *)malloc(sizeof(char) * size1);
    if (!file1) {
		return 1;
	}
	
    strcpy(file1, argv[1]);

	char * file2 = (char *)malloc(sizeof(char) * size2);
    if (!file2) {
		return 1;
	}
	
    strcpy(file2, argv[2]);

    FILE * fp;
    fp = fopen(file1, "r");
    if (!fp){
        return 1;
    }

    char * type = (char *)malloc(sizeof(char)* 6);
    if (!type){
        return 1;
    }

    if (fscanf(fp, "%s", type) != 1){
        return 1;
    }

    type[5]='\0';

    free(type);
    free(file1);

    //read the rows and col or input
    int row, col;

    if (fscanf(fp, "%d %d", &col, &row) !=2) return 1;
    col++;

    //malloc mem
    int i, j;
    
    double ** x = (double **)malloc(sizeof(double *) * row);
	double ** y = (double **)malloc(sizeof(double *) * row);

    if (!x || !y){
        return 1;
    }

    for (int i = 0; i< row; i++){

        x[i] = (double *)malloc(sizeof(double) * col);
		y[i] = (double *)malloc(sizeof(double));

        if ( !x[i] || !y[i]){
            return 1;
        }
    }

    // take data from input into x and y
    int valid = 0;

    for (int i = 0; i < row; i++){
        for (int j = 0; j<col+1; j++){

            if (j == 0){
                x[i][j] = 1.0;
            }
            else if (j == col){
                valid = fscanf(fp, "%lf ", &y[i][0]);

                if (valid != 1){
                    return 1;
                }
            }
            else {
                valid = fscanf(fp, " %lf", &x[i][j]);
                
                if (valid != 1){
                    return 1;
                }
            }
        }
    }

    //Solve W
    double ** Transpose = transpose(x, row, col);
    if (Transpose == NULL){
        return 1;
    }

    double ** producto = multiple(Transpose, x, col, row, row, col);
    if (producto == NULL){
        return 1;
    }

    // free x cause it unnecessary
    freeMatrix(x,row);

    double ** inverse = invertMatrix(producto, col, col);
    if (inverse == NULL){
        return 1;
    }

    freeMatrix(producto,col);

    double ** producto2 = multiple(inverse, Transpose, col, col, col, row);
    if (producto2 == NULL){
        return 1;
    }

    freeMatrix(Transpose, col);
    freeMatrix(inverse, col);

    double ** W = multiple(producto2, y, col, row, row, 1);
    if (W == NULL){
        return 1;
    }

    freeMatrix(y, row);
    freeMatrix(producto2, col);

    fclose(fp);

    FILE *fp2;
    fp2 = fopen(file2, "r");
    if(!fp2){
        return 1;
    }

    char * type2 = (char *)malloc(sizeof(char)* 5);
   
    if (!type2) {
        return 1;
    }
	
    if (fscanf(fp2, "%s ", type2)!=1) {
        return 1;
    }
	
    type2[4]='\0';

    free(type2);
    free(file2);

    int row2,col2;
   
    if (fscanf(fp2, "%d %d", &col2, &row2) !=2){
        return 1;
    }
    col2++;

    //malloc mem
    double ** data = (double **)malloc(sizeof(double *) * row2);
    
    if(!data){
        return 1;
    }

    for (int i = 0; i < row2; i++){
        data[i] = (double *)malloc(sizeof(double) * col2);
        
        if (!data[i]){
            return 1;
        }
    }

    valid = 0;

    // insert info into data
    for (i=0; i<row2; i++)  {
		for (j=0; j<col2; j++) {
			
            if (j==0) {
				data[i][j] = 1.0;
			} else {
				valid = fscanf(fp2, " %lf", &data[i][j]);
				if (valid!=1) return 1;
			}
		}
	}

    //New Prices
    double ** new = multiple(data, W, row2, col2, col, 1);

    if (new == NULL){
        return 1;
    }

    //loop to print
    for (i = 0; i < row2; i++){
        for (j = 0; j < 1; j++){

            printf("%.0f", new[i][j]);

        }

        printf("\n");
    }

    freeMatrix(data,row2);
    freeMatrix(new, row2);
    freeMatrix(W, col);
    fclose(fp2);

    
    return 0;

}