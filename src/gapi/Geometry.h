#pragma once
#include "api.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

#include <vector>


namespace gapi {
	class GAPI_EXPORT Geometry final {
	public:
		Geometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);

	private:
		llr::VertexBuffer m_vertexBuffer;
		llr::IndexBuffer m_indexBuffer;
	};
}
