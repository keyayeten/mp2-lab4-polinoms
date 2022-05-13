#include"gtest.h"
#include<algorithm>
#include"../Polinoms/Polinom.h"

TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom m);
}


TEST(Monom, can_compare_the_monoms)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1 == m2);
	ASSERT_NO_THROW(m1 < m2);
	ASSERT_NO_THROW(m1 > m2);
}

TEST(Monom, monoms_are_compared_correctly)
{
	TMonom m1(1, 1, 3.0), m2(1, 2, 3.0);
	EXPECT_EQ(true, m1 < m2);
	EXPECT_EQ(true, m2 > m1);
	m1.y = 2;
	EXPECT_EQ(true, m1 == m2);
}

TEST(Monom, monom_can_be_assigned_to)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1 = m2);
}


TEST(Monom, monoms_can_be_multiplied_by_each_other)
{
	TMonom m1, m2;
	ASSERT_NO_THROW(m1 = m1 * m2);
}

TEST(Monom, monoms_multiplying_by_each_other_is_done_correctly)
{
	TMonom m1(1, 2, 3, 4.0), m2(4, 3, 2, 1.0);
	m1 = m1 * m2;
	int error = 0;
	if (m1.x != 5 || m1.y != 5 || m1.z != 5 || m1.coeff != 4.0)
		error++;
	EXPECT_EQ(0, error);
}

TEST(Monom, monoms_can_be_multiplied_by_a_number)
{
	TMonom m;
	ASSERT_NO_THROW(m = m * 5.0);
}

TEST(Monom, monoms_multiplying_by_a_number_is_done_correctly)
{
	TMonom m(1, 2, 3, 4.0);
	m = m * 5.0;
	int error = 0;
	if (m.x != 1 || m.y != 2 || m.z != 3 || m.coeff != 20.0)
		error++;
	EXPECT_EQ(0, error);
}

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(TList<int> l);
}

TEST(List, can_copy_empty_list)
{
	TList<int> l;
	ASSERT_NO_THROW(TList<int> copy(l));
}

TEST(List, can_add_an_elem_to_the_top_of_the_empty_list)
{
	TList<int> l;
	ASSERT_NO_THROW(l.InsFirst(3));
}

TEST(List, can_add_an_elem_to_the_top_of_the_no_empty_list)
{
	TList<int> l;
	l.InsFirst(3);
	ASSERT_NO_THROW(l.InsFirst(3));
}

TEST(List, adding_an_elem_to_the_top_of_the_list_size_by_one)
{
	TList<int> l;
	l.InsFirst(3);
	int size = l.Get_Size();
	l.InsFirst(3);
	EXPECT_EQ(size + 1, l.Get_Size());
}

TEST(List, can_add_an_elem_to_the_end_of_the_empty_list)
{
	TList<int> l;
	ASSERT_NO_THROW(l.InsLast(5));
}

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(TPolinom p);
}

TEST(Polinom, can_copy_empty_polinom)
{
	TPolinom l;
	ASSERT_NO_THROW(TPolinom p(l));
}

TEST(Polinom, adding_such_a_monomial_does_not_change_the_size_of_the_polynomial)
{
	TPolinom p;
	TMonom m1(1, 2, 3, 4.0), m2(1, 2, 3, 2.0);
	p.InsMonom(m1);
	int size = p.Get_Size();
	p.InsMonom(m2);
	EXPECT_EQ(size, p.Get_Size());
}

TEST(Polinom, can_compare_empty_polinom)
{
	TPolinom p1, p2, p3;
	ASSERT_NO_THROW(p1 = p2 = p3);
}

TEST(Polinom, can_compare_no_empty_polinom_the_same_sizes)
{
	TPolinom p1, p2, p3;
	TMonom m;
	p1.InsMonom(m);
	m.x = 5;
	p2.InsMonom(m);
	m.y = 5;
	p3.InsMonom(m);
	ASSERT_NO_THROW(p1 = p2 = p3);
}

TEST(Polinom, can_compare_no_empty_polinom_the_different_sizes_)
{
	TPolinom p1, p2;
	TMonom m1, m2(1, 2, 3, 4.0);
	p2.InsMonom(m1);
	p2.InsMonom(m2);
	ASSERT_NO_THROW(p1 = p2);
	TMonom m3(2, 4, 6, 1.0), m4(0, 9, 0, 5.0);
	TPolinom p3;
	p3.InsMonom(m3);
	p2.InsMonom(m4);
	ASSERT_NO_THROW(p2 = p3);
}

TEST(Polinom, can_multiply_an_empty_polinom_by_a_number)
{
	TPolinom p, res;
	ASSERT_NO_THROW(res = p * 5);
}

