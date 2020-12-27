#pragma once
#include <string>

#define MAX_NUMBER_OF_FIELDS 10

struct Type {
	std::string name; 
	size_t size; 
};

struct Field {
	Type* type;
	std::string name;
	size_t offset; 
};

struct Class {
	Field field[MAX_NUMBER_OF_FIELDS];
};

template<typename T>
const Class* GetClass();

#define BEGIN_ATTRIBUTES_FOR(CLASS)  \
template<> \
const Class* GetClass<CLASS>() { \
	static Class localClass; \
	using type = CLASS; 
	enum { BASE = __COUNTER__ }; \

#define DEFINE_MEMBER(NAME)  \
	enum { NAME##INDEX = __COUNTER__ - BASE - 1}; \
	localClass.field[NAME##INDEX].name = #NAME;  \
	localClass.field[NAME##INDEX].offset = offsetof(type, NAME);\

#define END_ATTRIBUTES \
return &localClass; \
}\

