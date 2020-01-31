#pragma once
#include "api.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

#include <vector>


namespace gapi {
	class GAPI_EXPORT Geometry final {
		friend class Gapi;
	private:
		Geometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes);
		Geometry() = default;
		Geometry(const Geometry&) = default;
		Geometry& operator=(const Geometry&) = default;

	public:
		bool operator==(const Geometry & r);

		const llr::VertexBuffer GetVertexBuffer() const;

		const llr::IndexBuffer GetIndexBuffer() const;

		bool IsValid() const;
	private:
		llr::VertexBuffer m_vertexBuffer;
		llr::IndexBuffer m_indexBuffer;
	};
}
