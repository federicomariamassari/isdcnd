#include <iostream>
#include <vector>
#include <cassert>
#include "matrix.h"

using namespace std;

int main()
{
    Matrix A = Matrix(
        {{1, 2}, 
         {3, 4}}
    );

    Matrix B = Matrix(
        {{5, 6},
         {7, 8}}
    );
    
    // Test matrix negation
    Matrix A_negative = Matrix(
        {{-1, -2}, 
         {-3, -4}}
    );

    assert(A_negative.is_identical(A.matrix_negation()));

    // Test matrix sum
    Matrix A_plus_B = Matrix(
        {{6, 8}, 
         {10, 12}}
    );

    assert(A_plus_B.is_identical(A.matrix_addition(B)));

    // Test matrix subtraction
    Matrix A_minus_B = Matrix(
        {{-4, -4},
         {-4, -4}}
    );

    assert(A_minus_B.is_identical(A.matrix_subtraction(B)));

    // Test matrix transpose
    Matrix A_transpose = Matrix(
        {{1, 3}, 
         {2, 4}}
    );

    assert(A_transpose.is_identical(A.matrix_transpose()));

    // Test matrix multiplication 2*2
    Matrix A_times_B = Matrix(
        {{19, 22}, 
         {43, 50}}
    );

    assert(A_times_B.is_identical(A.matrix_multiplication(B)));

    // Test matrix right multiplication by scalar
    int x = 2;
    Matrix x_times_A = Matrix(
        {{2, 4}, 
         {6, 8}}
    );

    assert(x_times_A.is_identical(A.matrix_right_multiplication(x)));

    cout << "All tests passed." << endl;

    return 0;
}