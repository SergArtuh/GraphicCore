#pragma once
#include "api.h"
#include "llr/ConstantBuffer.h"

#include <vector>

namespace gapi {

	class GAPI_EXPORT RenderPassInput {
		using Data = std::vector<char>;
		using CData = const Data;

		friend class Gapi;
	protected:
		RenderPassInput(size_t);
		RenderPassInput() = default;
		RenderPassInput(const RenderPassInput&) = default;
		RenderPassInput& operator=(const RenderPassInput&) = default;
	public:
		//bool operator==(const RenderPassInput& r);

		const llr::ConstantBuffer GetConstantBuffer();

		Data & GetData();

		CData & GetData() const;

		void MarkDirty();

		bool IsValid() const;
	private:
		llr::ConstantBuffer m_constantBuffer;

		std::vector<char> m_data;
		bool m_isDirty = true;
		
	};


	using PRenderPassInput = RenderPassInput *;
}
