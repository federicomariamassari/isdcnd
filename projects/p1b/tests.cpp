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

    Matrix C = Matrix(
        {{1, -2, -3}, 
         {-4, -5, -6},
         {7, 8, 9}}
    );
    
    Matrix D = Matrix(
        {{1, 2, 3}, 
         {4, 5, 6}}
    );

    // Test trace
    float trace = 5;
    assert(A.trace() == trace);

    // Test determinants up to 3x3
    assert(Matrix({{1},}).determinant() == 1);
    assert(A.determinant() == -2);
    assert(C.determinant() == 6);

    // Test matrix inverse 2x2
    Matrix A_inverse = Matrix(
        {{-2., 1.},
         {1.5, -0.5}}
    );

    assert(A_inverse == A.inverse());

    // Test matrix inverse 3x3 (tol: 1e-5)
    Matrix C_inverse = Matrix(
        {{0.5,  -1.,  -0.5},
         {-1.,  5.,  3.},
         {0.5, -3.66667, -2.16667}}
    );

    assert(C_inverse == C.inverse());

    // Test matrix negation
    Matrix minus_A = Matrix(
        {{-1, -2}, 
         {-3, -4}}
    );

    assert(minus_A == -A);

    // Test matrix sum
    Matrix A_plus_B = Matrix(
        {{6, 8}, 
         {10, 12}}
    );

    assert(A_plus_B == A + B);

    // Test matrix subtraction
    Matrix A_minus_B = Matrix(
        {{-4, -4},
         {-4, -4}}
    );

    assert(A_minus_B == A - B);

    // Test matrix transpose
    Matrix A_transpose = Matrix(
        {{1, 3}, 
         {2, 4}}
    );

    assert(A_transpose == A.transpose());

    // Test matrix multiplication 2x2
    Matrix A_times_B = Matrix(
        {{19, 22}, 
         {43, 50}}
    );

    assert(A_times_B == A * B);

    // Test matrix multiplication 2x3
    Matrix D_times_C = Matrix(
        {{14, 12, 12},
         {26, 15, 12}}
    );

    assert(D_times_C == D * C);

    // Test matrix multiplication 3x2
    Matrix C_times_D_transpose = Matrix(
        {{-12, -24},
         {-32, -77},
         {50, 122}}
    );

    assert(C_times_D_transpose == C * D.transpose());

    // Test matrix right multiplication by scalar
    int x = 2;
    Matrix x_times_A = Matrix(
        {{2, 4}, 
         {6, 8}}
    );

    assert(x_times_A == A * x);

    cout << "All tests passed." << endl;

    return 0;
}