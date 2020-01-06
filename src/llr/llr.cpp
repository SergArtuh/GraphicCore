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
}
