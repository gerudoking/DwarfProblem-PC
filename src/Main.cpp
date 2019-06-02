#include "Manager.h"
#include "Dwarf.h"

int main(int argc, char const *argv[])
{
	setbuf(stdout, NULL);
	srand(time(NULL));
	
	Manager* instance = Manager::GetInstance();

	int dwarfNum = atoi(argv[1]);
	Dwarf* dwarves[dwarfNum];

	for(int i = 0; i < dwarfNum; i++){
		dwarves[i] = new Dwarf(i);
	}

	for(int i = 0; i < dwarfNum; i++){
		pthread_join(Manager::GetInstance()->threads[i], NULL);
	}

	return 0;
}