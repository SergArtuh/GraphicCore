#include "VertexArrayBuffer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "GlAdapter.h"

#include "helper.h"

namespace llr
{
	VertexArrayBuffer::VertexArrayBuffer(const VertexArrayBuffer & r) : m_bufferId(r.m_bufferId), m_idxSize(r.m_idxSize), m_idxDataType(r.m_idxDataType), m_referenceCounter(r.m_referenceCounter) {
		m_referenceCounter.Increase();
	}

	VertexArrayBuffer::~VertexArrayBuffer() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_bufferId != UNUSED) {
			glDeleteVertexArrays(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;
		}
	}

	VertexArrayBuffer& VertexArrayBuffer::operator=(const VertexArrayBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_idxSize = r.m_idxSize;
		m_idxDataType = r.m_idxDataType;
		m_referenceCounter = r.m_referenceCounter;

		m_referenceCounter.Increase();
		return *this;
	}

	void VertexArrayBuffer::Bind() {
		if (m_bufferId == UNUSED) {
			glGenVertexArrays(1, &m_bufferId); GL_CHECK
		}
		glBindVertexArray(m_bufferId); GL_CHECK
	}

	void VertexArrayBuffer::Unbind() {
		glBindVertexArray(0); GL_CHECK
	}
	void VertexArrayBuffer::SetVertexBuffer(const VertexBuffer & buffer, const int location) {
		Bind();
		glEnableVertexAttribArray(location);  GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, buffer.GetId()); GL_CHECK

		glVertexAttribPointer(location, (GLsizei)buffer.GetCount(), adapter::DataType(buffer.GetDataType()), GL_FALSE, (GLsizei)0, nullptr); GL_CHECK

		Unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}
	void VertexArrayBuffer::SetIndexBuffer(const IndexBuffer& buffer) {
		Bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.GetId()); GL_CHECK

		Unbind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK

		m_idxSize = buffer.GetSize();
		m_idxDataType = buffer.GetDataType();
	}

	size_t VertexArrayBuffer::GetIndexSize() const
	{
		return m_idxSize;
	}

	EDataType VertexArrayBuffer::GetIndexDataType() const
	{
		return m_idxDataType;
	}
}
