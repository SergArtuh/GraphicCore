#pragma once
#include "api.h"

#include "GL/glew.h"

#include "ReferenceCounter.h"

namespace llr
{
	class  VertexBuffer final {
	public:
		VertexBuffer();
		VertexBuffer(CSize size, EDataType dataType, CSize count, bool isInstansable = false);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&);
		VertexBuffer(VertexBuffer &&);

		VertexBuffer& operator=(const VertexBuffer& r);

		size_t GetSizeInBytes() const;

		size_t GetSize() const;

		size_t GetCount() const;

		EDataType GetDataType() const;

		void Write(const size_t offset, const size_t size, const void* data);

		void Read(const size_t offset, const size_t size, void* o_data);

		GLuint GetId() const { return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

		bool IsInstansable() const;

	private:
		void AddReference();

		void RemoveReference();

		ReferenceCounter m_referenceCounter;

		GLuint m_bufferId = ((GLuint)UNUSED);

		size_t m_size = 0;
		size_t m_count = 0;
		EDataType m_dataType = EDataType::NONE;

		bool m_isInsnansable = false;
		
	};
}