TEST(Polinom, can_multiply_a_no_empty_polinom_by_a_number)
{
	TPolinom p, res;
	TMonom m;
	p.InsMonom(m);
	ASSERT_NO_THROW(res = p * 5);
}

TEST(Polinom, multiplying_a_polynomial_by_zero_makes_the_polynomial_empty)
{
	TPolinom p, res;
	TMonom m;
	p.InsMonom(m);
	res.InsMonom(m);
	res = p * 0;
	EXPECT_EQ(0, res.Get_Size());
}
TEST(Polinom, can_multiply_an_empty_polinom_by_a_monom)
{
	TPolinom p, res;
	TMonom m;
	ASSERT_NO_THROW(res = p * m);
}

TEST(Polinom, can_multiply_a_no_empty_polinom_by_a_monom)
{
	TPolinom p, res;
	TMonom m, m1(1, 0, 2, 4.0);
	p.InsMonom(m);
	ASSERT_NO_THROW(res = p * m1);
}

TEST(Polinom, multiplying_a_polynomial_by_a_monomial_with_a_nonzero_coefficient_does_not_change_the_size_of_the_polynomial)
{
	TPolinom p, res;
	TMonom m;
	p.InsMonom(m);
	TMonom m1(4, 3, 2, 1.0);
	int size = p.Get_Size();
	res = p * m1;
	EXPECT_EQ(size, res.Get_Size());
}
TEST(Polinom, multiplying_a_polynomial_by_a_monomial_with_a_zero_coefficient_makes_the_polynomial_empty)
{
	TPolinom p, res;
	TMonom m;
	p.InsMonom(m);
	res.InsMonom(m);
	TMonom m1(4, 3, 2, 0.0);
	res = p * m1;
	EXPECT_EQ(0, res.Get_Size());
}

TEST(Polinom, can_add_up_an_empty_polinom_by_a_empty_polinom)
{
	TPolinom p1, p2, res;
	ASSERT_NO_THROW(res = p1 + p2);
	ASSERT_NO_THROW(p1 += p2);
}

TEST(Polinom, can_add_up_a_no_empty_polinom_by_a_empty_polinom)
{
	TPolinom p1, p2, res;
	TMonom m;
	p1.InsMonom(m);
	ASSERT_NO_THROW(res = p1 + p2);
	ASSERT_NO_THROW(p1 += p2);
}

TEST(Polinom, can_add_up_an_emty_polinom_by_a_no_empty_polinom)
{
	TPolinom p1, p2, res;
	TMonom m;
	p2.InsMonom(m);
	ASSERT_NO_THROW(res = p1 + p2);
	ASSERT_NO_THROW(p1 += p2);
}

TEST(Polinom, can_add_up_a_no_empty_polinom_by_a_no_empty_polinom)
{
	TPolinom p1, p2, res;
	TMonom m1, m2(1, 2, 3, 4.0);
	p1.InsMonom(m1);
	p2.InsMonom(m2);
	ASSERT_NO_THROW(res = p1 + p2);
	ASSERT_NO_THROW(p1 += p2);
}

TEST(Polinom, the_amount_of_polynomials_without_such_monomials_is_equal_to_the_sum_of_the_sizes_of_terms_of_the_polynomial)
{
	TPolinom p1, p2, res;
	TMonom m1, m2(1, 2, 3, 4.0), m3(1, 3, 4, 2.0);
	p1.InsMonom(m1);
	p2.InsMonom(m2);
	p2.InsMonom(m3);
	int size1 = p1.Get_Size(), size2 = p2.Get_Size();
	res = p1 + p2;
	EXPECT_EQ(res.Get_Size(), size1 + size2);
	p1 += p2;
	EXPECT_EQ(p1.Get_Size(), size1 + size2);
}

TEST(Polinom, when_adding_polynomials_the_coefficients_of_such_monons_are_added_togetherand_one_monom_with_a_different_coefficient_is_obtained)
{
	TPolinom p1, p2, res;
	TMonom m1, m2(1, 2, 3, 4.0), m3(1, 2, 3, 3.0);
	p1.InsMonom(m1);
	p1.InsMonom(m2);
	p2.InsMonom(m3);
	res = p1 + p2;
	EXPECT_EQ(res.Get_Size(), 2);
	p1 += p2;
	EXPECT_EQ(p1.Get_Size(), 2);
}

TEST(Polinom, when_adding_polynomials_similar_monoms_with_opposite_coefficients_are_removed)
{
	TPolinom p1, p2, res;
	TMonom m1, m2(1, 2, 3, 4.0), m3(1, 2, 3, -4.0);
	p1.InsMonom(m1);
	p1.InsMonom(m2);
	p2.InsMonom(m3);
	res = p1 + p2;
	EXPECT_EQ(res.Get_Size(), 1);
	p1 += p2;
	EXPECT_EQ(p1.Get_Size(), 1);
}