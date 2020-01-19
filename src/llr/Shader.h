#pragma once
#include "api.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "ReferenceCounter.h"

#include "enum.h"

#include "GL/glew.h"

#include <vector> 
#include <list>
#include <map>

namespace llr
{
	struct ShaderSource {
		ShaderSource() : Data(nullptr), Type(EShaderSourceType::NONE){}
		ShaderSource(const char * const data, const EShaderSourceType type) : Data(data), Type(type) {}
		const char * const Data;
		EShaderSourceType Type;
	};

	const ShaderSource g_noShaderSource = ShaderSource();


	class  Shader final
	{
	public:
		Shader() = default;
		Shader(std::list<ShaderSource> shaderSources);
		
		Shader(const Shader&);

		Shader& operator=(const Shader& r);

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
		ReferenceCounter m_referenceCounter;

		std::map<int, VertexBuffer> m_vertexBuffer;
		IndexBuffer m_indexBuffer = IndexBuffer();

		GLuint m_programId = ((GLuint) UNUSED );
	};
}
