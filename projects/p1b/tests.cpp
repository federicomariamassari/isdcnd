#include <iostream>
#include <vector>
#include <cassert>
#include "matrix.h"

using namespace std;

int main()
{
    Matrix A = Matrix({{1, 2}, {3, 4}});
    Matrix B = Matrix({{1, 2}, {3, 4}});

    assert(A.is_identical(B));

    return 0;
}