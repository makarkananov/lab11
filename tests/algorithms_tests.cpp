#include <gtest/gtest.h>
#include <numeric>
#include <list>
#include "lib/algorithms.h"

TEST(AllOfTest, Basic) {
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {2, 4, 6, 8, 10};
  auto is_even = [](int n) { return n % 2 == 0; };
  auto is_greater_than_zero = [](int n) { return n > 0; };

  EXPECT_FALSE(algos::all_of(vec1.begin(), vec1.end(), is_even));
  EXPECT_TRUE(algos::all_of(vec2.begin(), vec2.end(), is_even));
  EXPECT_TRUE(algos::all_of(vec1.begin(), vec1.end(), is_greater_than_zero));
  EXPECT_TRUE(algos::all_of(vec2.begin(), vec2.end(), is_greater_than_zero));
}

TEST(AnyOfTest, Basic) {
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {-2, -4, -6, -8, -10};
  auto is_even = [](int n) { return n % 2 == 0; };
  auto is_greater_than_zero = [](int n) { return n > 0; };

  EXPECT_TRUE(algos::any_of(vec1.begin(), vec1.end(), is_even));
  EXPECT_TRUE(algos::any_of(vec2.begin(), vec2.end(), is_even));
  EXPECT_TRUE(algos::any_of(vec1.begin(), vec1.end(), is_greater_than_zero));
  EXPECT_FALSE(algos::any_of(vec2.begin(), vec2.end(), is_greater_than_zero));
}

TEST(NoneOfTest, Basic) {
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {-2, -4, -6, -8, -10};
  auto is_even = [](int n) { return n % 2 == 0; };
  auto is_greater_than_zero = [](int n) { return n > 0; };

  EXPECT_TRUE(algos::none_of(vec1.begin(), vec1.end(), is_even));
  EXPECT_FALSE(algos::none_of(vec2.begin(), vec2.end(), is_even));
  EXPECT_FALSE(algos::none_of(vec1.begin(), vec1.end(), is_greater_than_zero));
  EXPECT_TRUE(algos::none_of(vec2.begin(), vec2.end(), is_greater_than_zero));
}

TEST(OneOfTest, Basic) {
  std::vector<int> vec1 = {-2, -3, 5};
  std::vector<int> vec2 = {-2, -4, -6, -8, -10};
  auto is_even = [](int n) { return n % 2 == 0; };
  auto is_greater_than_zero = [](int n) { return n > 0; };

  EXPECT_TRUE(algos::one_of(vec1.begin(), vec1.end(), is_even));
  EXPECT_FALSE(algos::one_of(vec2.begin(), vec2.end(), is_even));
  EXPECT_TRUE(algos::one_of(vec1.begin(), vec1.end(), is_greater_than_zero));
  EXPECT_FALSE(algos::one_of(vec2.begin(), vec2.end(), is_greater_than_zero));
}

TEST(IsSortedTest, Basic) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {5, 4, 3, 2, 1};

  EXPECT_TRUE(algos::is_sorted(v1.begin(), v1.end()));
  EXPECT_FALSE(algos::is_sorted(v2.begin(), v2.end()));
}

TEST(IsSortedTest, BasicWithComparator) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {5, 4, 3, 2, 1};

  auto greater_than = [](int a, int b) { return a > b; };

  EXPECT_FALSE(algos::is_sorted(v1.begin(), v1.end(), greater_than));
  EXPECT_TRUE(algos::is_sorted(v2.begin(), v2.end(), greater_than));
}

TEST(IsPartitionedTest, Basic) {
  std::vector<int> v1 = {1, 2, 3, -4, -5};
  std::vector<int> v2 = {-1, 4, 3, 2, -1};

  auto is_greater_than_zero = [](int n) { return n > 0; };

  EXPECT_TRUE(algos::is_partitioned(v1.begin(), v1.end(), is_greater_than_zero));
  EXPECT_FALSE(algos::is_partitioned(v2.begin(), v2.end(), is_greater_than_zero));
}

TEST(FindNotTest, Basic) {
  std::vector<int> v1 = {1, 1, 1, 2, 3};
  std::vector<int> v2 = {2, 1, 3, 4, 5};

  EXPECT_EQ(*algos::find_not(v1.begin(), v1.end(), 1), 2);
  EXPECT_EQ(*algos::find_not(v2.begin(), v2.end(), 1), 2);
}

TEST(FindBackwardTest, Basic) {
  std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 2, 2, 2};

  EXPECT_EQ(*algos::find_backward(v1.begin(), v1.end()-1, 5), 5);
  EXPECT_EQ(*algos::find_backward(v2.begin(), v2.end()-1, 1), 1);
}

TEST(IsPalindromeTest, Basic) {
  std::vector<int> v1 = {1, 2, 2, 1};
  std::vector<int> v2 = {1, 2, 2, 1, 2};

  auto both_even_or_odd = [](int a, int b) { return (a % 2) == (b % 2); };
  EXPECT_TRUE(algos::is_palindrome(v1.begin(), v1.end()-1, both_even_or_odd));
  EXPECT_FALSE(algos::is_palindrome(v2.begin(), v2.end()-1, both_even_or_odd));
}


TEST(XRangeTest, Basic) {
  auto r = algos::xrange(5);
  std::vector<int> expected {0, 1, 2, 3, 4};
  EXPECT_EQ(std::vector<int>(r.begin(), r.end()), expected);
}

TEST(XRangeTest, Float) {
  auto r = algos::xrange(5.0, 7.0, 0.5);
  std::vector<double> expected {5.0, 5.5, 6.0, 6.5};
  EXPECT_EQ(std::vector<double>(r.begin(), r.end()), expected);
}

TEST(XRangeTest, NegativeStep) {
  auto r = algos::xrange(10, 0, -2);
  std::vector<int> expected {10, 8, 6, 4, 2};
  EXPECT_EQ(std::vector<int>(r.begin(), r.end()), expected);
}

TEST(ZipTest, Basic) {
  std::vector<int> v1 {1, 2, 3};
  std::vector<int> v2 {4, 5, 6};
  auto z = algos::zip(v1, v2);
  std::vector<std::pair<int, int>> expected {{1, 4}, {2, 5}, {3, 6}};
  EXPECT_EQ((*z.begin()).first, expected[0].first);
  EXPECT_EQ((*(++z.begin())).second, expected[1].second);
}

TEST(ZipTest, DifferentTypes) {
  std::vector<int> v1 {1, 2, 3};
  std::list<int> v2 {4, 5, 6};
  auto z = algos::zip(v1, v2);
  std::vector<std::pair<int, int>> expected {{1, 4}, {2, 5}, {3, 6}};
  EXPECT_EQ((*z.begin()).first, expected[0].first);
  EXPECT_EQ((*(++z.begin())).second, expected[1].second);
}

TEST(ZipTest, UnequalLength) {
  std::vector<int> v1 {1, 2, 3};
  std::vector<int> v2 {4, 5};
  auto z = algos::zip(v1, v2);
  std::vector<std::pair<int, int>> expected {{1, 4}, {2, 5}};
  EXPECT_EQ((*(++z.begin())).first, expected[1].first);
}