#pragma once
#include <string>

template<typename T>
std::string SerializeObject(const T&);

template<typename T>
T DeserializeObject(const std::string&);