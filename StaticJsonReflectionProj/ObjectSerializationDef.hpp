#pragma once
#include "pch.h"
#include <string>
#include "GetClass.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

template<typename T>
std::string SerializeObject(T& arg) {
		const Class* objectInfo = GetClass<T>();
		std::string result;
		rapidjson::Document document;
		rapidjson::Value key; 
		rapidjson::Value value; 

		document.SetObject();

		for (const auto& field : objectInfo->fields) {
				if (field.type == nullptr) break;

				key.SetString(field.name.c_str(), field.name.size(), document.GetAllocator());
				int8_t* source = reinterpret_cast<int8_t*>(&arg) + field.offset;

				switch (field.type->enumName) {
						case TypeName::int8_t:
						case TypeName::int16_t:
						case TypeName::int32_t: {
								int32_t destination = 0;
								memcpy(&destination, source, field.type->size);
								value.SetInt(destination);
								break;
						}

						case TypeName::uint8_t:
						case TypeName::uint16_t:
						case TypeName::uint32_t: {
								uint32_t destination = 0; 
								memcpy(&destination, source, field.type->size);
								value.SetUint(destination);
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
		const Class* objectInfo = GetClass<T>();
		T result; 
		rapidjson::Document document; 
		document.Parse(json.c_str());

		for (const auto& field : objectInfo->fields) {
				if (field.type == nullptr) break;
				if (document.HasMember(field.name.c_str()) && 
						(document[field.name.c_str()].IsInt() || document[field.name.c_str()].IsUint())) {
						auto* destination = reinterpret_cast<int8_t*>(&result) + field.offset;
						auto source = document[field.name.c_str()].GetInt(); 

						memcpy(destination, &source, field.type->size);
				}
		}

		return result; 
}
