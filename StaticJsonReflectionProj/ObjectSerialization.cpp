#include "pch.h"
#include "ObjectSerialization.hpp"
#include "GetClass.hpp"
#include "rapidjson/document.h"

using namespace rapidjson; 

template<typename T>
std::string SerializeObject(const T& arg) {
		Class* objectInfo = GetClass<T>(); 
		std::string result; 
		Document document; 

		for (auto& field : objectInfo->fields) {
				if (field.type == nullptr) break; 

				switch (field.type->enumName) {
						case TypeName::int8_t: {
								int8_t result = *reinterpret_cast<int8_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
								document.AddMember(field.name, Value(result), document.GetAllocator());

								break;
						}

						case TypeName::int16_t: {
								int16_t result = reinterpret_cast<int16_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
								document.AddMember(field.name, Value(result), document.GetAllocator());
								break;
						}

						case TypeName::int32_t: {
								int32_t result = reinterpret_cast<int32_t*>(reinterpret_cast<int8_t*>(&arg) + field.offset);
								document.AddMember(field.name, Value(result), document.GetAllocator());
								break;
						}

						default:
								assert(false); 
								break;
				}
				
		}

		return result; 
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