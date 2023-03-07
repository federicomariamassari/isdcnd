#include <iostream>
#include <vector>
#include <numeric>

typedef std::vector< std::vector<float> > t_grid;
t_grid zeros(int n_rows, int n_cols);
t_grid identity(int n);

class Matrix
{
    private:
        t_grid grid;
        std::vector<float>::size_type rows;
        std::vector<float>::size_type cols;

        float dot_product(std::vector<float> p, std::vector<float> q);
        bool is_square();
        float get_minor(t_grid G);
        t_grid get_submatrix(int col);

    public:
        Matrix(t_grid G);

        void set_grid(t_grid G);
        t_grid get_grid();
        std::vector<float>::size_type get_rows();
        std::vector<float>::size_type get_cols();

        float trace();
        float determinant();
        Matrix inverse();
        Matrix transpose();
        Matrix operator+(Matrix other);     // Matrix addition (A + B)
        Matrix operator-(Matrix other);     // Matrix subtraction (A - B)
        Matrix operator-();                 // Matrix negative (-A)
        Matrix operator*(Matrix other);     // Matrix multiplication (A * B)
        Matrix operator*(float scalar);     // Matrix right multiplication (x * A)

        void matrix_print();
        bool operator==(Matrix other);      // Are matrices identical (tol: 1e-5)?
};