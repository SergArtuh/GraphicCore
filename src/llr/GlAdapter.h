#pragma once
#include "api.h"
#include "GL/glew.h"

namespace llr {
	namespace adapter {
		class DataType {
		public:
			DataType(EDataType type);

			operator const GLenum();
		private:
			GLenum m_type;
		};
	}
}
