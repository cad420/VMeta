#include <gtest/gtest.h>
#include <VMeta/staticdict.hpp>


using namespace std;

TEST(test_staticdict,common)
{
	using namespace vm;

	using Params = StaticDict<struct pos, struct size, struct type,struct mytype>;


	std::string v = "int";

	struct MyType
	{
		int v = 4;
	}my;

	auto p = Params::Create().Set<pos>(1).Set<size>(12.34).Set<type>("int").Set<mytype>(my);

	EXPECT_EQ(p.Get<pos>(), 1);
	EXPECT_EQ(p.Get<size>(),12.34);
	EXPECT_EQ(p.Get<type>(),"int");
	EXPECT_EQ(p.Get<mytype>().v,4);
	
}
