#include "ConstantBuffer.h"
#include "helper.h"


namespace llr
{
	ConstantBuffer::ConstantBuffer() {
	}

	ConstantBuffer::ConstantBuffer(size_t size) : m_size(size) {
		glGenBuffers(1, &m_bufferId); GL_CHECK
		glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_UNIFORM_BUFFER, m_size, nullptr, GL_STATIC_DRAW); GL_CHECK
		glBindBuffer(GL_UNIFORM_BUFFER, 0); GL_CHECK
	}

	ConstantBuffer::ConstantBuffer(const ConstantBuffer& r) :m_bufferId(r.m_bufferId), m_size(r.m_size), m_referenceCounter(r.m_referenceCounter) {}

	ConstantBuffer::~ConstantBuffer() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_bufferId != UNUSED) {
			glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;
		}
	}
	ConstantBuffer& ConstantBuffer::operator=(const ConstantBuffer& r) {
		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_referenceCounter = r.m_referenceCounter;
		return *this;
	}

	size_t ConstantBuffer::GetSize() const {
		return m_size;
	}

	void ConstantBuffer::Write(const size_t offset, const size_t size, const void* data) {
		glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void ConstantBuffer::Read(const size_t offset, const size_t size, void* o_data) {
		glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId);
		glGetBufferSubData(GL_UNIFORM_BUFFER, offset, size, o_data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
