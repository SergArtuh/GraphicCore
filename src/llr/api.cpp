#include "api.h"

#include <GL/glew.h>
#include <Windows.h>

#include<vector>

#include <stdio.h>

#include "wnd/window.h"


#define MAX_BUFFER_SIZE 2048

#define GL_CHECK if(glGetError() != GL_NO_ERROR) {LLR_ERROR("OpenGL error with error code %x, at %d line %s", glGetError(), __LINE__, __FILE__);}


namespace llr {

	llr::llr(wnd::Window& window)
	{
		window.makeContextCurrent();

		glewInit();
		GL_CHECK
	}




	void llrDebugMsg(const char* str, const char * msgType, va_list args) {
		std::vector<char> buffer(MAX_BUFFER_SIZE);

		snprintf(buffer.data(), buffer.size(), "[ LLR %s ]\t", msgType);

		const size_t shift = strlen(buffer.data());

		vsnprintf(buffer.data() + shift, MAX_BUFFER_SIZE, str, args);

		OutputDebugString(buffer.data());
		OutputDebugString("\n");
	}

	void llrError(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Error", args);
		va_end(args);
	}

	void llrWarning(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Warning", args);
		va_end(args);
	}

	void llrInfo(const char* str, ...) {
		va_list args;
		va_start(args, str);
		llrDebugMsg(str, "Info", args);
		va_end(args);
	}
}