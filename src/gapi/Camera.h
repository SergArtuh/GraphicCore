#pragma once
#include "api.h"
#include "RenderPassInput.h"

#include "common/Matrix.h"
#include "common/Vector.h"

namespace gapi {
	class GAPI_EXPORT Camera final : public RenderPassInput{
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
}
