#pragma once
#include "api.h"
#include "llr/llr.h"

#include "Shader.h"

#include <vector>
#include <list>

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
		Gapi(const Gapi & gapi);

		~Gapi();

		Context* CreateContext();

		void DeleteContext(Context * context);

		Scene* CreateScene();

		void DeleteScene(Scene*);


		Shader* CreateShader(const std::list< ShaderSource> & sources);

		void DeleteShader(Shader * shader);


		RenderPass* CreateRenderPass(Shader * shader);

		void DeleteRenderPass(RenderPass * renderPass);

		void ContextAddRenderPass(Context* context, RenderPass* renderPass);

		void ContextRemoveRenderPass(Context* context, RenderPass* renderPass);

		Geometry* CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);

		void DeleteGeometry(Geometry*);

		void Draw(Context* context, Scene* scene);

	private:
		llr::Llr m_llr;

		size_t* m_instanceCounterRef = nullptr;
	};
}
