#include "helper.h"
#include "api.h"

namespace llr {
	namespace helper {
		size_t getDataTypeSize(EDataType type) {
			switch (type)
			{
			
			case llr::EDataType::FLOAT: return sizeof(float);
			case llr::EDataType::INT: 
			case llr::EDataType::UINT: return sizeof(int);
			case llr::EDataType::NONE:
			default: 
				LLR_ERROR("Unknown data type enum");
				return 0;
			}
		}
	}
}
