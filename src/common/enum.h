#pragma once

#include "types.h"

enum class EDataType : I32 {
	NONE = -1,
	FLOAT = 0,
	INT,
	UINT
};

enum class ETextureFormat : I32
{
	RED,
	RED_INTEGER,
	RGB,
	RGB_INTEGER,
	RGBA,
	RGBA_INTEGER,
	NONE = -1
};

enum class ERenderPassInputGeometryTarget : I32 {
	NONE = -1,
	ALL_SCENE = 1,
	NDC_RECT,
	CUSTOM
};

enum class EShaderSourceType {
	NONE = -1,
	VERTEX = 1,
	FRAGMENT,
	GEOMETRY,
	COMPUTE,

	FIRST = VERTEX,
	LAST = FRAGMENT
};
