#include "Client.h"
#include <iostream>
#include <thread>
#include <chrono>




Client::Client()
{
	srand(time(NULL));
}


Client::~Client()
{
}

Task Client::createTask()
{
	++countTask;
	Task task;
	task.processors = rand() % MaxProcessors + 1;
	for (int i = 0; i < task.processors; ++i) {
		task.cores.push_back(rand() % MaxCores + 1);
	}
	task.priority = rand() % 5 + 1;
	task.tacts = rand() % 5 + 1;
	task.id = countTask;
	std::cout << "create Task id = " << countTask;
	std::cout << " Parametres processors = " << task.processors << " priority = " << task.priority << " tacts = " << task.tacts << std::endl;
	return task;
}

void Client::tact()
{
	int k = 0;
	while (k++ != MaxTacts) {
		std::cout << "--------------------"<< k <<"--------------------" << std::endl;
		vector<Task> tasks;
		for (int i = 0; i < rand() % (MaxTasks + 1); i++) {
			tasks.push_back(this->createTask());
		}
		cluster.setNewTasks(tasks);
		cluster.doTasks();
		cluster.incTaskPriority();
		std::this_thread::sleep_for(chrono::seconds(10));
	}
}
