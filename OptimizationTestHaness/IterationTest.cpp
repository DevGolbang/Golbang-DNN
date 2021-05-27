#include<string>
#include "Timer.h"
#include <iostream>
#include <windows.h>
std::string remove_ctrl(std::string s) {
	std::string result;
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] >= 0x20) {
			result = result + s[i];
		}

	}
	return result;
}
// ���� ������ ���
std::string remove_ctrl_mutating(std::string s) {
	std::string result;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 0x20)
			result += s[i];
	}
	return result;
}
// reserve() ��� + ����
std::string remove_ctrl_reserve(std::string s) {
	std::string result;
	result.reserve(s.length());
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 0x20)
			result += s[i];
	}

	return result;
}

//����
std::string remove_ctrl_ref_args(std::string const& s) {
	std::string result;
	result.reserve(s.length());
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] >= 0x20)
			result += s[i];
	}

	return result;
}

//���ͷ����� + ����
std::string remove_ctrl_ref_args_it(std::string const& s) {
	std::string result;
	result.reserve(s.length());

	for (std::string::const_iterator it = s.begin(), end = s.end(); it != end; ++it) {
		const char& res = *it;
		if (res >= 0x20)
			result += res;
	}

	return result;
}
//���ͷ����� + ���� + Ranged_Based_For�� ������ ����ȭ
std::string remove_ctrl_ref_args_it_upgrade(std::string const& s) {
	std::string result;
	result.reserve(s.length());
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	for (; it != end; ++it) {
		if (*it >= 0x20)
			result += *it;
	}

	return result;
}
//Ranged based For + ����
std::string remove_ctrl_ref_args_rbf(std::string const& s) {
	std::string result;
	result.reserve(s.length());
	//for (std::string::const_iterator it = s.begin(), end = s.end(); it != end; ++it) {
	//	if (*it >= 0x20)
	//		result += *it;
	//}
	for (auto& ite : s) {
		if (ite >= 0x20) result += ite;
	}

	return result;
}
//���� ��ȯ + ���� + ���ͷ�����
void remove_ctrl_ref_result_it(std::string& result, std::string const& s) {
	result.clear();
	result.reserve(s.length());
	for (auto it = s.begin(), end = s.end(); it != end; ++it) {
		if (*it >= 0x20)
			result += *it;
	}
}

