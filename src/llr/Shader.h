#pragma once
#include "api.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture2d.h"
#include "Framebuffer.h"

#include "VertexArrayBuffer.h"

#include "ReferenceCounter.h"

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
		
		Shader(const Shader&) = default;

		Shader& operator=(const Shader& r);

		~Shader();
			
		void SetVertexArrayBuffer(const llr::VertexArrayBuffer vao);

		void SetConstantBuffer(const ConstantBuffer buffer, CI32 location);

		void SetTexture2D(const Texture2D texture, CI32 location);

		void SetVertexBuffer(const VertexBuffer buffer, CI32 location, CSize stride = 0U);

		void SetIndexBuffer(const IndexBuffer buffer);

		void SetFramebuffer(const Framebuffer framebuffer);

		void Draw();

		GLuint GetId() const {return m_programId; }

		bool IsValid() const { return m_programId != (GLuint)UNUSED; }

	public:
		void SetConstant(const char* name, const float c0, const float c1, const float c2);

		void SetConstant(const char* name, const int c0, const int c1, const int c2);

		void SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2);


		void SetConstant(const char* name, const float c0, const float c1, const float c2, const float c3);

		void SetConstant(const char* name, const int c0, const int c1, const int c2, const float c3);

		void SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2, const float c3);

		void SetInstanceCount(CUI32 count);

	private:
		ReferenceCounter m_referenceCounter;

		llr::VertexArrayBuffer m_vao;

		std::map<int, ConstantBuffer> m_constantBuffer;
		std::map<int, VertexBuffer> m_vertexBuffer;
		std::map<int, Texture2D> m_textures2d;
		IndexBuffer m_indexBuffer;
		Framebuffer m_framebuffer;
		UI32 m_instanceCount = 0;

		GLuint m_programId = ((GLuint) UNUSED );
	};
}
