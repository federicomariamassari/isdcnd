#include <vector>

typedef std::vector< std::vector<float> > t_grid;

class Matrix
{
    private:
        t_grid grid;
        std::vector<float>::size_type rows;
        std::vector<float>::size_type cols;
        
        float dot_product(std::vector<float> p, std::vector<float> q);

    public:
        Matrix();
        Matrix(t_grid G);

        void set_grid(t_grid G);
        t_grid get_grid();
        std::vector<float>::size_type get_rows();
        std::vector<float>::size_type get_cols();

        Matrix matrix_transpose();
        Matrix matrix_addition(Matrix other);
        Matrix matrix_subtraction(Matrix other);
        Matrix matrix_negation();
        Matrix matrix_multiplication(Matrix other);

        void matrix_print();

};