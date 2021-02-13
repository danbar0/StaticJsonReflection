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
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		rapidjson::Value key; 
		rapidjson::Value value; 

		for (auto& field : objectInfo->fields) {
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

		}

		document.AddMember(key, value, document.GetAllocator());
		return buffer.GetString();
}

template<typename T>
T DeserializeObject(const std::string& arg) {

		//for (auto& field : objectInfo->fields) {
		//		switch (field.type->size) {
		//		case 1:
		//				break;

		//		case 2:
		//				break;

		//		case 4:
		//				break;

		//		default:
		//				break;
		//		}
		//}

}
