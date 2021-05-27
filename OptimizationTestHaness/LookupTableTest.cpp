#include <assert.h>
#include <iostream>
#include "Timer.h"
struct Animal {
	int animal_code;
	const char* move_state;
};
void RabbitHop(Animal& _target) {
	_target.move_state = "It is Hopping";
}
void BearWalk(Animal& _target) {
	_target.move_state = "It is Walking";
}

void TigerRun(Animal& _target) {
	_target.move_state = "It is Running";
}

enum Animal_Variable {
	RABBIT, TIGER, BEAR, ANIMAL_MAX
};
enum  Move_State_Variable {
	HOP, Run, Walk, MOVE_MAX
};
void(*lookup_table[3])(Animal& _target) = { RabbitHop , TigerRun, BearWalk };

void Move_lookup_table(char& virtual_code, Animal& _target) {
	(*lookup_table[virtual_code])(_target);
}
void Move_switch(char& virtual_code, Animal& _target) {
	switch (virtual_code) {
	case RABBIT:

		return RabbitHop(_target);
	case TIGER:
		return TigerRun(_target);
	case BEAR:
		return BearWalk(_target);

	}
}
void Move_if(char& virtual_code, Animal& _target) {
	if (virtual_code == RABBIT) return RabbitHop(_target);
	else if (virtual_code == TIGER) return TigerRun(_target);
	else if (virtual_code == BEAR) return BearWalk(_target);
	else assert(0);

}
unsigned int DoTestHaness(int count, void(*move_)(char& virtual_code, Animal& _target)) {
	TimerBaseChrono _chrono;
	_chrono.Start();
	for (int j = 0; j < count; ++j) {
		for (int i = 0; i < ANIMAL_MAX; ++i) {
			Animal _anim = { i, "0" };
			move_((char&)i, _anim);
		}
	}
	return _chrono.GetMS();
}
//void main() {
//	const int TEST_COUNT = 10000000;
//
//	std::cout << "if문 사용시 소모 시간 : " << DoTestHaness(TEST_COUNT, Move_if) << std::endl;
//	std::cout << "switch문 사용시 소모 시간 : " << DoTestHaness(TEST_COUNT, Move_switch) << std::endl;
//	std::cout << "룩업 테이블 사용시 소모 시간 : " << DoTestHaness(TEST_COUNT, Move_lookup_table) << std::endl;
//}