//C ��Ÿ��
void remove_ctrl_cstrings(char* destp, char const* srcp, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		if (srcp[i] >= 0x20)
			*destp++ = srcp[i];
	}
	*destp = 0;
}
//�ʿ���� �������
std::string remove_ctrl_block(std::string s) {
	std::string result;
	for (size_t b = 0, i = b, e = s.length(); b < e; b = i + 1) {
		for (i = b; i < e; ++i) {
			if (s[i] < 0x20)
				break;
		}
		result = result + s.substr(b, i - b);
	}
	return result;

}
//�ʿ���� �������
std::string remove_ctrl_block_ref(std::string const& s) {
	std::string result;
	for (size_t b = 0, i = b, e = s.length(); b < e; b = i + 1) {
		for (i = b; i < e; ++i) {
			if (s[i] < 0x20)
				break;
		}
		result = result + s.substr(b, i - b);
	}
	return result;

}
//�� ��� �ݴ��
std::string remove_ctrl_block_append(std::string s) {
	std::string result;
	result.reserve(s.length());
	for (size_t b = 0, i = b; b < s.length(); b = i + 1) {
		for (i = b; i < s.length(); ++i) {
			if (s[i] < 0x20) break;
		}
		result.append(s, b, i - b);
	}
	return result;
}
//�� ��� �ݴ��
std::string remove_ctrl_block_append_ref(std::string const& s) {
	std::string result;
	result.reserve(s.length());
	for (size_t b = 0, i = b; b < s.length(); b = i + 1) {
		for (i = b; i < s.length(); ++i) {
			if (s[i] < 0x20) break;
		}
		result.append(s, b, i - b);
	}
	return result;
}
std::string remove_ctrl_erase(std::string s) {
	for (size_t i = 0; i < s.length();) {
		if (s[i] < 0x20)
			s.erase(i, 1);
		else ++i;
	}
	return s;
}
std::string remove_ctrl_erase_ref(std::string& s) {
	for (size_t i = 0; i < s.length();) {
		if (s[i] < 0x20)
			s.erase(i, 1);
		else ++i;
	}
	return s;
}
//typedef std::basic_string<char, std::char_traits<char>, block_allocator<char, 10>> fixed_block_string;
//fixed_block_string remove_ctrl_fixed_block(std::string s) {
//	fixed_block_string result;
//	for (size_t i = 0; i < s.length(); ++i) {
//		if (s[i] >= 0x20)
//			result = result + s[i];
//	}
//	return result;
//}
inline unsigned int DoTestHaness(TimerBaseChrono& _chrono, int count, std::string(*remove_ctrl_str)(std::string const& s)) {
	std::string k = "sdsldfjsdlfjlsdfjlsdjflsdjkfsdjflsjfsjk";
	_chrono.Start();
	for (int i = 0; i < count; ++i) {
		remove_ctrl_str(k);
	};
	return _chrono.GetMS();
}
inline unsigned int DoTestHaness(TimerBaseChrono& _chrono, int count, std::string(*remove_ctrl_str)(std::string& s)) {
	std::string k = "sdsldfjsdlfjlsdfjlsdjflsdjkfsdjflsjfsjk";
	_chrono.Start();
	for (int i = 0; i < count; ++i) {
		remove_ctrl_str(k);
	};
	return _chrono.GetMS();
}
inline unsigned int DoTestHaness(TimerBaseChrono& _chrono, int count, std::string(*remove_ctrl_str)(std::string const s)) {
	std::string k = "sdsldfjsdlfjlsdfjlsdjflsdjkfsdjflsjfsjk";
	_chrono.Start();
	for (int i = 0; i < count; ++i) {
		remove_ctrl_str(k);
	};
	return _chrono.GetMS();
}
inline unsigned int DoTestHaness(TimerBaseChrono& _chrono, int count, void(*remove_ctrl_str)(char* destp, char const* srcp, size_t size)) {
	std::string k = "sdsldfjsdlfjlsdfjlsdjflsdjkfsdjflsjfsjk";
	char result[40];
	memset(result, 0, 40);
	_chrono.Start();
	for (int i = 0; i < count; ++i) {
		remove_ctrl_str(result, k.c_str(), 40);
		memset(result, 0, 40);
	};
	return _chrono.GetMS();
}
//int main(void) {
//	TimerBaseChrono m_chrono;
//	std::cout << "������ ���� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_reserve) << std::endl;
//	std::cout << "������ ���� ��� ������ �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_block) << std::endl;
//	std::cout << "������ ���� ��� �߰��� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_block_append) << std::endl;
//	std::cout << "������ ���� ���� �޼ҵ� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_erase) << std::endl;
//	std::cout << "���� ���� ��� ������ �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_block_ref) << std::endl;
//	std::cout << "���� ���� ��� �߰��� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_block_append_ref) << std::endl;
//	std::cout << "���� ���� ���� �޼ҵ� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_erase_ref) << std::endl;
//	std::cout << "���ڿ� + �ݺ��� -> ������ �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_ref_args) <<std::endl;
//	std::cout << "���ͷ����� ���� ���� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_ref_args_it) << std::endl;
//	std::cout << "���ͷ����� ���� + Upgrade ���� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_ref_args_it_upgrade) << std::endl;
//	std::cout << "Ranged_Based_For ���� ���� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_ref_args_rbf) << std::endl;
//	std::cout << "C���� ���� �ӵ�:" << DoTestHaness(m_chrono, 10000, remove_ctrl_cstrings) << std::endl;
//	return 0;
//}