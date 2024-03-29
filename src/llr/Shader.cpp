#include "Shader.h"
#include "VertexBuffer.h"

#include <utility>

#include "GlAdapter.h"

#include "helper.h"
#include "common/Logger.h"

namespace llr
{
	GLint getUniformLocation(const char* name, GLint program) {
		GLint location = glGetUniformLocation(program, name);

		if (location == UNUSED) {
			LOG_ERROR("Could not find shader(Program ID: %d) uniform with name %s", program, name);
		}
		return location;
	}




	GLint CreateShader(ShaderSource shaderSource) {
		if (shaderSource.Type == EShaderSourceType::NONE) {
			return UNUSED;
		}

		const GLenum shaderTypeEnum = [&shaderSource]()->GLenum {
			switch (shaderSource.Type)
			{
			case EShaderSourceType::VERTEX: return GL_VERTEX_SHADER;
			case EShaderSourceType::FRAGMENT: return GL_FRAGMENT_SHADER;
			case EShaderSourceType::GEOMETRY: return GL_GEOMETRY_SHADER;
			case EShaderSourceType::COMPUTE: return GL_COMPUTE_SHADER;
			default:
				return UNUSED;
			}
		}();


		

		GLuint shaderId = glCreateShader(shaderTypeEnum); GL_CHECK
		glShaderSource(shaderId, 1, (const GLchar**)&shaderSource.Data, NULL); GL_CHECK

		glCompileShader(shaderId); GL_CHECK


		GLint status;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);  GL_CHECK

		if (!status) {
			GLint maxLength = 0;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength); GL_CHECK

			std::vector<GLchar> infoLog(maxLength);

			glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]); GL_CHECK
			glDeleteShader(shaderId); GL_CHECK

			LOG_ERROR(infoLog.data());

			return UNUSED;
		}

		return shaderId;
	}

	Shader::Shader(std::list<ShaderSource> shaderSources) {
	
		std::list<GLint> shaderIDs;

		bool createShadersSuccess = true;
		for (auto ss : shaderSources) {
			GLint id = CreateShader(ss);
			if (id == UNUSED) {
				createShadersSuccess = false;
				break;
			}
			shaderIDs.push_back(id);
		}
			
		if(!createShadersSuccess) {
			for (auto id : shaderIDs) {
				glDeleteShader(id); GL_CHECK
			}
			m_programId = UNUSED;
			return;
		}

		m_programId = glCreateProgram(); GL_CHECK

		

		for (auto id : shaderIDs) {
			
			glAttachShader(m_programId, id); GL_CHECK
		}

		glLinkProgram(m_programId); GL_CHECK

		GLint isLinked = 0;
		glGetProgramiv(m_programId, GL_LINK_STATUS, (int*)&isLinked); GL_CHECK
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength); GL_CHECK

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_programId, maxLength, &maxLength, &infoLog[0]); GL_CHECK

			LOG_ERROR(infoLog.data());

			
			glDeleteProgram(m_programId); GL_CHECK
			m_programId = UNUSED;
			
			for (auto & id : shaderIDs) {
				const GLint shaderId = id;
				if (shaderId != UNUSED) {
					glDeleteShader(shaderId); GL_CHECK
				}
				id = UNUSED;
			}
			return;
		}

		for (auto id : shaderIDs) {
			const GLint shaderId = id;
			if (shaderId != UNUSED) {
				glDetachShader(m_programId, shaderId);  GL_CHECK
			}
		}
	}
	
	Shader & Shader::operator=(const Shader& r) {
		m_programId = r.m_programId;
		m_referenceCounter = r.m_referenceCounter;
		return * this;
	}

	Shader::~Shader() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_programId != UNUSED) {
			
			glDeleteProgram(m_programId); GL_CHECK

			m_programId = UNUSED;
		}
	}

	void Shader::SetVertexArrayBuffer(const llr::VertexArrayBuffer vao) {
		m_vao = vao;
	}

	void Shader::SetConstantBuffer(const ConstantBuffer buffer, CI32 location) {

		if (!buffer.IsValid()) {
			LOG_WARNING("Try to set to a shader(Program ID: %d) Invali ConstantBuffer", m_programId);
			return;
		}

		m_constantBuffer[location] = buffer;
	}

	void Shader::SetTexture2D(const Texture2D texture, CI32 location) {
		if (!texture.IsValid()) {
			LOG_WARNING("Try to set to a shader(Program ID: %d) Invali Texture2d", m_programId);
			return;
		}

		m_textures2d[location] = texture;
	}

	void Shader::SetVertexBuffer(const VertexBuffer buffer, CI32 location, CSize stride)
	{
		if (!buffer.IsValid()) {
			LOG_WARNING("Try to set to a shader(Program ID: %d) Invali VertexBuffer", m_programId);
			return;
		}

		m_vertexBuffer[location] = buffer;

		glUseProgram(m_programId); GL_CHECK

		glBindBuffer(GL_ARRAY_BUFFER, buffer.GetId()); GL_CHECK

		glVertexAttribPointer(location, (GLsizei)buffer.GetCount(), adapter::DataType(buffer.GetDataType()), GL_FALSE, (GLsizei)stride, nullptr); GL_CHECK

		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK

		glUseProgram(0); GL_CHECK
	}
	void Shader::SetIndexBuffer(const IndexBuffer buffer)
	{
		m_indexBuffer = buffer;
	}

	void Shader::SetFramebuffer(const Framebuffer framebuffer) {
		m_framebuffer = framebuffer;
	}

	void Shader::Draw()
	{
		if (!IsValid()) {
			LOG_WARNING("Try to draw invalid shader");
			return;
		}


		if (m_framebuffer.IsValid()) {
			glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer.GetId()); GL_CHECK
		}

		glUseProgram(m_programId); GL_CHECK
		glEnable(GL_DEPTH_TEST);

		for (auto uniformBlock : m_constantBuffer)
		{
			const int bindingId = uniformBlock.first;
			const ConstantBuffer buffer = uniformBlock.second;
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingId, buffer.GetId()); GL_CHECK

		}

		for (const auto& textureAttachment : m_textures2d)
		{
			const GLuint attachmenyId = textureAttachment.first;
			const Texture2D texture = textureAttachment.second;

			glActiveTexture(GL_TEXTURE0 + attachmenyId);
			glBindTexture(GL_TEXTURE_2D, texture.GetId());
		}


		GLsizei idxSize = 0;
		GLenum idxDataType = UNUSED;

		if (m_vao.IsValid()) {
			m_vao.Bind();

			idxSize = (GLsizei)m_vao.GetIndexSize();
			idxDataType = adapter::DataType(m_vao.GetIndexDataType());
		}
		else {
			if (!m_indexBuffer.IsValid()) {
				LOG_WARNING("Try to draw shader (Program ID: %d) with invalid index buffer", m_programId);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer.GetId()); GL_CHECK

			for (auto vb : m_vertexBuffer) {
				const VertexBuffer& buffer = vb.second;
				if (!buffer.IsValid()) {
					continue;
				}

				const int& location = vb.first;

				glEnableVertexAttribArray(location);  GL_CHECK
				glBindBuffer(GL_ARRAY_BUFFER, buffer.GetId()); GL_CHECK
				glVertexAttribDivisor(location, (buffer.IsInstansable()) ? 1 : 0); GL_CHECK
			}


			idxSize = (GLsizei)m_indexBuffer.GetSize();
			idxDataType = adapter::DataType(m_indexBuffer.GetDataType());
		}

		if (m_instanceCount > 0) {
			glDrawElementsInstanced(GL_TRIANGLES, idxSize, idxDataType, NULL, m_instanceCount); GL_CHECK
		}
		else {
			glDrawElements(GL_TRIANGLES, idxSize, idxDataType, NULL); GL_CHECK
		}
		

		for (auto vb : m_vertexBuffer) {
			const int& location = vb.first;
			glDisableVertexAttribArray(location);  GL_CHECK	
		}

		if (m_vao.IsValid()) {
			m_vao.Unbind();
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK
		}
		
		glDisable(GL_DEPTH_TEST);
		glUseProgram(0); GL_CHECK
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void Shader::SetConstant(const char* name, const float c0, const float c1, const float c2)
	{
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform3f(location, c0, c1, c2);
		}

		glUseProgram(0);
		
	}
	void Shader::SetConstant(const char* name, const int c0, const int c1, const int c2)
	{
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform3i(location, c0, c1, c2);
		}

		glUseProgram(0);
	}
	void Shader::SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2)
	{
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform3ui(location, c0, c1, c2);
		}

		glUseProgram(0);
	}

	void Shader::SetConstant(const char* name, const float c0, const float c1, const float c2, const float c3) {
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform4f(location, c0, c1, c2, c3);
		}

		glUseProgram(0);
	}

	void Shader::SetConstant(const char* name, const int c0, const int c1, const int c2, const float c3) {
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform4i(location, c0, c1, c2, c3);
		}

		glUseProgram(0);
	}
	void Shader::SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2, const float c3) {
		glUseProgram(m_programId);
		auto location = getUniformLocation(name, m_programId);

		if (location != UNUSED) {
			glUniform4ui(location, c0, c1, c2, c3);
		}

		glUseProgram(0);
	}
	void Shader::SetInstanceCount(CUI32 count) {
		m_instanceCount = count;
	}
}
