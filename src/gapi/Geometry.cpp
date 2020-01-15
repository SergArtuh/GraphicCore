#include "Scene.h"
#include "Geometry.h"

namespace gapi {
	Geometry::Geometry(std::vector<float> vertices3f, std::vector<unsigned int> indexes) 
		: m_vertexBuffer(vertices3f.size(), llr::EDataType::FLOAT, 3)
		, m_indexBuffer(indexes.size(), llr::EDataType::UINT)
	{
		if (!m_vertexBuffer.IsValid()) {
			throw std::exception("vertex buffer invalid");
		}

		if (!m_indexBuffer.IsValid()) {
			throw std::exception("index buffer invalid");
		}


		m_vertexBuffer.Write(0, vertices3f.size(), vertices3f.data());
		m_indexBuffer.Write(0, indexes.size(), indexes.data());
	}
}