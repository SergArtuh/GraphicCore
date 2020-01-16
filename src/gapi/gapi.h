#pragma once
#include "api.h"
#include "llr/llr.h"

#include <vector>

namespace wnd {
	class Window;
}

namespace gapi {
	class Context;
	class Scene;
	class RenderPass;
	class Geometry;


	class GAPI_EXPORT Gapi final {
	public:
		Gapi(wnd::Window & window);
		~Gapi();

		Scene* CreateScene();

		void DeleteScene(Scene*);

		RenderPass* CreateRenderPass(llr::Shader & shader);

		void DeleteRenderPass(RenderPass * renderPass);

		Geometry* CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);

		void DeleteGeometry(Geometry*);

		void Draw(Scene* scene);

	private:
		llr::Llr m_llr;
		Context* m_context = nullptr;
	};
}
