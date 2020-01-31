#pragma once

#include "api.h"

namespace wnd {
	class Window;
	class WND_EXPORT IRenderer {
	public:
		virtual void OnRender(Window & window) = 0;
	};
}
