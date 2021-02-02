#pragma once
#include "api.h"

#include "llr/Shader.h"

#include <list>

namespace gapi {
	class Geometry;
	class Camera;

	enum class ReservedShaderInputConstant : I32{
		CAMERA = 0
	};


	class ShaderSourceType {
	public:
		ShaderSourceType() {}
		ShaderSourceType(I32 type) {
			if (type < static_cast<I32>(EShaderSourceType::FIRST)
				|| type > static_cast<I32>(EShaderSourceType::LAST)) {
				
				return;
			}
			m_type = static_cast<EShaderSourceType>(type);
		}
		operator EShaderSourceType() { return m_type; }
		operator const EShaderSourceType() const { return m_type; }

	private:
		EShaderSourceType m_type = EShaderSourceType::NONE;
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

		void SetGeometry(const Geometry & geometry);

		[[deprecated]]
		void SetCamera(const Camera & camera);

		void Draw();

		bool IsValid() const;
	private:
		llr::Shader m_shader;
	};

	using PShader = Shader*;
}
