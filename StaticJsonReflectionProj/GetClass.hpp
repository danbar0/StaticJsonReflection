#pragma once
#include <string>
#include <array>

#define MAX_NUMBER_OF_FIELDS 10

enum class TypeName {
		int8_t,
		int16_t,
		int32_t
};

struct Type {
		std::string stringName; 
		TypeName enumName; 
		size_t size;
};

struct Field {
		Type* type;
		std::string name;
		size_t offset; 
};

struct Class {
		std::array<Field, MAX_NUMBER_OF_FIELDS> fields;
};

template<typename T>
Type* GetType();

template<typename T>
Class* GetClass();

#define DEFINE_TYPE(TYPE) \
template<> \
Type* GetType<TYPE>() { \
		static Type type; \
		type.stringName = #TYPE; \
		type.size = sizeof(TYPE); \
		type.enumName = TypeName::TYPE; \
		return &type; \
}\

#define BEGIN_ATTRIBUTES_FOR(CLASS)  \
template<> \
Class* GetClass<CLASS>() { \
		using ClassType = CLASS; \
		static Class localClass; \
		enum { BASE = __COUNTER__ }; \

#define DEFINE_MEMBER(NAME)  \
		enum { NAME##Index = __COUNTER__ - BASE - 1}; \
		localClass.fields[NAME##Index].type = GetType<decltype(ClassType::NAME)>();\
		localClass.fields[NAME##Index].name = #NAME;  \
		localClass.fields[NAME##Index].offset = offsetof(ClassType, NAME);\

#define END_ATTRIBUTES \
return &localClass; \
}\

