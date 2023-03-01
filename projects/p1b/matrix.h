#include <vector>

typedef std::vector< std::vector<float> > t_grid;

class Matrix
{
    private:
        t_grid grid;
        std::vector<float>::size_type rows;
        std::vector<float>::size_type cols;

        float dot_product(std::vector<float> p, std::vector<float> q);
        bool is_square();

    public:
        Matrix(t_grid G);

        void set_grid(t_grid G);
        t_grid get_grid();
        std::vector<float>::size_type get_rows();
        std::vector<float>::size_type get_cols();

        Matrix zeros(int n_rows, int n_cols);
        Matrix identity(int n);
        float trace();
        Matrix matrix_transpose();
        Matrix matrix_addition(Matrix other);
        Matrix matrix_subtraction(Matrix other);
        Matrix matrix_negation();
        Matrix matrix_multiplication(Matrix other);
        Matrix matrix_right_multiplication(float scalar);
        Matrix matrix_right_multiplication(Matrix other);

        void matrix_print();

};