#include <stdio.h>

// Helper function to print a matrix
void print_matrix(int rows, int cols, int matrix[rows][cols], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 1. Matrix Addition
void add_matrices(int rows, int cols, int A[rows][cols], int B[rows][cols], int result[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// 2. Matrix Multiplication
void multiply_matrices(int rowsA, int colsA, int A[rowsA][colsA], int colsB, int B[colsA][colsB], int result[rowsA][colsB]) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0; // Initialize the result cell to 0
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// 3. Matrix Transpose
void transpose_matrix(int rows, int cols, int A[rows][cols], int result[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = A[i][j];
        }
    }
}

int main() {
    // Define dimensions
    int rows = 2, cols = 2;
    
    // Initialize matrices
    int matrix_X[2][2] = {
        {1, 2},
        {3, 4}
    };
    
    int matrix_Y[2][2] = {
        {5, 6},
        {7, 8}
    };
    
    // Resultant matrices
    int sum_matrix[2][2];
    int prod_matrix[2][2];
    int transposed_X[2][2];

    print_matrix(rows, cols, matrix_X, "Matrix X");
    print_matrix(rows, cols, matrix_Y, "Matrix Y");
    
    // Execute and print addition
    add_matrices(rows, cols, matrix_X, matrix_Y, sum_matrix);
    print_matrix(rows, cols, sum_matrix, "Addition (X + Y)");
    
    // Execute and print multiplication (X columns must equal Y rows, both are 2 here)
    multiply_matrices(rows, cols, matrix_X, cols, matrix_Y, prod_matrix);
    print_matrix(rows, cols, prod_matrix, "Multiplication (X * Y)");
    
    // Execute and print transpose
    transpose_matrix(rows, cols, matrix_X, transposed_X);
    print_matrix(cols, rows, transposed_X, "Transpose of X");

    return 0;
}
