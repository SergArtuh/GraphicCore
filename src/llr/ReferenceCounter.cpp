#include "helper.h"
#include "ReferenceCounter.h"

namespace llr {
	ReferenceCounter::ReferenceCounter() {
		m_counter = new Counter;
		* m_counter = 1;
	}

	ReferenceCounter::operator bool() {
		return m_counter && *m_counter > 0;
	}


	ReferenceCounter::ReferenceCounter(const ReferenceCounter & r) : m_counter(r.m_counter) {
		Increase();
	}

	ReferenceCounter& ReferenceCounter::operator=(const ReferenceCounter & r) {
		m_counter = r.m_counter;
		Increase();

		return * this;
	}

	void ReferenceCounter::Increase() {
		if (m_counter) {
			(*m_counter)++;
		}
	}

	void ReferenceCounter::Decrease() {
		if (m_counter) {
			(*m_counter)--;
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
