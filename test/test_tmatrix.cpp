#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(5);
  // Заполним чем-то, чтобы тест был осмысленным
  m[0][0] = 10;
  m[4][4] = 20;
  
  TDynamicMatrix<int> m1(m);
  ASSERT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 10;
  
  TDynamicMatrix<int> m1(m);
  m1[0][0] = 99; // Меняем копию
  
  // Если память своя, то у оригинала останется 10
  ASSERT_EQ(m[0][0], 10);
  ASSERT_EQ(m1[0][0], 99);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(5);
  ASSERT_EQ(m.size(), 5); 
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 42;
  ASSERT_EQ(m[1][2], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m[-1][0] = 5); // operator[] должен бросать out_of_range
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m[5][0] = 5); // Индекс >= sz должен бросать ошибку
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 7;
  ASSERT_NO_THROW(m = m);
  ASSERT_EQ(m[0][0], 7);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(5), m2(5);
  m1[0][0] = 1;
  m2[0][0] = 2;
  
  m1 = m2;
  ASSERT_EQ(m1[0][0], 2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  m1 = m2;
  ASSERT_EQ(m1.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  m2[4][4] = 99;
  
  m1 = m2;
  ASSERT_EQ(m1.size(), 5);
  ASSERT_EQ(m1[4][4], 99);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3), m2(3);
  m1[1][1] = 5;
  m2[1][1] = 5;
  
  ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(3);
  ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3), m2(5);
  ASSERT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), res(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  
  m2[0][0] = 10; m2[0][1] = 20;
  m2[1][0] = 30; m2[1][1] = 40;
  
  res = m1 + m2;
  ASSERT_EQ(res[0][0], 11);
  ASSERT_EQ(res[0][1], 22);
  ASSERT_EQ(res[1][0], 33);
  ASSERT_EQ(res[1][1], 44);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);

  ASSERT_ANY_THROW(m1 + m2); 
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), res(2);
  m1[0][0] = 10; m1[0][1] = 20;
  
  m2[0][0] = 1; m2[0][1] = 2;
  
  res = m1 - m2;
  ASSERT_EQ(res[0][0], 9);
  ASSERT_EQ(res[0][1], 18);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 - m2); 
}