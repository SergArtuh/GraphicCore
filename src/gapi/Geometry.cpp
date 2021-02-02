#include "Geometry.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

namespace gapi {
	Geometry::Geometry(std::vector<float> vertices3f, std::vector<UI32> indexes) 
	{
		llr::VertexBuffer vertexBuffer(vertices3f.size(), EDataType::FLOAT, 3);
		llr::IndexBuffer indexBuffer(indexes.size(), EDataType::UINT);

		vertexBuffer.Write(0, vertices3f.size(), vertices3f.data());
		indexBuffer.Write(0, indexes.size(), indexes.data());

		m_vao.SetIndexBuffer(indexBuffer);

		//TODO: use constant
		m_vao.SetVertexBuffer(vertexBuffer, 0);
	}
	bool Geometry::operator==(const Geometry& r)
	{
		return m_vao.GetId() != UNUSED && m_vao.GetId() == r.m_vao.GetId();
	}
	const llr::VertexArrayBuffer Geometry::GetVertexArrayBuffer() const
	{
		return m_vao;
	}
	
	bool Geometry::IsValid() const
	{
		return m_vao.IsValid();
	}
	bool Geometry::IsAddedToScene() const
	{
		return m_isAddedScene;
	}
	void Geometry::SetIsAddedToScene(bool isInScene)
	{
		m_isAddedScene = isInScene;
	}
}