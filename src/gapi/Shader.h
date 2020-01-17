#pragma once
#include "api.h"

#include "llr/enum.h"
#include "llr/Shader.h"

#include <list>

namespace gapi {
	class ShaderSourceType {
	public:
		ShaderSourceType() {}
		ShaderSourceType(int type) {
			if (type < static_cast<int>(llr::EShaderSourceType::FIRST)
				|| type > static_cast<int>(llr::EShaderSourceType::LAST)) {
				
				return;
			}
			m_type = static_cast<llr::EShaderSourceType>(type);
		}
		operator llr::EShaderSourceType() { return m_type; }
		operator const llr::EShaderSourceType() const { return m_type; }

	private:
		llr::EShaderSourceType m_type = llr::EShaderSourceType::NONE;
	};

	struct ShaderSource {
	public:
		ShaderSource(const char* const source, ShaderSourceType type) : Source(source), Type(type){

		}
		const char* const Source;
		const ShaderSourceType Type;
	};

	class GAPI_EXPORT Shader final {
	public:
		Shader(const std::list<ShaderSource> & sources);

		llr::Shader& GetShaderLLr();
		const llr::Shader& GetShaderLLr() const;
	private:
		llr::Shader m_shader;
	};
}
