#include "llr.h"

#include <GL/glew.h>
#include <Windows.h>

#include<vector>

#include "wnd/window.h"

#include "VertexBuffer.h"


namespace llr {

	Llr::Llr(wnd::Window& window) : m_window(window) {
		m_window.makeContextCurrent();

		glewInit();
		GL_CHECK
	}

	void Llr::getFramebufferData(float* o_data)
	{
		m_window.makeContextCurrent();
		glReadPixels(0, 0, (GLsizei)m_window.getWidth(), (GLsizei)m_window.getHeight(), GL_RGBA, GL_FLOAT, o_data);
	}

	wnd::Window& Llr::GetWindow() {
		return m_window;
	}

	const wnd::Window& Llr::GetWindow() const {
		return m_window;
	}

}
