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

		Scene* CreateScene();

		void DeleteScene(Scene*);


		Shader* CreateShader(const std::list< ShaderSource> & sources);

		void DeleteShader(Shader * shader);


		RenderPass* CreateRenderPass(Shader * shader);

		void DeleteRenderPass(RenderPass * renderPass);

		void AddRenderPass(RenderPass* renderPass);

		void RemoveRenderPass(RenderPass* renderPass);

		Geometry* CreateGeometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);

		void DeleteGeometry(Geometry*);

		void Draw(Scene* scene);

	private:
		llr::Llr m_llr;
		Context* m_context = nullptr;

		size_t* m_instanceCounterRef = nullptr;
	};
}
