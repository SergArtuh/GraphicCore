#include "api.h"

#include "window.h"
#include "GLFW/glfw3.h"

#define MIN_REQUIRED_OGL_VERSION_MAJOR 4
#define MIN_REQUIRED_OGL_VERSION_MINOR 3

namespace wnd {
	Window::Window(const size_t w, const size_t h, const char* title) : m_width(w), m_height(h)
	{
		if (!glfwInit())
			return;

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MIN_REQUIRED_OGL_VERSION_MAJOR);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MIN_REQUIRED_OGL_VERSION_MINOR);

		m_window = glfwCreateWindow((int)m_width, (int)m_height, title, NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			return;
		}

		makeContextCurrent();
	}

	Window::Window(Window& r)
	{
		std::swap(m_window, r.m_window);
	}

	Window::~Window()
	{
		if (m_window)
		{
			glfwTerminate();
			m_window = nullptr;
		}
	}

	void Window::makeContextCurrent()
	{
		glfwMakeContextCurrent(m_window);
	}


	void Window::addRenderer(IRenderer* renderer)
	{
		m_rendererListener.push_back(renderer);
	}

	void Window::removeRenderer(IRenderer* renderer)
	{
		for (auto r : m_rendererListener) {
			if (r == renderer) {
				m_rendererListener.remove(renderer);
				return;
			}
		}
	}

	void Window::clearRenderers()
	{
		m_rendererListener.clear();
	}

	void Window::draw()
	{
		for (auto r : m_rendererListener) {
			r->OnRender(* this );
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

}