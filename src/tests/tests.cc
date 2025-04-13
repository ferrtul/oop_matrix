#include <gtest/gtest.h>

#include "../matrix.h"

TEST(Operation, eqMatrix) {
  Matrix matrix1 = Matrix(3, 3);
  Matrix matrix2 = Matrix(3, 3);
  matrix1.FilingMatrix(48);
  matrix2.FilingMatrix(48);
  ASSERT_TRUE(matrix1.EqMatrix(matrix2));
}
TEST(Operation, eqMatrix2) {
  Matrix matrix1 = Matrix(3, 3);
  Matrix matrix2 = Matrix(3, 3);
  matrix1.FilingMatrix(48.5);
  matrix2.FilingMatrix(48.4);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}
TEST(Operation, eqMatrix3) {
  Matrix matrix1 = Matrix(3, 4);
  Matrix matrix2 = Matrix(3, 3);
  matrix1.FilingMatrix(48.5);
  matrix2.FilingMatrix(48.5);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, eqMatrix4) {
  Matrix matrix1 = Matrix(3, 3);
  Matrix matrix2 = Matrix(3, 3);
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operation, sumMatrix) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sum = Matrix(5, 5);
  matrix1.FilingMatrix(18.4);
  matrix2.FilingMatrix(15.0);
  sum.FilingMatrix(33.4);
  matrix1.SumMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sum));
}

TEST(Operation, sumMatrix2) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sum = Matrix(5, 5);
  matrix1.FilingMatrix(25.7);
  matrix2.FilingMatrix(15.0);
  sum.FilingMatrix(33.4);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sum));
}

TEST(Operation, subMatrix) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sub = Matrix(5, 5);
  matrix1.FilingMatrix(50.67);
  matrix2.FilingMatrix(15.0);
  sub.FilingMatrix(35.67);
  matrix1.SubMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(sub));
}

TEST(Operation, subMatrix2) {
  Matrix matrix1 = Matrix(5, 5);
  Matrix matrix2 = Matrix(5, 5);
  Matrix sub = Matrix(5, 5);
  matrix1.FilingMatrix(50.67);
  matrix2.FilingMatrix(15.0);
  sub.FilingMatrix(11.5);
  matrix1.SubMatrix(matrix2);
  EXPECT_FALSE(matrix1.EqMatrix(sub));
}

TEST(Operation, mulMatrix) {
  Matrix matrix1 = Matrix(5, 4);
  Matrix matrix2 = Matrix(4, 6);
  Matrix mul = Matrix(5, 6);
  matrix1.FilingMatrix(-1);
  matrix2.FilingMatrix(4);
  mul.FilingMatrix(-16);
  matrix1.MulMatrix(matrix2);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, mulNumber) {
  Matrix matrix1 = Matrix(5, 4);
  Matrix mul = Matrix(5, 4);
  matrix1.FilingMatrix(-1);
  mul.FilingMatrix(-16);
  matrix1.MulNumber(16);
  EXPECT_TRUE(matrix1.EqMatrix(mul));
}

TEST(Operation, transpose) {
  Matrix matrix = Matrix(7, 3);
  Matrix res = Matrix(3, 7);
  matrix.FilingMatrix(-1);
  res.FilingMatrix(-1);
  Matrix transpose = matrix.Transpose();
  EXPECT_TRUE(transpose.EqMatrix(res));
}

TEST(Operation, calcComplements) {
  Matrix matrix = Matrix(3, 3);
  Matrix dop = Matrix(3, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 4;
  matrix(1, 0) = 6;
  matrix(1, 1) = 8;
  matrix(1, 2) = 2;
  matrix(2, 0) = 2;
  matrix(2, 1) = 10;
  matrix(2, 2) = 4;

  dop(0, 0) = 12;
  dop(0, 1) = -20;
  dop(0, 2) = 44;
  dop(1, 0) = 32;
  dop(1, 1) = -4;
  dop(1, 2) = -6;
  dop(2, 0) = -28;
  dop(2, 1) = 22;
  dop(2, 2) = -4;
  Matrix res = matrix.CalcComplements();

  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, inverseMatrix) {
  Matrix matrix = Matrix(2, 2);
  Matrix dop = Matrix(2, 2);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  dop(0, 0) = -2;
  dop(0, 1) = 1;
  dop(1, 0) = 1.5;
  dop(1, 1) = -0.5;

  Matrix res = matrix.InverseMatrix();
  EXPECT_TRUE(res.EqMatrix(dop));
}

TEST(Operation, operatorSum) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  matrix1.FilingMatrix(1);
  matrix2.FilingMatrix(0);
  dop.FilingMatrix(1);
  Matrix sum = matrix1 + matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSum2) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  matrix1.FilingMatrix(1);
  matrix2.FilingMatrix(0);
  dop.FilingMatrix(1);
  matrix1 += matrix2;
  EXPECT_TRUE(matrix1.EqMatrix(dop));
}

TEST(Operation, operatorSub) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  matrix1.FilingMatrix(1);
  matrix2.FilingMatrix(0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  Matrix sum = matrix1 - matrix2;
  EXPECT_TRUE(sum == dop);
}

TEST(Operation, operatorSub2) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  Matrix dop(2, 2);
  matrix1.FilingMatrix(1);
  matrix2.FilingMatrix(0);
  dop(0, 0) = 1;
  dop(0, 1) = 1;
  dop(1, 0) = 1;
  dop(1, 1) = 1;
  matrix1 -= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulMatrix) {
  Matrix matrix1(5, 4);
  Matrix matrix2(4, 6);
  Matrix dop(5, 6);
  matrix1.FilingMatrix(-1);
  matrix2.FilingMatrix(4);
  dop.FilingMatrix(-16);
  Matrix mul = matrix1 * matrix2;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulMatrix2) {
  Matrix matrix1(5, 4);
  Matrix matrix2(4, 6);
  Matrix dop(5, 6);
  matrix1.FilingMatrix(-1);
  matrix2.FilingMatrix(4);
  dop.FilingMatrix(-16);
  matrix1 *= matrix2;
  EXPECT_TRUE(matrix1 == dop);
}

TEST(Operation, operatorMulNumber) {
  Matrix matrix(2, 2);
  Matrix dop(2, 2);
  matrix.FilingMatrix(1);
  dop.FilingMatrix(4);
  Matrix mul = matrix * 4;
  EXPECT_TRUE(mul == dop);
}

TEST(Operation, operatorMulNumber2) {
  Matrix matrix(2, 2);
  Matrix dop(2, 2);
  matrix.FilingMatrix(1);
  dop.FilingMatrix(4);
  matrix *= 4;
  EXPECT_TRUE(matrix == dop);
}

TEST(GetAndSet, setSize) {
  Matrix matrix1(3, 6);
  Matrix matrix2(5, 4);
  matrix2.set_rows(3);
  matrix2.set_cols(6);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, setSize2) {
  Matrix matrix1(7, 2);
  Matrix matrix2(5, 4);
  matrix2.set_rows(7);
  matrix2.set_cols(2);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(GetAndSet, getRows) {
  Matrix matrix(4, 7);
  int rows = matrix.get_rows();
  EXPECT_TRUE(rows == 4);
}

TEST(GetAndSet, getCols) {
  Matrix matrix(4, 7);
  int cols = matrix.get_cols();
  EXPECT_TRUE(cols == 7);
}

TEST(Construct, moveMatrix) {
  Matrix matrix(4, 5);
  matrix.FilingMatrix(1);
  Matrix dop(matrix);
  Matrix result(std::move(matrix));
  EXPECT_TRUE(result == dop);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

