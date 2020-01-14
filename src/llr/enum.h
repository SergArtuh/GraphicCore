#pragma once
namespace llr
{

	enum class EDataType {
		NONE = -1,
		FLOAT = 0,
		INT,
		UINT
	};

	enum class EShaderSourceType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT,
		GEOMETRY,
		COMPUTE
	};

}
