#pragma once
#include "api.h"

#include "llr/enum.h"
#include "llr/Shader.h"

#include <list>

namespace gapi {
	class Geometry;
	class Camera;

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
		friend class Gapi;
	private:
		Shader(const std::list<ShaderSource>& sources);
		Shader() = default;
		Shader(const Shader&) = default;
		Shader& operator=(const Shader&) = default;
	public:

		llr::Shader& GetShaderLLr();
		const llr::Shader& GetShaderLLr() const;

		//TODO: create SetConstantBuffer

		void SetGeometry(const Geometry & geometry);

		void SetCamera(const Camera & camera);

		void Draw();

		bool IsValid() const;
	private:
		llr::Shader m_shader;
	};
}
