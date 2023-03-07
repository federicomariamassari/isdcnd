#include "matrix.h"

using namespace std;

/* Create a matrix of zeros with dimensions n_rows x n_cols.
 *
 * Example:
 *  >> zeros(2, 3);
 * 
 * Returns:
 *  >> {{0, 0, 0}, {0, 0, 0}}
 */
t_grid zeros(int n_rows, int n_cols)
{
    t_grid grid (n_rows, vector<float> (n_cols, 0.));
    return grid;
}

/* Create an n-dimensional matrix of zeros with diagonal of ones.
 *
 * Example:
 *  >> identity(3);
 * 
 * Returns:
 *  >> {{1, 0, 0}, {0, 1, 0} {0, 0, 1}}
 */
t_grid identity(int n)
{
    t_grid I = zeros(n, n);

    for (int i=0; i < n; i++) {
        I[i][i] = 1.;
    }

    return I;
}

Matrix::Matrix(t_grid G)
{
    grid = G;
    rows = grid.size();
    cols = grid[0].size();
}

void Matrix::set_grid(t_grid G)
{
    grid = G;
}

t_grid Matrix::get_grid()
{
    return grid;
}

vector<float>::size_type Matrix::get_rows()
{
    return rows;
}

vector<float>::size_type Matrix::get_cols()
{
    return cols;
}

/* Returns dot product between vectors p (row of A) and q (column of B).
 *
 * Example: 
 *  >> dot_product({1, 2, 3}, {4, 5, 6});
 * 
 * Returns: 
 *  >> (1 * 4) + (2 * 5) + (3 * 6) = 32
 */
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

bool Matrix::is_square()
{
    return rows == cols;
}

/* Returns the minor (i.e., determinant) of a 2x2 submatrix.
 *
 * Example:
 *  >> get_minor({{1, 2}, {3, 4}});
 * 
 * Returns:
 *  >> (1 * 4) - (2 * 3) = -2
 */
float Matrix::get_minor(t_grid G)
{
    float a = G[0][0];
    float b = G[0][1];
    float c = G[1][0];
    float d = G[1][1];

    return (a * d) - (b * c);
}

/* Returns submatrix formed by deleting first row, j-th column of input matrix.
 *
 * Example:
 *  >> Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
 *  >> A.get_submatrix(3);
 * 
 * Returns:
 *  >> {{4, 5}, {7, 8}}
 */
t_grid Matrix::get_submatrix(int col)
{
    t_grid submatrix;
    vector<float> row;

    for (int i=1; i < rows; i++)
    {
        row.clear();
        for (int j=0; j < cols; j++) {
            if (j != col) {
                row.push_back(grid[i][j]);
            }
        }
        submatrix.push_back(row);
    }

    return submatrix;
}

/* Returns the sum of the diagonal elements of a square matrix.
 *
 * Example:
 *  >> Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
 *  >> A.trace();
 * 
 * Returns:
 *  >> 1 + 5 + 9 = 15
 */
float Matrix::trace()
{
    if (!is_square()) {
        throw length_error("Cannot calculate the trace of a non-square matrix.");
    }

    float s = 0.;
    
    for (int i=0; i < rows; i++) {
        s += grid[i][i];
    }

    return s;
}

/* Calculates determinant of square matrices up to 3x3.
 *
 * Example:
 *  >> Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
 *  >> A.determinant();
 * 
 * Returns:
 *  >> (-1)^1 * (5*9 - 6*8) + (-1)^2 * (4*9 - 6*7) + (-1)^3 * (4*8 - 5*7) = 0
 */
float Matrix::determinant()
{
    if (!is_square()) {
        throw length_error("Cannot calculate determinant of a non-square matrix.");
    }
    
    if (rows > 3) {
        throw logic_error("Calculating determinant not implemented for matrices larger than 3x3.");
    }

    if (rows == 1) {
        return grid[0][0];

    } else if (rows == 2) {
        return get_minor(grid);

    } else {
        float det = 0;

        // In matrix algebra rows and cols start from index 1, which is convenient to get sign (-1)^(i+j) 
        for (int j=1; j < cols+1; j++) {
            t_grid submatrix = get_submatrix(j-1);
            det += pow(-1, 1+j) * grid[0][j-1] * get_minor(submatrix);
        }
        return det;
    }
}

