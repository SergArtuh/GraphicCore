#pragma once
#include "api.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

#include <vector>


namespace gapi {
	class GAPI_EXPORT Geometry final {
	public:
		Geometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);
		bool operator==(const Geometry & r);

		const llr::VertexBuffer GetVertexBuffer() const;

		const llr::IndexBuffer GetIndexBuffer() const;
	private:
		llr::VertexBuffer m_vertexBuffer;
		llr::IndexBuffer m_indexBuffer;
	};
}
