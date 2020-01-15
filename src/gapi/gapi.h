#pragma once
#include "api.h"
#include "llr/llr.h"

namespace wnd {
	class Window;
}

namespace gapi {
	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);
	private:
		llr::Llr m_llr;
	};
}
