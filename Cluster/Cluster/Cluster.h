#pragma once
#include "TQueue.h"
#include <vector>
using namespace std;

typedef struct Processor {
	vector<bool> cores;
	int freeCores;
	bool used;
	vector<int> tactsForDone;
};

typedef struct taskInWork {
	int id;
	int tactsForDone;
};



class Cluster
{
	TQueue<Task> queue;
	vector<Processor> cluster;
	vector<taskInWork> workProcess;
	int cores;
	int workingCores;

	int doneTasks = 0;
	int invalidTasks = 0;
	
public:
	Cluster();
	~Cluster();
	void setNewTasks(vector<Task> &tasks);
	bool validTask(Task &task);
	void incTaskPriority();
	void doTasks();
	void getStats();
	bool setTaskOnCluster(Task &task);
};

