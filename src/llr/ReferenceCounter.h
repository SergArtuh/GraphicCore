#pragma once
#include "api.h"


namespace llr {
	class LLR_EXPORT ReferenceCounter {
		using Counter = size_t;
		using CounterPtr = Counter *;
	public:
		ReferenceCounter();
		ReferenceCounter(const ReferenceCounter &);
		ReferenceCounter(ReferenceCounter &&);
		ReferenceCounter& operator=(const ReferenceCounter&);
		virtual ~ReferenceCounter();

		void Increase();

		void Decrease();

		operator bool();

	protected:
	private:
		CounterPtr m_counter = nullptr;
	};
}



#define REFERENCE_COUNTER_PROFOLER
#ifdef REFERENCE_COUNTER_PROFOLER

class ReferenceCounterProfiler {
public:
	static ReferenceCounterProfiler& Get();

	void Enable() {
		m_isEnabled = true;
	}

	void Disable() {
		m_isEnabled = false;
	}

	void Reset() {
		m_counter = 0;
	}

	void Increase() {
		if (m_isEnabled) {
			m_counter++;
		}
	}

	void Decrease() {
		if (m_isEnabled) {
			m_counter--;
		}
	}

	int Count() {
		return m_counter;
	}

private:
	bool m_isEnabled = false;
	int m_counter = 0;
};

#endif //REFERENCE_COUNTER_PROFOLER