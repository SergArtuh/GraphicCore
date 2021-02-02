#pragma once
#include "api.h"
#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
	class VertexBuffer;
	class IndexBuffer;

	class  VertexArrayBuffer final {
	public:
		VertexArrayBuffer() = default;

		~VertexArrayBuffer();

		VertexArrayBuffer(const VertexArrayBuffer&);
		VertexArrayBuffer& operator=(const VertexArrayBuffer& r);

		void Bind();

		void Unbind();

		void SetVertexBuffer(const VertexBuffer &, CI32 location);

		void SetIndexBuffer(const IndexBuffer&);

		size_t GetIndexSize() const;

		EDataType GetIndexDataType() const;

		GLuint GetId() const { return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED && m_idxDataType != EDataType::NONE; }

	private:
		ReferenceCounter m_referenceCounter;

		Size m_idxSize = 0;
		EDataType m_idxDataType = EDataType::NONE;

		GLuint m_bufferId = ((GLuint)UNUSED);
	};
}

