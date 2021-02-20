#include "pch.h"
#include "../StaticJsonReflectionProj/GetClass.hpp"
#include "../StaticJsonReflectionProj/ObjectSerializationDef.hpp"

struct TestStruct {
	int32_t field1;
	int16_t field2;
	int8_t field3;
};

BEGIN_ATTRIBUTES_FOR(TestStruct)
DEFINE_MEMBER(field1);
DEFINE_MEMBER(field2);
DEFINE_MEMBER(field3);
END_ATTRIBUTES

TEST(SerializationTest, SerializeTest) {
	TestStruct test { 1, 2, 3 };

	auto result = SerializeObject(test); 

	EXPECT_EQ(result, "{\"field1\":1,\"field2\":2,\"field3\":3}");
}

TEST(SerializationTest, DeserializeTest) {
		std::string testJsonData = "{\"field1\":1,\"field2\":2,\"field3\":3}"; 

		TestStruct result = DeserializeObject<TestStruct>(testJsonData);

		EXPECT_EQ(result.field1, 1);
		EXPECT_EQ(result.field2, 2);
		EXPECT_EQ(result.field3, 3);
}