/* Calculates the inverse of matrices up to 3x3 using Cayley-Hamilton formulae.
 * 
 * Example:
 *  >> Matrix A = {{1, -2, -3}, {-4, -5, -6}, {7, 8, 9}};
 *  >> A.inverse();
 * 
 * Returns (tol: 1e-5):
 *  >> {{0.5,  -1,  -0.5}, {-1,  5,  3}, {0.5, -3.66667, -2.16667}}
 */
Matrix Matrix::inverse()
{
    if (!is_square()) {
        throw length_error("Non-square Matrix does not have an inverse.");
    }

    if (rows > 3) {
        throw logic_error("Inversion is not implemented for matrices larger than 3x3.");
    }

    float det = determinant();
    if (det == 0) {
        throw invalid_argument("Inverse does not exist for singular matrices (determinant == 0).");
    }

    if (rows == 1)
    {
        return Matrix({{(float) pow(det, -1)}});

    } else if (rows == 2) {
        // Cayley-Hamilton decomposition of a 2x2 matrix
        return (Matrix(identity(rows)) * trace() - Matrix(grid)) * (float) pow(det, -1);

    } else {
        // Cayley-Hamilton decomposition of a 3x3 matrix
        Matrix g = (Matrix) grid;
        return (Matrix(identity(rows)) * (pow(trace(), 2) - (g * g).trace()) * 0.5 - g * trace() + (g * g)) * pow(det, -1);
    }
}

/* Switch input matrix rows and columns.
 *
 * Example:
 *  >> Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
 *  >> A.transpose();
 * 
 * Returns:
 *  >> {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}}
 */
Matrix Matrix::transpose()
{
    t_grid transpose = zeros(cols, rows);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            
            transpose[j][i] = grid[i][j];
        }
    }
    return Matrix(transpose);
}

Matrix Matrix::operator+(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be added if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    t_grid matrix_sum = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            matrix_sum[i][j] = grid[i][j] + other_grid[i][j];
        }
    }
    return Matrix(matrix_sum);
}

Matrix Matrix::operator-(Matrix other)
{
    if (rows != other.get_rows() || cols != other.get_cols()) {
        throw invalid_argument("Matrices can only be subtracted if their dimensions are the same.");
    }

    t_grid other_grid = other.get_grid();
    t_grid matrix_sub = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            matrix_sub[i][j] = grid[i][j] - other_grid[i][j];
        }
    }
    return Matrix(matrix_sub);
}

Matrix Matrix::operator-()
{
    t_grid matrix_neg = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            matrix_neg[i][j] = -grid[i][j];
        }
    }
    return Matrix(matrix_neg);
}

Matrix Matrix::operator*(Matrix other)
{
    if (cols != other.get_rows()) {
      throw length_error("Number of columns of A must match number of rows of B.");
    }

    Matrix other_transpose = other.transpose();
    t_grid matrix_mul = zeros(rows, other.get_cols());
    
    for (int i=0; i < rows; i++) {
        for (int j=0; j < other.get_cols(); j++) {
            matrix_mul[i][j] = dot_product(grid[i], other_transpose.grid[j]);
        }
    }
    return Matrix(matrix_mul);
}

Matrix Matrix::operator*(float scalar)
{
    t_grid matrix_rmul = zeros(rows, cols);

    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            matrix_rmul[i][j] = scalar * grid[i][j];
        }
    }
    return Matrix(matrix_rmul);
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

bool Matrix::operator==(Matrix other)
{
    // Check if compared matrices have same size
    if (rows != other.get_rows() || cols != other.get_cols()) {
        return false;
    }

    // Check if matrices are (almost) identical for each element i,j
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {

            // Set maximum tolerance level
            if(abs(grid[i][j] - other.grid[i][j]) > 1e-5) {
                return false;
            }
        }
    }
    return true;
}
