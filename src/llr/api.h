#pragma once

#define LLR_EXPORT __declspec(dllexport)

#define LLR_ERROR(str, ...) llr::errorMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LLR_WARNING(str, ...) llr::warningMsg( __LINE__, __FILE__, (str), __VA_ARGS__)
#define LLR_INFO(str, ...) llr::infoMsg( __LINE__, __FILE__, (str), __VA_ARGS__)

#define GL_CHECK { GLenum err = glGetError(); if(err != GL_NO_ERROR) {LLR_ERROR("OpenGL error with error code %x, at %d line %s", err, __LINE__, __FILE__);}}

#define UNUSED -1

namespace llr {

	void errorMsg(const int line, const char * const file, const const char* str, ...);

	void warningMsg(const int line, const char* const file, const char* str, ...);

	void infoMsg(const int line, const char* const file, const char* str, ...);
}