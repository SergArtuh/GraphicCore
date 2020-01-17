#pragma once
#include "api.h"

namespace wnd {
	class Window;
}

namespace llr {
	class VertexBuffer;

	class LLR_EXPORT Llr final {
	public:
		Llr(wnd::Window & window);
		Llr(const Llr& r) = default;

		void getFramebufferData(float* o_data);

	private:
		wnd::Window& m_window;

	};
}
