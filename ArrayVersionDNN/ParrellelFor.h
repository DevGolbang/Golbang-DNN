#pragma once
#include <future>

class ParrelelFor{
private:
	std::future<void> *m_asnc_job_list;
	int m_count = 0;
public:
	ParrelelFor(int _count) : m_count(_count) {
		m_asnc_job_list = new std::future<void>[_count];
		
	}
	void DoJob(void(*target_func)()) {
		for (int i = 0; i < m_count; ++i) { m_asnc_job_list[i] = std::async(target_func); }
	}
	~ParrelelFor() {
		delete[] m_asnc_job_list;
	}

};
