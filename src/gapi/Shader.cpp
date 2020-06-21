#include "Shader.h"
#include "Geometry.h"
#include "Camera.h"


namespace gapi {
	Shader::Shader(const std::list<ShaderSource> & sources) {
		std::list<llr::ShaderSource> llrShaderSources;

		for (auto ss : sources) {
			llrShaderSources.push_back(llr::ShaderSource(ss.Source, ss.Type));
		}

		m_shader = llr::Shader(llrShaderSources);
	}
	llr::Shader& Shader::GetShaderLLr()
	{
		return m_shader;
	}
	const llr::Shader& Shader::GetShaderLLr() const
	{
		return m_shader;
	}
	void Shader::SetGeometry(CGeometry& geometry) {
		m_shader.SetVertexArrayBuffer(geometry.GetVertexArrayBuffer());
	}

	void Shader::SetCamera(CCamera& camera) {
		m_shader.SetConstantBuffer(camera.GetConstantBuffer(), 0); //TODO: USE CONSTANT
	}

	void Shader::Draw() {
		m_shader.Draw();
	}

	bool Shader::IsValid() const
	{
		return m_shader.IsValid();
	}
}