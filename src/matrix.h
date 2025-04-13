#ifndef CPP_MATRIXPLUS_MATRIX_H
#define CPP_MATRIXPLUS_MATRIX_H

#include <cmath>
#include <iostream>
#define EPS 1e-7

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);
  ~Matrix();

  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  // operators
  bool operator==(const Matrix &other);
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(double num);
  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(double num);
  Matrix operator=(const Matrix &other);
  double &operator()(int i, int j);

  // helpers
  void PrintMatrix() const;
  void FilingMatrix(double num);
  void SwapRows(int row_num, int &swap_value);
  void RedactWitchTriangle(int &swap_value);
  double CalcDeterminant(int swap_value);
  double CalcComplement(int row, int column);

  // setters & getters
  int get_rows();
  void set_rows(int new_row);
  int get_cols();
  void set_cols(int new_cols);

 private:
  // Attributes
  int rows_ = 0;
  int cols_ = 0;
  double **matrix_ = nullptr;
};
#endif  // CPP_MATRIXPLUS_MATRIX_H