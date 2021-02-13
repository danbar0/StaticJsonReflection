#include "pch.h"
#include "../StaticJsonReflectionProj/GetClass.hpp"
#include "../StaticJsonReflectionProj/ObjectSerialization.hpp"

struct TestStruct {
	uint32_t field3;
	uint16_t field2;
	uint8_t field1;
};

BEGIN_ATTRIBUTES_FOR(TestStruct)
DEFINE_MEMBER(field3);
DEFINE_MEMBER(field2);
DEFINE_MEMBER(field1);
END_ATTRIBUTES

TEST(TestCaseName, TestName) {
	TestStruct test { 1, 2, 3 };
	auto result = SerializeObject(test); 
	EXPECT_EQ(result, "");
}