#pragma once
#include "api.h"
#include "llr/llr.h"

#include <vector>

namespace wnd {
	class Window;
}

namespace gapi {
	class Scene;
	class Geometry;

	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);

		Scene* CreateScene();

		void DeleteScene(Scene*);

		Geometry* CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);

		void DeleteGeometry(Geometry*);

	private:
		llr::Llr m_llr;
	};
}
