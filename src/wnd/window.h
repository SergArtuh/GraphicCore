#pragma once

#include "api.h"
#include "IRenderer.h"

#include<list>

struct  GLFWwindow;

namespace wnd {
	class WND_EXPORT Window {
		public:
			Window() = default;
			Window(const size_t w, const size_t h, const char* title);
			Window(const Window& r) = default;

			~Window();

			void makeContextCurrent();

			void addRenderer(IRenderer* renderer);

			void removeRenderer(IRenderer* renderer);

			void clearRenderers();

			size_t getWidth() const { return m_width; }

			size_t getHeight() const { return m_height; }

			void draw();

			bool isValid() const;

		private:
			GLFWwindow* m_window = nullptr;
			size_t m_width = 0;
			size_t m_height = 0;

			std::list<IRenderer*> m_rendererListener;
	};
}
