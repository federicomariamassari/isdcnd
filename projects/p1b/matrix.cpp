#include <iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix()
{
    t_grid grid(3, vector<float> (3, 0));
    rows = grid.size();
    cols = grid[0].size();

};

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

std::vector<float>::size_type Matrix::get_rows()
{
    return rows;
};

std::vector<float>::size_type Matrix::get_cols()
{
    return cols;
}


Matrix Matrix::matrix_addition(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be added if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    t_grid result (rows, vector<float> (cols, 0.0));

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            result[i][j] = grid[i][j] + other_grid[i][j];
        }
    }

    return Matrix(result);
};


Matrix Matrix::matrix_subtraction(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be subtracted if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    t_grid result (rows, vector<float> (cols, 0.0));

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            result[i][j] = grid[i][j] - other_grid[i][j];
        }
    }

    return Matrix(result);
}


Matrix Matrix::matrix_negation()
{
    t_grid result (rows, vector<float> (cols, 0.0));

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            grid[i][j] = -grid[i][j];
        }
    }

    return Matrix(result);
}


Matrix Matrix::matrix_transpose()
{
    t_grid result (rows, std::vector<float> (cols, 0.0));

    for (int j=0; j < cols; j++) {
        for (int i=0; i < rows; i++) {
            
            result[i][j] = grid[j][i];
        }
    }

    return Matrix(result);
}


void Matrix::matrix_print()
{
    for (int i=0; i < get_rows(); i++) {
        for (int j=0; j < get_cols(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
