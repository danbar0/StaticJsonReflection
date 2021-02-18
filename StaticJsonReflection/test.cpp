#include "pch.h"
#include "../StaticJsonReflectionProj/GetClass.hpp"
#include "../StaticJsonReflectionProj/ObjectSerialization.hpp"

struct TestStruct {
	int32_t field3;
	int16_t field2;
	int8_t field1;
};

BEGIN_ATTRIBUTES_FOR(TestStruct)
DEFINE_MEMBER(field3);
DEFINE_MEMBER(field2);
DEFINE_MEMBER(field1);
END_ATTRIBUTES

TEST(TestCaseName, TestName) {
	TestStruct test { 1, 2, 3 };

	auto result = SerializeObject(test); 

	EXPECT_EQ(result, "{\"field3\":1,\"field2\":2,\"field1\":3}");
}