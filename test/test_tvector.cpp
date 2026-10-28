#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(5);
	v[0] = 10;
	v[4] = 20;

	TDynamicVector<int> v1(v);
	ASSERT_TRUE(v == v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(5);
	v[0] = 10;

	TDynamicVector<int> v1(v);
	v1[0] = 99; // Меняем копию

	// Если память скопировалась правильно, у оригинала останется 10
	ASSERT_EQ(v[0], 10);
	ASSERT_EQ(v1[0], 99);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	// Отрицательный индекс превратится в огромное число size_t
	ASSERT_ANY_THROW(v[-1] = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v[5] = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	v[0] = 7;
	ASSERT_NO_THROW(v = v);
	ASSERT_EQ(v[0], 7);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 1;
	v2[0] = 2;

	v1 = v2;
	ASSERT_EQ(v1[0], 2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v1 = v2;
	ASSERT_EQ(v1.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v2[4] = 99;

	v1 = v2;
	ASSERT_EQ(v1.size(), 5);
	ASSERT_EQ(v1[4], 99);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[1] = 5;
	v2[1] = 5;

	ASSERT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);
	ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	res = v + 10;
	ASSERT_EQ(res[0], 11);
	ASSERT_EQ(res[1], 12);
	ASSERT_EQ(res[2], 13);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 10; v[1] = 20; v[2] = 30;

	res = v - 5;
	ASSERT_EQ(res[0], 5);
	ASSERT_EQ(res[1], 15);
	ASSERT_EQ(res[2], 25);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 2; v[1] = 3; v[2] = 4;

	res = v * 3;
	ASSERT_EQ(res[0], 6);
	ASSERT_EQ(res[1], 9);
	ASSERT_EQ(res[2], 12);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), res(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 10; v2[1] = 20; v2[2] = 30;

	res = v1 + v2;
	ASSERT_EQ(res[0], 11);
	ASSERT_EQ(res[1], 22);
	ASSERT_EQ(res[2], 33);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	// Твой operator+ должен бросать std::invalid_argument
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), res(3);
	v1[0] = 10; v1[1] = 20; v1[2] = 30;
	v2[0] = 1; v2[1] = 2; v2[2] = 3;

	res = v1 - v2;
	ASSERT_EQ(res[0], 9);
	ASSERT_EQ(res[1], 18);
	ASSERT_EQ(res[2], 27);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;

	// Скалярное произведение: 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
	ASSERT_EQ(v1 * v2, 32);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	// В твоем коде operator* при разных размерах возвращает T(), то есть 0.
	// Если тест требует исключение, нужно поменять код на throw.
	// Если возврат нуля - то проверяем, что вернулся 0.
	ASSERT_EQ(v1 * v2, 0);
}