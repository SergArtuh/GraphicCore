#include "Geometry.h"

#include "llr/VertexBuffer.h"
#include "llr/IndexBuffer.h"

namespace gapi {
	Geometry::Geometry(std::vector<float> vertices3f, std::vector<UI32> indexes, std::vector<float> normals3f, std::vector<float> uv2f, std::vector<float> tangent3f, std::vector<float> bitangent3f)
	{
		llr::VertexBuffer vertexBuffer(vertices3f.size(), EDataType::FLOAT, 3);
		llr::VertexBuffer normalBuffer(normals3f.size(), EDataType::FLOAT, 3);
		llr::VertexBuffer uvBuffer(uv2f.size(), EDataType::FLOAT, 2);
		llr::VertexBuffer tangentBuffer(tangent3f.size(), EDataType::FLOAT, 3);
		llr::VertexBuffer bitangentBuffer(bitangent3f.size(), EDataType::FLOAT, 3);
		llr::IndexBuffer indexBuffer(indexes.size(), EDataType::UINT);

		vertexBuffer.Write(0, vertices3f.size(), vertices3f.data());
		normalBuffer.Write(0, normals3f.size(), normals3f.data());
		uvBuffer.Write(0, uv2f.size(), uv2f.data());
		tangentBuffer.Write(0, tangent3f.size(), tangent3f.data());
		bitangentBuffer.Write(0, bitangent3f.size(), bitangent3f.data());
		indexBuffer.Write(0, indexes.size(), indexes.data());

		m_vao.SetIndexBuffer(indexBuffer);

		m_vao.SetVertexBuffer(vertexBuffer, 0);
		m_vao.SetVertexBuffer(normalBuffer, 1);
		m_vao.SetVertexBuffer(uvBuffer, 2);
		m_vao.SetVertexBuffer(tangentBuffer, 3);
		m_vao.SetVertexBuffer(bitangentBuffer, 4);
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