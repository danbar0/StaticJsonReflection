#pragma once
#include <string>
#include <array>

#define MAX_NUMBER_OF_FIELDS 10

struct Type {
		std::string name; 
		size_t size; 
};

struct Field {
		const Type* type;
		std::string name;
		size_t offset; 
};

struct Class {
		std::array<Field, MAX_NUMBER_OF_FIELDS> fields;
};

template<typename T>
const Type* GetType();

template<typename T>
const Class* GetClass();

#define DEFINE_TYPE(TYPE) \
template<> \
const Type* GetType<TYPE>() { \
		static Type type; \
		type.name = #TYPE; \
		type.size = sizeof(TYPE); \
		return &type; \
}\

#define BEGIN_ATTRIBUTES_FOR(CLASS)  \
template<> \
const Class* GetClass<CLASS>() { \
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

