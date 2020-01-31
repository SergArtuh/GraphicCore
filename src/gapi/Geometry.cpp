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
	bool Geometry::operator==(const Geometry& r)
	{
		return m_vertexBuffer.GetId() == r.m_vertexBuffer.GetId()
			&& m_indexBuffer.GetId() == r.m_indexBuffer.GetId();
	}
	const llr::VertexBuffer Geometry::GetVertexBuffer() const
	{
		return m_vertexBuffer;
	}
	const llr::IndexBuffer Geometry::GetIndexBuffer() const
	{
		return m_indexBuffer;
	}
	bool Geometry::IsValid() const
	{
		return m_vertexBuffer.IsValid() && m_indexBuffer.IsValid();
	}
}