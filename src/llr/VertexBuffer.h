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

		Size GetSizeInBytes() const;

		Size GetSize() const;

		Size GetCount() const;

		EDataType GetDataType() const;

		void Write(CSize offset, CSize size, const Data data);

		void Read(CSize offset, CSize size, Data o_data);

		GLuint GetId() const { return m_bufferId; }

		bool IsValid() const { return m_bufferId != (GLuint)UNUSED; }

		bool IsInstansable() const;

	private:
		void AddReference();

		void RemoveReference();

		ReferenceCounter m_referenceCounter;

		GLuint m_bufferId = ((GLuint)UNUSED);

		Size m_size = 0;
		Size m_count = 0;
		EDataType m_dataType = EDataType::NONE;

		bool m_isInsnansable = false;
		
	};
}

