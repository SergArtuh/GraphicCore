#include "helper.h"
#include "ReferenceCounter.h"

namespace llr {


	ReferenceCounter::ReferenceCounter() {
		m_counter = new Counter;
		*m_counter = 1;

#ifdef REFERENCE_COUNTER_PROFOLER
		ReferenceCounterProfiler::Get().Increase();
#endif //REFERENCE_COUNTER_PROFOLER
	}

	ReferenceCounter::operator bool() {
		return m_counter && *m_counter > 0;
	}


	ReferenceCounter::ReferenceCounter(const ReferenceCounter& r) : m_counter(r.m_counter) {
		Increase();
	}

	ReferenceCounter::ReferenceCounter(ReferenceCounter && r) : m_counter(r.m_counter) {
		r.m_counter = nullptr;
	}

	ReferenceCounter& ReferenceCounter::operator=(const ReferenceCounter& r) {
		m_counter = r.m_counter;
		Increase();

		return *this;
	}

	void ReferenceCounter::Increase() {
		if (m_counter) {
			(*m_counter)++;

#ifdef REFERENCE_COUNTER_PROFOLER
			ReferenceCounterProfiler::Get().Increase();
#endif //REFERENCE_COUNTER_PROFOLER

		}
	}

	void ReferenceCounter::Decrease() {
		if (m_counter) {
			(*m_counter)--;

#ifdef REFERENCE_COUNTER_PROFOLER
			ReferenceCounterProfiler::Get().Decrease();
#endif //REFERENCE_COUNTER_PROFOLER

		}
	}

	ReferenceCounter::~ReferenceCounter()
	{
		if (!*this) {
			delete m_counter;
			m_counter = nullptr;
		}
	}
}

ReferenceCounterProfiler& ReferenceCounterProfiler::Get()
{
	static ReferenceCounterProfiler profiler;
	return profiler;
}
