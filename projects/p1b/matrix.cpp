#include <iostream>
#include <numeric>
#include "matrix.h"

using namespace std;


Matrix::Matrix(t_grid G)
{
    grid = G;
    rows = grid.size();
    cols = grid[0].size();
};


void Matrix::set_grid(t_grid G)
{
    grid = G;
};

t_grid Matrix::get_grid()
{
    return grid;
};


vector<float>::size_type Matrix::get_rows()
{
    return rows;
};


vector<float>::size_type Matrix::get_cols()
{
    return cols;
}


float Matrix::dot_product(vector<float> p, vector<float> q)
{
    float s = 0.;
    int length = p.size();
    vector<float> temp (length);

    for (int k=0; k < length; k++) {
      temp[k] = p[k] * q[k];
    }

    s = accumulate(temp.begin(), temp.end(), 0.);

    return s;
}


Matrix Matrix::zeros(int n_rows, int n_cols)
{
    t_grid grid(n_rows, vector<float> (n_cols, 0.));
    rows = grid.size();
    cols = grid[0].size();

    return Matrix(grid);
};

Matrix Matrix::identity(int n)
{
    Matrix I = zeros(n, n);

    for (int i=0; i < n; i++) {
        I.grid[i][i] = 1.;
    }
    return I;
};


Matrix Matrix::matrix_transpose()
{
    Matrix transpose = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < rows; j++) {
            
            transpose.grid[j][i] = grid[i][j];
        }
    }
    return transpose;
}


Matrix Matrix::matrix_addition(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be added if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    Matrix matrix_sum = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            matrix_sum.grid[i][j] = grid[i][j] + other_grid[i][j];
        }
    }
    return matrix_sum;
};


Matrix Matrix::matrix_subtraction(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be subtracted if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    Matrix matrix_sub = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            matrix_sub.grid[i][j] = grid[i][j] - other_grid[i][j];
        }
    }
    return matrix_sub;
}


Matrix Matrix::matrix_negation()
{
    Matrix matrix_neg = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            matrix_neg.grid[i][j] = -grid[i][j];
        }
    }
    return matrix_neg;
}


Matrix Matrix::matrix_multiplication(Matrix other)
{
    if (cols != other.get_rows()) {
      throw length_error("Number of columns of A must match number of rows of B.");
    }

    Matrix other_transpose = other.matrix_transpose();
    Matrix matrix_mul = zeros(rows, other_transpose.get_cols());
    
    for (int i=0; i < rows; i++) {
        for (int j=0; j < other.get_cols(); j++) {
            matrix_mul.grid[i][j] = dot_product(grid[i], other_transpose.grid[j]);
        }
    }
    return matrix_mul;
}


Matrix Matrix::matrix_right_multiplication(float scalar)
{
    Matrix matrix_rmul = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            matrix_rmul.grid[i][j] = scalar * grid[i][j];
        }
    }
    return matrix_rmul;
}


Matrix Matrix::matrix_right_multiplication(Matrix other)
{
    if (other.get_cols() != rows) {
      throw length_error("Number of columns of A must match number of rows of B.");
    }

    Matrix matrix_rmul = zeros(rows, other.get_cols());

    for (int i=0; i < rows; i++) {
        for (int j=0; j < other.get_cols(); j++) {
            matrix_rmul.grid[i][j] = dot_product(grid[i], other.grid[j]);
        }
    }
    return matrix_rmul;
}


void Matrix::matrix_print()
{
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
