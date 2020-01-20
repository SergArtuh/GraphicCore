#pragma once
#include "api.h"

#include "wnd/window.h"

#include <map>

namespace gapi {
	class Scene;
	class RenderPass;

	class GAPI_EXPORT Context final {
		friend class Gapi;
	private:
		Context(wnd::Window & window);
		Context(const Context&) = delete;
		Context() = default;
		Context& operator=(const Context&) = default;
	public:
		
		void AddRenderPass(RenderPass* renderPass, int priority = 99);

		void RemoveRenderPass(RenderPass* renderPass);

		void Draw(const Scene * scene);
	private:
		wnd::Window m_window;

		std::multimap<int, RenderPass*> m_renderPasses;
	};
}
