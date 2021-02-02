#pragma once
#include "api.h"
#include "llr/ConstantBuffer.h"

#include <vector>

namespace gapi {

	class GAPI_EXPORT RenderPassConstantInput {
		using Data = std::vector<char>;

		friend class Gapi;
	protected:
		RenderPassConstantInput(size_t);
		RenderPassConstantInput() = default;
		RenderPassConstantInput(const RenderPassConstantInput&) = default;
		RenderPassConstantInput& operator=(const RenderPassConstantInput&) = default;
	public:
		//bool operator==(const RenderPassConstantInput& r);

		const llr::ConstantBuffer GetConstantBuffer() const;

		Data & GetData();

		const Data & GetData() const;

		void Update();

		bool IsValid() const;
	private:
		llr::ConstantBuffer m_constantBuffer;

		std::vector<char> m_data;
	};


	using PRenderPassConstantInput = RenderPassConstantInput *;
}
