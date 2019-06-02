#include "Manager.h"

Manager* Manager::instance = nullptr;

Manager::Manager(){
	sem_init(&tunnels, 0, TUNNEL_NUM);
	villageLock = PTHREAD_MUTEX_INITIALIZER;
	printLock = PTHREAD_MUTEX_INITIALIZER;
	storedMinerals = 0;
}

Manager::~Manager(){

}

Manager* Manager::GetInstance(){
	if(instance == nullptr){
		instance = new Manager();
	}

	return instance;
}