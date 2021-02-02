#pragma once
#include "api.h"
#include "llr/ConstantBuffer.h"

#include <vector>

//TODO: rename RenderPassConstantInput

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

		const llr::ConstantBuffer GetConstantBuffer() const;

		Data & GetData();

		CData & GetData() const;

		void Update();

		bool IsValid() const;
	private:
		llr::ConstantBuffer m_constantBuffer;

		std::vector<char> m_data;
	};


	using PRenderPassInput = RenderPassInput *;
}
