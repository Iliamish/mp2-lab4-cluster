#pragma once
#include "Cluster.h"
#include <ctime>

const int MaxTacts = 100;
const int MaxTasks = 8;

class Client
{
	Cluster cluster;
	int countTask = 0;
public:
	Client();
	~Client();
	Task createTask();
	void tact();


};

