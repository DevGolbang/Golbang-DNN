#pragma once
#include <chrono>

using namespace std::chrono;
class TimerBaseChrono {
public:
	//타이머제거
	TimerBaseChrono() :
		m_start(system_clock::time_point::min()) {

	}
	void Clear() {
		m_start = system_clock::time_point::min();
	}
	bool IsStarted() const {
		return (m_start != system_clock::time_point::min());
	}

	void Start() {
		m_start = std::chrono::system_clock::now();
	}

	unsigned long GetMS() {
		if (IsStarted()) {
			system_clock::duration diff;
			diff = system_clock::now() - m_start;
			return (unsigned)(duration_cast<milliseconds>(diff).count());
		}
		return 0;
	}
private:
	std::chrono::system_clock::time_point m_start;
};
