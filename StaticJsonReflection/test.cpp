#include "pch.h"
#include "../StaticJsonReflectionProj/GetClass.hpp"
#include "../StaticJsonReflectionProj/ObjectSerializationDef.hpp"

struct TestStruct {
	int32_t field1;
	int16_t field2;
	int8_t field3;
	uint32_t field4;
	uint16_t field5;
	uint8_t field6;
};

BEGIN_ATTRIBUTES_FOR(TestStruct)
DEFINE_MEMBER(field1);
DEFINE_MEMBER(field2);
DEFINE_MEMBER(field3);
DEFINE_MEMBER(field4);
DEFINE_MEMBER(field5);
DEFINE_MEMBER(field6);
END_ATTRIBUTES

TEST(SerializationTest, SerializeTest) {
	TestStruct test { 1, 2, 3, 4, 5, 6};

	auto result = SerializeObject(test); 

	EXPECT_EQ(result, "{\"field1\":1,\"field2\":2,\"field3\":3,\"field4\":4,\"field5\":5,\"field6\":6}");
}

TEST(SerializationTest, DeserializeTest) {
		std::string testJsonData = "{\"field1\":1,\"field2\":2,\"field3\":3,\"field4\":4,\"field5\":5,\"field6\":6}";

		TestStruct result = DeserializeObject<TestStruct>(testJsonData);

		EXPECT_EQ(result.field1, 1);
		EXPECT_EQ(result.field2, 2);
		EXPECT_EQ(result.field3, 3);
		EXPECT_EQ(result.field4, 4);
		EXPECT_EQ(result.field5, 5);
		EXPECT_EQ(result.field6, 6);
}