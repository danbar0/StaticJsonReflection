#pragma once
#include "pch.h"
#include <string>

template<typename T>
std::string SerializeObject(T&);

template<typename T>
T DeserializeObject(const std::string& json); 
