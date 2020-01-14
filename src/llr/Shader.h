#pragma once
#include "api.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "enum.h"

#include "GL/glew.h"

#include <vector> 
#include <map>

#define NO_SHADER_SOURCE g_noShaderSource

namespace llr
{
	struct ShaderSource {
		ShaderSource() : Data(nullptr), Type(EShaderSourceType::NONE){}
		ShaderSource(const char* data, EShaderSourceType type) : Data(data), Type(type) {}
		const char* Data;
		EShaderSourceType Type;
	};

	const ShaderSource g_noShaderSource = ShaderSource();


	class  Shader final
	{
	public:
		Shader(
			ShaderSource shaderSource0
			, ShaderSource shaderSource1 = NO_SHADER_SOURCE
			, ShaderSource shaderSource2 = NO_SHADER_SOURCE
			, ShaderSource shaderSource3 = NO_SHADER_SOURCE
		);
		
		Shader(Shader&);

		Shader& operator=(Shader& r);

		~Shader();
			
		void SetVertexBuffer(const VertexBuffer buffer, const int location, const size_t stride = 0U);

		void SetIndexBuffer(const IndexBuffer buffer);

		void Draw();

		GLuint GetId() const {return m_programId; }

		bool IsValid() const { return m_programId != (GLuint)UNUSED; }

	public:
		void SetConstant(const char* name, const float c0, const float c1, const float c2);
		void SetConstant(const char* name, const int c0, const int c1, const int c2);
		void SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2);

	private:

		std::map<int, VertexBuffer> m_vertexBuffer;
		IndexBuffer m_indexBuffer = IndexBuffer();

		GLuint m_programId = ((GLuint) UNUSED );
		size_t * m_instanceCounterRef = nullptr;
	};
}
