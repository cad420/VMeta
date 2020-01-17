
#include <gtest/gtest.h>
#include <VMeta/operation.hpp>
TEST(test_operation,Sum)
{
	using namespace vm;
	constexpr int sum = Sum<1, 2, 3, 4, 5>;
	EXPECT_EQ(15, sum);
}
TEST(test_operation, CountOnes)
{
	using namespace vm;
	constexpr int ones = CountOnes<14>;
	EXPECT_EQ(3, ones);
}
TEST(test_operation, Add)
{
	using namespace vm;
	constexpr int add = Add<14,15>;
	EXPECT_EQ(29, add);
}

TEST(test_operation,FindFirstIndexOf)
{
	using namespace vm;
	constexpr auto idx = FindFirstIndexOf<double, char, int, double, int>;
	EXPECT_EQ(2, idx);
}

TEST(test_operation,GetTypeOf)
{
	using namespace vm;

	using ty = GetTypeOf<3, char, unsigned, double, float, char, int>;
	constexpr bool True = std::is_same<ty,float>::value;

	std::cout << typeid(ty).name() << std::endl;
	
	EXPECT_TRUE(True);
}

