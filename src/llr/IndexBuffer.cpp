#include "IndexBuffer.h"

#include <utility>

namespace llr
{

	IndexBuffer::IndexBuffer(size_t size) {
		m_size = size;
		
		glGenBuffers(1, &m_bufferId); GL_CHECK

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, 0, GL_STATIC_DRAW); GL_CHECK

		m_instanceCounterRef = new size_t[1];
		* m_instanceCounterRef = 1;
		 
	}
	IndexBuffer::IndexBuffer(IndexBuffer & r) : m_bufferId(r.m_bufferId), m_size(r.m_size), m_instanceCounterRef(r.m_instanceCounterRef) {
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)++;
		}
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_instanceCounterRef = r.m_instanceCounterRef;

		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}

		return * this;
	}

	IndexBuffer::~IndexBuffer() {
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}
		
		if (!(*m_instanceCounterRef) && m_bufferId != UNUSED) {
			glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;

			delete m_instanceCounterRef;
			m_instanceCounterRef = nullptr;
		}
	}

	void IndexBuffer::Write(const size_t offset, const size_t size, const void * data) {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data); GL_CHECK
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK
	}

	void IndexBuffer::Read(const size_t offset, const size_t size, void * o_data) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, o_data); GL_CHECK
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK
	}
}
