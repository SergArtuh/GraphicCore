#pragma once

#include <stdint.h>

#include "api.h"

namespace gapi {
	enum class ERenderPassInputGeometryTarget : I32 {
		NONE = -1,
		ALL_SCENE = 1,
		NDC_RECT,
		CUSTOM
	};


	enum class ETextureFormat : int
	{
		RED,
		RED_INTEGER,
		RGB,
		RGB_INTEGER,
		RGBA,
		RGBA_INTEGER,
		NONE = -1
	};
}
