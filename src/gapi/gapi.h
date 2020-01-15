#pragma once
#include "api.h"
#include "llr/llr.h"


namespace wnd {
	class Window;
}

namespace gapi {
	class Scene;

	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);

		Scene* CreateScene();
		void DeleteScene(Scene*);

	private:
		llr::Llr m_llr;
	};
}
