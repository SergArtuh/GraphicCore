#pragma once


#include "types.h"

	template<class T>
	class ObjectHandleable {
	protected:
		virtual void Copy(const T& r) = 0;
		virtual bool IsValid() = 0;
		virtual void Dispose() = 0;
	};
	

	template<class T>
	class ObjectHandler : public T {
		using Counter = int;
		using CounterPtr = Counter*;
	public:
		ObjectHandler() {
			Increase();
		}

		ObjectHandler(const ObjectHandler& r) : m_counter(r.m_counter) {
			Copy(static_cast<T>(r));
			Increase();
		}

		ObjectHandler(ObjectHandler&& r) : m_counter(r.m_counter) {
			Copy(static_cast<T>(r));
			r.m_counter = nullptr;

		}

		~ObjectHandler() {
			Decrease();
		}

		ObjectHandler& operator=(const ObjectHandler& r) {
			Decrease();
			m_counter = r.m_counter;
			Copy(static_cast<T>(r));
			Increase();
			return *this;
		}

		/*ObjectHandler& operator=(ObjectHandler& r) {
			Decrease();
			m_counter = r.m_counter;
			Copy(static_cast<T>(r));
			Increase();
		}*/

		bool operator==(const ObjectHandler& r) {
			return m_counter == r.m_counter;
		}

		operator bool() {
			return m_counter && IsValid();
		}

		int GetReferenceCount() const {
			return (m_counter) ? *m_counter : 0;
		}

	protected:
		void Increase() {
			if (m_counter) {
				(*m_counter)++;
			}
			else {
				m_counter = new Counter;
				*m_counter = 1;
			}
		}

		void Decrease() {
			if (m_counter) {
				(*m_counter)--;

				if (*m_counter <= 0) {

					if (IsValid()) {
						Dispose();
					}

					delete m_counter;
					m_counter = nullptr;
				}
			}
		}
	private:
		CounterPtr m_counter = nullptr;
	};
