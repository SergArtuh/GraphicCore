#include "Shader.h"
#include "VertexBuffer.h"

#include <utility>

#include "GlAdapter.h"

namespace llr
{
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

			LLR_ERROR(infoLog.data());

			return UNUSED;
		}

		return shaderId;
	}

	Shader::Shader(std::list<ShaderSource> shaderSources) {
	
		std::list<GLint> shaderIDs;

		for (auto ss : shaderSources) {
			shaderIDs.push_back(CreateShader(ss));
		}

		m_programId = glCreateProgram(); GL_CHECK

		for (auto id : shaderIDs) {
			if (id != UNUSED) {
				glAttachShader(m_programId, id); GL_CHECK
			}
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

			LLR_ERROR(infoLog.data());

			
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

		m_instanceCounterRef = new size_t[1];
		*m_instanceCounterRef = 1;
	}
	
	Shader::Shader(const Shader& r) : m_programId(r.m_programId), m_instanceCounterRef(r.m_instanceCounterRef){
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)++;
		}
	}


	Shader & Shader::operator=(const Shader& r) {
		m_programId = r.m_programId;
		m_instanceCounterRef = r.m_instanceCounterRef;

		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}

		return * this;
	}

	Shader::~Shader() {
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}
		
		if (m_instanceCounterRef && !(*m_instanceCounterRef) && m_programId != UNUSED) {
			
			glDeleteProgram(m_programId); GL_CHECK

			m_programId = UNUSED;

			delete m_instanceCounterRef;
			m_instanceCounterRef = nullptr;
		}
	}

	void Shader::SetVertexBuffer(const VertexBuffer buffer, const int location, const size_t stride)
	{
		if (!buffer.IsValid()) {
			LLR_WARNING("Try to set to a shader(Program ID: %d) Invali VertexBuffer", m_programId);
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

	void Shader::Draw()
	{
		if (!(IsValid() && m_indexBuffer.IsValid())) {
			return;
		}
		glUseProgram(m_programId); GL_CHECK

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer.GetId()); GL_CHECK

		for (auto vb : m_vertexBuffer) {
			const VertexBuffer& buffer = vb.second;
			if (!buffer.IsValid()) {
				continue;
			}

			const int & location = vb.first;
			
			glEnableVertexAttribArray(location);  GL_CHECK
			glBindBuffer(GL_ARRAY_BUFFER, buffer.GetId()); GL_CHECK
		}
		
		glDrawElements(GL_TRIANGLES, (GLsizei)m_indexBuffer.GetSize(), adapter::DataType(m_indexBuffer.GetDataType()), NULL); GL_CHECK

		for (auto vb : m_vertexBuffer) {
			const int& location = vb.first;
			glDisableVertexAttribArray(location);  GL_CHECK	
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
		glUseProgram(0); GL_CHECK
	}
	void Shader::SetConstant(const char* name, const float c0, const float c1, const float c2)
	{
		glUseProgram(m_programId);
		GLint location = glGetUniformLocation(m_programId, name);
		glUniform3f(location, c0, c1, c2);
		glUseProgram(0);
		
	}
	void Shader::SetConstant(const char* name, const int c0, const int c1, const int c2)
	{
		glUseProgram(m_programId);
		GLint location = glGetUniformLocation(m_programId, name);
		glUniform3i(location, c0, c1, c2);
		glUseProgram(0);
	}
	void Shader::SetConstant(const char* name, const unsigned int c0, const unsigned int c1, const unsigned int c2)
	{
		glUseProgram(m_programId);
		GLint location = glGetUniformLocation(m_programId, name);
		glUniform3ui(location, c0, c1, c2);
		glUseProgram(0);
	}
}
