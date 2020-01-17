#include "Shader.h"


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
}