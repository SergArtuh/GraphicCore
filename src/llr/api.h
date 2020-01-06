#pragma once

#define LLR_EXPORT __declspec(dllexport)

#define LLR_ERROR(str, ...) llr::errorMsg((str), __VA_ARGS__)
#define LLR_WARNING(str, ...) llr::warningMsg((str), __VA_ARGS__)
#define LLR_INFO(str, ...) llr::infoMsg((str), __VA_ARGS__)

#define GL_CHECK if(glGetError() != GL_NO_ERROR) {LLR_ERROR("OpenGL error with error code %x, at %d line %s", glGetError(), __LINE__, __FILE__);}

#define UNUSED -1

namespace llr {

	void errorMsg(const char* str, ...);

	void warningMsg(const char* str, ...);

	void infoMsg(const char* str, ...);
}