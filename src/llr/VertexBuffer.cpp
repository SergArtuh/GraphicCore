#include "VertexBuffer.h"

#include <utility>

namespace llr
{

	VertexBuffer::VertexBuffer(size_t size) {
		m_size = size;
		
		glGenBuffers(1, &m_bufferId); GL_CHECK

		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_ARRAY_BUFFER, m_size, 0, GL_STATIC_DRAW); GL_CHECK

		m_instanceCounterRef = new size_t[1];
		*m_instanceCounterRef = 1;
		 
	}
	VertexBuffer::VertexBuffer(VertexBuffer & r) : m_bufferId(r.m_bufferId), m_size(r.m_size), m_instanceCounterRef(r.m_instanceCounterRef){
		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)++;
		}
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_instanceCounterRef = r.m_instanceCounterRef;

		if (m_instanceCounterRef) {
			(*m_instanceCounterRef)--;
		}

		return * this;
	}

	VertexBuffer::~VertexBuffer() {
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

	void VertexBuffer::Write(const size_t offset, const size_t size, const void * data) {

		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}

	void VertexBuffer::Read(const size_t offset, const size_t size, void * o_data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, o_data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}
}
