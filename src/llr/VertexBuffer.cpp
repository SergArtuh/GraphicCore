#include "VertexBuffer.h"
#include "helper.h"

#include <utility>

namespace llr
{
	VertexBuffer::VertexBuffer() {}
	VertexBuffer::VertexBuffer(CSize size, EDataType dataType, CSize count, bool isInstansable) :
		m_size(size), m_count(count), m_dataType(dataType), m_isInsnansable(isInstansable) {
		glGenBuffers(1, &m_bufferId); GL_CHECK

		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferData(GL_ARRAY_BUFFER, size * helper::getDataTypeSize(m_dataType), 0, GL_STATIC_DRAW); GL_CHECK		 
	}
	VertexBuffer::VertexBuffer(const VertexBuffer & r) : 
		m_bufferId(r.m_bufferId), m_size(r.m_size), m_count(r.m_count), m_dataType(r.m_dataType), m_referenceCounter(r.m_referenceCounter), m_isInsnansable(r.m_isInsnansable){
		AddReference();
	}

	VertexBuffer::VertexBuffer(VertexBuffer && r) : m_bufferId(r.m_bufferId), m_size(r.m_size), m_count(r.m_count), m_dataType(r.m_dataType), m_referenceCounter(std::move(r.m_referenceCounter)), m_isInsnansable(r.m_isInsnansable) {
		r.m_bufferId = UNUSED;
		r.m_size = 0;
		r.m_count = 0;
		r.m_dataType = EDataType::NONE;
	}

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer& r) {
		RemoveReference();

		m_bufferId = r.m_bufferId;
		m_size = r.m_size;
		m_count = r.m_count;
		m_dataType = r.m_dataType;
		m_isInsnansable = r.m_isInsnansable;
		m_referenceCounter = r.m_referenceCounter;

		AddReference();
		return * this;
	}

	Size VertexBuffer::GetSizeInBytes() const
	{
		return helper::getDataTypeSize(m_dataType) * m_size * m_count;
	}

	Size VertexBuffer::GetSize() const
	{
		return m_size;
	}

	Size VertexBuffer::GetCount() const
	{
		return m_count;
	}

	EDataType VertexBuffer::GetDataType() const
	{
		return EDataType();
	}

	VertexBuffer::~VertexBuffer() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_bufferId != UNUSED) {
			glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;
		}
	}

	void VertexBuffer::Write(CSize offset, CSize size, const void * data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glBufferSubData(GL_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}

	void VertexBuffer::Read(CSize offset, CSize size, void * o_data) {
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); GL_CHECK
		glGetBufferSubData(GL_ARRAY_BUFFER, offset, size * helper::getDataTypeSize(m_dataType), o_data); GL_CHECK
		glBindBuffer(GL_ARRAY_BUFFER, 0); GL_CHECK
	}

	bool VertexBuffer::IsInstansable() const {
		return m_isInsnansable;
	}

	void VertexBuffer::AddReference() {
		m_referenceCounter.Increase();
	}

	void VertexBuffer::RemoveReference() {
		m_referenceCounter.Decrease();

		if (!m_referenceCounter && m_bufferId != UNUSED) {
			glDeleteBuffers(1, &m_bufferId); GL_CHECK
			m_bufferId = UNUSED;
		}
	}
}
