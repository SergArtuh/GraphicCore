#pragma once
#include "api.h"
#include "RenderPassConstantInput.h"

#include "common/Matrix.h"
#include "common/Vector.h"

namespace gapi {
	class GAPI_EXPORT Camera final : public RenderPassConstantInput{
		friend class Gapi;
	private:
		Camera(float fow, float aspect, float near, float far);
		Camera() = default;
		Camera(const Camera&) = default;
		Camera& operator=(const Camera&) = default;

	private:
		Mat4f m_projMat;
		Mat4f m_viewMat;
		Vec4f m_posVec;
	};

	using PCamera = Camera*;
}
