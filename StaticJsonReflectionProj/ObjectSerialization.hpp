#pragma once
#include "pch.h"
#include <string>
#include "GetClass.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

template<typename T>
std::string SerializeObject(T& arg) {
		Class* objectInfo = GetClass<T>();
		std::string result;
		rapidjson::Document document;
		document.SetObject(); 

		rapidjson::Value key; 
		rapidjson::Value value; 

		for (const auto& field : objectInfo->fields) {
				if (field.type == nullptr) break;

				switch (field.type->enumName) {
				case TypeName::int8_t: {
						int8_t result = *reinterpret_cast<int8_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
						key.SetString(field.name.c_str(), field.name.size(), document.GetAllocator());
						value.SetInt(result);
						
						break;
				}

				case TypeName::int16_t: {
						int16_t result = *reinterpret_cast<int16_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
						key.SetString(field.name.c_str(), field.name.size(), document.GetAllocator());
						value.SetInt(result);

						break;
				}
														
				case TypeName::int32_t: {
						int32_t result = *reinterpret_cast<int32_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
						key.SetString(field.name.c_str(), field.name.size(), document.GetAllocator());
						value.SetInt(result);

						break;
				}

				default:
						assert(false);
						break;
				}

				document.AddMember(key, value, document.GetAllocator());
		}

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		return buffer.GetString();
}

template<typename T>
T DeserializeObject(const std::string& json) {
		Class* objectInfo = GetClass<T>();
		T result; 
		rapidjson::Document document; 
		document.Parse(json.c_str());

		for (const auto& field : objectInfo->fields) {
				if (field.type == nullptr) break;
				if (document.HasMember(field.name.c_str()) && document[field.name.c_str()].IsInt()) {
						(*reinterpret_cast<int8_t*>(&result) + field.offset) = document[field.name.c_str()];
				}
		}

		return result; 
}
