#include "GlAdapter.h"
#include "common/Logger.h"

#include "api.h"

namespace llr {
	namespace adapter {
		DataType::DataType(EDataType type) {
			switch (type)
			{
				case EDataType::FLOAT:	
					m_type = GL_FLOAT;
					break;
				case EDataType::UINT:
					m_type = GL_UNSIGNED_INT;
					break;
				case EDataType::INT:
					m_type = GL_INT;
					break;
			default:
				LOG_ERROR("Unknown data type enum");
				m_type = UNUSED;
				break;
			}
		}
		DataType::operator const GLenum()
		{
			return m_type;
		}
	}
}
