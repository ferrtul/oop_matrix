# Oop Matrix+

Implementation of the ### An example of a matrix class in C++
```cpp
class Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        Matrix();              // Default constructor
        ~Matrix();             // Destructor

        void SumMatrix(const Matrix& other); 
        // Other methods..
}
```

### A reminder of the matrix basics

Matrix is a rectangular table of numbers arranged in m rows and n columns:

```
    1 2 3
A = 4 5 6
    7 8 9
```

```
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

You can get the desired element using indices as follows A[1,1] = 1, where the first index is the row number, the second is the column number.

The order of a matrix is the number of its rows or columns. \
The main diagonal of a square matrix is the diagonal from the upper left to the lower right corner. \

A rectangular matrix (B) is a matrix with the number of rows not equal to the number of columns. \
A square matrix (A) is a matrix with the number of rows equal to the number of columns.

## Matrix operations

Below is a brief description of the matrix operations that need to be implemented in the development library.
They are similar to the operations you performed earlier in "Structured Programming", so you can see a more detailed description of them there.
Note that some operations have exceptional situations that require special handling using the exception mechanism.

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const Matrix& other)` | Checks matrices for equality with each other. |  |
| `void SumMatrix(const Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions. |
| `void SubMatrix(const Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions. |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number. |  |
| `void MulMatrix(const Matrix& other)` | Multiplies the current matrix by the second matrix. | The number of columns of the first matrix is not equal to the number of rows of the second matrix. |
| `Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it. |  |
| `Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it. | The matrix is not square. |
| `double Determinant()` | Calculates and returns the determinant of the current matrix. | The matrix is not square. |
| `Matrix InverseMatrix()` | Calculates and returns the inverse matrix. | Matrix determinant is 0. |

Apart from those operations, you also need to implement constructors and destructors:

| Method | Description |
| ---------- | ----------- |
| `Matrix()` | A basic constructor that initialises a matrix of some predefined dimension. |  
| `Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns. |
| `Matrix(const Matrix& other)` | Copy constructor. |
| `Matrix(Matrix&& other)` | Move constructor. |
| `~Matrix()` | Destructor. |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices. | Different matrix dimensions. |
| `-`   | Subtraction of one matrix from another. | Different matrix dimensions. |
| `*`  | Matrix multiplication and matrix multiplication by a number. | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `==`  | Checks for matrices equality (`EqMatrix`). | |
| `=`  | Assignment of values from one matrix to another one. | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions. |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions. |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`). | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `(int i, int j)`  | Indexation by matrix elements (row, column). | Index is outside the matrix. |


