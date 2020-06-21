#pragma once
#include "api.h"

#include "wnd/window.h"

#include <map>

namespace gapi {
	class Scene;
	class RenderPass;

	class GAPI_EXPORT Context final {
		friend class Gapi;

		using RenderPasses = std::multimap<int, RenderPass*>;

	private:
		Context(wnd::Window & window);
		Context(const Context&) = delete;
		Context() = default;
		Context& operator=(const Context&) = default;
	public:
		
		void AddRenderPass(RenderPass* renderPass, I32 priority = 99);

		void RemoveRenderPass(RenderPass* renderPass);

		void Draw(const Scene * scene);
	private:
		void SetupRenderPass(const Scene* scene, RenderPass*);

		wnd::Window m_window;

		RenderPasses m_renderPasses;
	};
}
