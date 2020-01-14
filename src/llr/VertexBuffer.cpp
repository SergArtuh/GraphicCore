#include "VertexBuffer.h"
#include "helper.h"

#include <utility>

namespace llr
{
	VertexBuffer::VertexBuffer() {}
	VertexBuffer::VertexBuffer(size_t size, EDataType dataType, size_t count) : m_size(size), m_count(count), m_dataType(dataType) {
		glGenBuffers(1, &m_bufferId); GL_CHECK

		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_ARRAY_BUFFER, size * helper::getDataTypeSize(m_dataType), 0, GL_STATIC_DRAW); GL_CHECK

		m_instanceCounterRef = new size_t[1];
		*m_instanceCounterRef = 1;
		 
	}
	VertexBuffer::VertexBuffer(const VertexBuffer & r) : m_bufferId(r.m_bufferId), m_size(r.m_size), m_count(r.m_count), m_dataType(r.m_dataType), m_instanceCounterRef(r.m_instanceCounterRef){
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)++;
		}
	}

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_count = r.m_count;
		m_dataType = r.m_dataType;
		m_instanceCounterRef = r.m_instanceCounterRef;

		return * this;
	}

	size_t VertexBuffer::GetSizeInBytes() const
	{
		return helper::getDataTypeSize(m_dataType) * m_size * m_count;
	}

	size_t VertexBuffer::GetSize() const
	{
		return m_size;
	}

	size_t VertexBuffer::GetCount() const
	{
		return m_count;
	}

	EDataType VertexBuffer::GetDataType() const
	{
		return EDataType();
	}

	VertexBuffer::~VertexBuffer() {
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}
		
		if (m_instanceCounterRef && !(*m_instanceCounterRef) && m_bufferId != UNUSED) {
			glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;

			delete m_instanceCounterRef;
			m_instanceCounterRef = nullptr;
		}
	}

	void VertexBuffer::Write(const size_t offset, const size_t size, const void * data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferSubData(GL_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}

	void VertexBuffer::Read(const size_t offset, const size_t size, void * o_data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glGetBufferSubData(GL_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), o_data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}
}
