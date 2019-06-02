#include "Dwarf.h"
#include "Manager.h"

void* Dwarf::MineHelper(void* arg){
	static_cast<Dwarf*>(arg)->Mine();
	return NULL;
}

Dwarf::Dwarf(int id){
	this->id = (int*) malloc(sizeof(int));
	*(this->id) = id;

	srand(time(NULL));
	this->stamina = (rand() % 3) + 1;
	this->rockCarryingNum = 0;
	this->lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_create(&(Manager::GetInstance()->threads[id]), NULL, MineHelper, this/*(void*) this->id*/);
}

Dwarf::~Dwarf(){

}

void* Dwarf::Mine(){
	while(1){
		pthread_mutex_lock(&(Manager::GetInstance()->printLock));
		printf("Dwarf %d: It's a beautiful day! Let's mine!\n", *(this->id));
		pthread_mutex_unlock(&(Manager::GetInstance()->printLock));
		
		sem_wait(&(Manager::GetInstance()->tunnels));

		pthread_mutex_lock(&(Manager::GetInstance()->printLock));
		printf("Dwarf %d: Entering tunnel, time to mine.\n", *(this->id));
		pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

		pthread_mutex_lock(&lock);
		while(rockCarryingNum < MAX_ROCK_CARRY_NUM){
			rockCarryingNum += (rand() % 2) + 1;

			pthread_mutex_lock(&(Manager::GetInstance()->printLock));
			printf("Dwarf %d: I have %d minerals in my bag.\n", *(this->id), this->rockCarryingNum);
			pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

			Sleep(1 * 1000);
		}
		pthread_mutex_unlock(&lock);

		pthread_mutex_lock(&(Manager::GetInstance()->printLock));
		printf("Dwarf %d: Finished mining! Returning to village.\n", *(this->id));
		pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

		sem_post(&(Manager::GetInstance()->tunnels));
		Sleep(5 * 1000);
		
		pthread_mutex_lock(&(Manager::GetInstance()->villageLock));
		Manager::GetInstance()->storedMinerals += this->rockCarryingNum;
		this->rockCarryingNum = 0;

		pthread_mutex_lock(&(Manager::GetInstance()->printLock));
		printf("Dwarf %d: Storing minerals. Village now has %d minerals.\n", *(this->id), Manager::GetInstance()->storedMinerals);
		pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

		this->stamina--;
		pthread_mutex_unlock(&(Manager::GetInstance()->villageLock));

		if(this->stamina > 0){
			pthread_mutex_lock(&(Manager::GetInstance()->printLock));
			printf("Dwarf %d: Not tired, I can go mine %d times more\n", *(this->id), this->stamina);
			pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

			Sleep(2 * 1000);
		}
		else{
			pthread_mutex_lock(&(Manager::GetInstance()->printLock));
			printf("Dwarf %d: Tired! Going to rest.\n", *(this->id));
			pthread_mutex_unlock(&(Manager::GetInstance()->printLock));

			Sleep(30 * 1000);
			this->stamina = (rand() % 3) + 1;
		}
	}
	pthread_exit(0);
}