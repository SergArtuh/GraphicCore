#include "IndexBuffer.h"

#include <utility>
#include "helper.h"

namespace llr
{
	IndexBuffer::IndexBuffer(size_t size, EDataType type) : m_size(size), m_dataType(type) {
		
		glGenBuffers(1, &m_bufferId); GL_CHECK

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * helper::getDataTypeSize(m_dataType), 0, GL_STATIC_DRAW); GL_CHECK
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK

		m_instanceCounterRef = new size_t[1];
		* m_instanceCounterRef = 1;
		 
	}
	IndexBuffer::IndexBuffer(const IndexBuffer & r) : m_bufferId(r.m_bufferId), m_size(r.m_size), m_dataType(r.m_dataType), m_instanceCounterRef(r.m_instanceCounterRef) {
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)++;
		}
	}

	IndexBuffer& IndexBuffer::operator=(const IndexBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_dataType = r.m_dataType;
		m_instanceCounterRef = r.m_instanceCounterRef;

		return * this;
	}

	IndexBuffer::~IndexBuffer() {
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

	void IndexBuffer::Write(const size_t offset, const size_t size, const void * data) {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), data); GL_CHECK
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK
	}

	void IndexBuffer::Read(const size_t offset, const size_t size, void * o_data) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), o_data); GL_CHECK
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK
	}
	size_t IndexBuffer::GetSize() const
	{
		return m_size;
	}

	EDataType IndexBuffer::GetDataType() const
	{
		return m_dataType;
	}
}
