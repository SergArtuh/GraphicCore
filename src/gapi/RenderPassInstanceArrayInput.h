#pragma once
#include "api.h"

#include "llr/VertexBuffer.h"



namespace gapi {
	class GAPI_EXPORT RenderPassInstanceArrayInput final {
		friend class Gapi;
	private:
		RenderPassInstanceArrayInput(CSize size, EDataType type, CSize count);
		RenderPassInstanceArrayInput() = default;
		RenderPassInstanceArrayInput(const RenderPassInstanceArrayInput&) = default;
		RenderPassInstanceArrayInput& operator=(const RenderPassInstanceArrayInput&) = default;

	public:
		bool operator==(const RenderPassInstanceArrayInput& r);

		void Write(CSize offset, CSize size, const Data data);

		const llr::VertexBuffer GetVertexBufferLlr() const;

		bool IsValid() const;
	private:

		llr::VertexBuffer m_vertexBuffer;
		bool m_isAddedScene = false;
	};


	using PRenderPassInstanceArrayInput = RenderPassInstanceArrayInput*;
}
