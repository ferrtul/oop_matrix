#include "matrix.h"

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) {
  if (!(rows > 0 && cols > 0)) {
    throw std::runtime_error("create_error");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

Matrix::Matrix(Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::Matrix(const Matrix &other) {
  //  : rows_(other.rows_), cols_(other.cols_)
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int Matrix::get_rows() { return rows_; }

void Matrix::set_rows(int new_row) {
  if (new_row < 0) {
    throw std::invalid_argument("Invalid argument: row>0");
  }

  Matrix new_matrix(new_row, cols_);
  for (int i = 0; i < std::min(new_row, rows_); ++i) {
    for (int j = 0; j < cols_; ++j) {
      new_matrix(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(new_matrix);
}

int Matrix::get_cols() { return cols_; }

void Matrix::set_cols(int new_cols) {
  if (new_cols < 0) {
    throw std::invalid_argument("Invalid argument: row>0");
  }
  Matrix new_matrix(rows_, new_cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < std::min(new_cols, cols_); ++j) {
      new_matrix(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(new_matrix);
}

bool Matrix::EqMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  bool eq_val = false;
  for (int i = 0; i < rows_ && !eq_val; i++) {
    for (int j = 0; j < cols_ && !eq_val; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        return false;
      }
    }
  }
  return true;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }

  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.rows_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

Matrix Matrix::Transpose() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Invalid argument: row>0");
  }
  Matrix transpose_matrix(cols_, rows_);
  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      transpose_matrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transpose_matrix;
}

double Matrix::Determinant() {
  double determinant_value = 0;
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }
  int swap_value = 0;
  Matrix rewrited_matrix = Matrix(*this);
  rewrited_matrix.RedactWitchTriangle(swap_value);
  determinant_value = rewrited_matrix.CalcDeterminant(swap_value);

  return determinant_value;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("The matrix is not square.");
  }
  Matrix complements_matrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      complements_matrix.matrix_[i][j] =
          this->CalcComplement(i, j) * pow(-1, (i + j));
    }
  }
  *this = std::move(complements_matrix);
  return *this;
}

Matrix Matrix::InverseMatrix() {
  Matrix matrix_copy(*this);
  double determinant_value = matrix_copy.Determinant();
  if (determinant_value == 0) {
    throw std::invalid_argument("Matrix determinant is 0.");
  }
  Matrix complements_matrix = matrix_copy.CalcComplements();
  Matrix transpose_matrix = complements_matrix.Transpose();

  transpose_matrix.MulNumber(1 / determinant_value);

  *this = std::move(transpose_matrix);
  return *this;
}

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *(this);
}
Matrix &Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *(this);
}
Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *(this);
}
Matrix &Matrix::operator*=(const double num) {
  MulNumber(num);
  return *(this);
}
Matrix Matrix::operator+(const Matrix &other) {
  Matrix result(rows_, cols_);
  SumMatrix(other);
  result = std::move(*this);
  return result;
}
Matrix Matrix::operator-(const Matrix &other) {
  Matrix result(rows_, cols_);
  SubMatrix(other);
  result = std::move(*this);
  return result;
}
Matrix Matrix::operator*(const Matrix &other) {
  Matrix result(rows_, cols_);
  MulMatrix(other);
  result = std::move(*this);
  return result;
}
Matrix Matrix::operator*(const double num) {
  Matrix result(rows_, cols_);
  MulNumber(num);
  result = std::move(*this);
  return result;
}
Matrix Matrix::operator=(const Matrix &other) {
  if (this != &other) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}
double &Matrix::operator()(int i, int j) {
  if (i >= 0 && j >= 0 && i < rows_ && j < cols_) {
    return matrix_[i][j];
  } else {
    throw std::invalid_argument("Index is outside the matrix.");
  }
}

// helpers
double Matrix::CalcComplement(int row, int column) {
  int minor_row = 0, minor_column = 0;
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("different matrix dimensions.");
  }
  Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i != row && j != column) {
        minor.matrix_[minor_row][minor_column] = this->matrix_[i][j];
        minor_column++;
        if (minor_column == minor.cols_) {
          minor_column = 0;
          minor_row++;
        }
      }
    }
  }
  double complement = minor.Determinant();
  return complement;
}

void Matrix::SwapRows(int row_num, int &swap_value) {
  double temp_value = 0;
  int in_swap_row_num = 0, stop = 0;

  for (int i = row_num; i < rows_ || stop == 0; ++i) {
    if (stop != 1 && matrix_[i][row_num] == 0) {
      in_swap_row_num = i;
      stop = 1;
    }
  }
  for (int i = 0; i < cols_; i++) {
    temp_value = matrix_[row_num][i];
    matrix_[row_num][i] = matrix_[in_swap_row_num][i];
    matrix_[in_swap_row_num][i] = temp_value;
  }
  swap_value++;
}

void Matrix::RedactWitchTriangle(int &swap_value) {
  double koeff = 0;
  for (int k = 0, n = 0; k < rows_ - 1 && n < cols_; k++, n++) {
    if (matrix_[k][n] == 0) {
      SwapRows(k, swap_value);
    }
    for (int i = k + 1; i < rows_; i++) {
      koeff = matrix_[i][k] / matrix_[k][k];
      for (int j = k; j < cols_; j++) {
        matrix_[i][j] -= koeff * matrix_[k][j];
      }
    }
  }
}

double Matrix::CalcDeterminant(int swap_value) {
  double determinant_value = 1;
  for (int i = 0, j = 0; i < rows_ && j < cols_; i++, j++) {
    determinant_value *= matrix_[i][j];
  }
  determinant_value = pow(-1, swap_value) * determinant_value;
  if (determinant_value == -0) determinant_value = 0;
  return determinant_value;
}

void Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "_______________"
            << "\n";
}

void Matrix::FilingMatrix(double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = num;
    }
  }
}
