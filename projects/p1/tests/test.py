from matrix import Matrix
import pytest


@pytest.fixture
def A():
    yield Matrix([
        [1, 2],
        [3, 4]
    ])


@pytest.fixture
def B():
    yield Matrix([
        [5, 6],
        [7, 8]
    ])


@pytest.fixture
def C():
    yield Matrix([
        [1, -2, -3],
        [-4, -5, -6],
        [7, 8, 9]
    ])


@pytest.fixture
def D():
    yield Matrix([
        [1, 2, 3],
        [4, 5, 6]
    ])


@pytest.fixture
def E():
    yield Matrix([
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ])


@pytest.fixture
def F():
    yield Matrix([
        [1, 2, 3, 4],
        [5, 6, 7, 8],
        [9, 10, 11, 12],
        [13, 14, 15, 16]
    ])


def test_matrix_addition(A, B):

    expected = Matrix([
        [6, 8],
        [10, 12]
    ])
    actual = A + B

    assert equal(actual, expected)


def test_matrix_subtraction(A, B):

    expected = Matrix([
        [-4, -4],
        [-4, -4]
    ])
    actual = A - B

    assert equal(actual, expected)


def test_matrix_negative(A):

    expected = Matrix([
        [-1, -2],
        [-3, -4]
    ])
    actual = -A

    assert equal(actual, expected)


def test_matrix_transpose(A):

    expected = Matrix([
        [1, 3],
        [2, 4]
    ])
    actual = A.T()

    assert equal(actual, expected)


def test_trace_on_non_square_matrix_raises_value_error(D):
    with pytest.raises(ValueError):
        D.trace()


def test_trace(A):
    expected = 5
    actual = A.trace()

    assert expected == actual


def test_determinant_on_non_square_matrix_raises_value_error(D):
    with pytest.raises(ValueError):
        D.determinant()


def test_determinant_on_matrices_larger_than_3x3_raises_not_implemented_error(F):
    with pytest.raises(NotImplementedError):
        F.determinant()


def test_determinant_1x1():
    expected = 1
    actual = Matrix([[1, ]]).determinant()

    assert expected == actual


def test_determinant_2x2(A):
    expected = -2
    actual = A.determinant()

    assert expected == actual


def test_determinant_3x3(C):
    expected = 6
    actual = C.determinant()

    assert expected == actual


def test_matrix_inverse_on_singular_matrix_raises_value_error(E):
    with pytest.raises(ValueError):
        E.inverse()


def test_matrix_inverse_2x2(A):
    expected = Matrix([
        [-2., 1.],
        [1.5, -0.5]
    ])
    actual = A.inverse()

    assert equal(actual, expected)


def test_matrix_inverse_3x3(C):
    expected = Matrix([
        [0.5, -1., -0.5],
        [-1., 5., 3.],
        [0.5, -3.66667, -2.16667]
    ])
    actual = C.inverse()

    assert equal(actual, expected)


def equal(m1, m2):

    if len(m1.g) != len(m2.g):
        return False

    if len(m1.g[0]) != len(m2.g[0]):
        return False

    for r1, r2 in zip(m1.g, m2.g):
        for v1, v2 in zip(r1, r2):

            if abs(v1 - v2) > 0.0001:
                return False

    return True


if __name__ == '__main__':
    pytest.main()
