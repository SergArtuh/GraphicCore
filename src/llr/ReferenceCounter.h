#pragma once
#include "api.h"

namespace llr {
	class LLR_EXPORT ReferenceCounter {
		using Counter = size_t;
		using CounterPtr = Counter *;
	public:
		ReferenceCounter();
		ReferenceCounter(const ReferenceCounter &);
		ReferenceCounter& operator=(const ReferenceCounter&);
		virtual ~ReferenceCounter();

		void Increase();

		void Decrease();

		operator bool();

	protected:
		virtual void Delete() {};
	private:
		CounterPtr m_counter = nullptr;
	};
}
