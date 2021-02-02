#pragma once
#include "api.h"
#include "common/Logger.h"

#define GL_CHECK { GLenum err = glGetError(); if(err != GL_NO_ERROR) {LOG_ERROR("OpenGL error with error code %x, at %d line %s", err, __LINE__, __FILE__);}}

namespace llr {
	namespace helper {
		size_t getDataTypeSize(EDataType type);
	}
}
