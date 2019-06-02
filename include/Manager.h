#ifndef MANAGER_H
#define MANAGER_H

#include "pthread.h"
#include "semaphore.h"

#define THREAD_MAX 100
#define TUNNEL_NUM 3

class Manager
{
public:
	Manager();
	~Manager();
	static Manager* GetInstance();
	pthread_t threads[THREAD_MAX];
	sem_t tunnels;
	pthread_mutex_t villageLock;
	pthread_mutex_t printLock;
	int storedMinerals;
private:
	static Manager* instance;
};

#endif