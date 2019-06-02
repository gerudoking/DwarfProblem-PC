#ifndef DWARF_H
#define DWARF_H

#include "pthread.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAX_ROCK_CARRY_NUM 20

//extern "C" void* MineHelper(void*);

class Dwarf
{
public:
	Dwarf(int id);
	~Dwarf();

	void* Mine();
	static void* MineHelper(void* arg);
private:
	int* id;
	int rockCarryingNum;
	int stamina;
	pthread_mutex_t lock;
};

#endif