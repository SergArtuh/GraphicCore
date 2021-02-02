#include "Camera.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

namespace gapi {
	
	Camera::Camera(float fov, float aspect, float near, float far) : 
		RenderPassConstantInput(m_projMat.SizeInBytes() + m_viewMat.SizeInBytes() + m_posVec.SizeInBytes())
		, m_projMat(reinterpret_cast<float *>( GetData().data() ), shmem::Use())
		, m_viewMat(reinterpret_cast<float*>(GetData().data() + m_projMat.SizeInBytes()), shmem::Use())
		, m_posVec(reinterpret_cast<float*>(GetData().data() + m_projMat.SizeInBytes() + m_viewMat.SizeInBytes()), shmem::Use()) {
	
		makeProjectionMatrix(fov, aspect, near, far, m_projMat);
		makeIdentityMatrix(m_viewMat);
		makeZeroVector(m_posVec);
		Update();
	}
}