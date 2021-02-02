#include "api.h"
#include "helper.h"
#include "common/Logger.h"

namespace llr {
	namespace helper {
		size_t getDataTypeSize(EDataType type) {
			switch (type)
			{
			
			case EDataType::FLOAT: return sizeof(float);
			case EDataType::INT: 
			case EDataType::UINT: return sizeof(int);
			case EDataType::NONE:
			default: 
				LOG_ERROR("Unknown data type enum");
				return 0;
			}
		}
	}
}
