#include "Cluster.h"
#include <algorithm>
#include <iostream>
#include <ctime>

Cluster::Cluster()
{
	for (int i = 0; i < MaxProcessors; i++) {
		Processor proc;
		int k = rand() % MaxCores + 1;
		while (k--) {
			cores++;
			proc.cores.push_back(0);
			proc.tactsForDone.push_back(0);
		}
		proc.used = false;
		proc.freeCores = proc.cores.size();
		cluster.push_back(proc);
	}
}


Cluster::~Cluster()
{
}

void Cluster::setNewTasks(vector<Task> &tasks)
{
	for (auto task : tasks) {
		queue.push(task);
	}
}

bool Cluster::validTask(Task &task)
{
	if (MaxProcessors < task.processors)
		return false;
	auto processorArray = cluster;
	std::sort(task.cores.begin(), task.cores.end());
	for (auto neededCores : task.cores) {
		bool flag = false;
		for (int i = 0; i < processorArray.size(); i++) {
			auto proc = processorArray[i];
			if (proc.cores.size() >= neededCores) {
				processorArray.erase(processorArray.begin() + i);
				flag = true;
				break;
			}
		}
		if (!flag)
			return false;
	}
	return true;
}

void Cluster::incTaskPriority()
{
	queue.incPriority();
}

void Cluster::doTasks()
{
	for (auto &proc : cluster){
		for (int i = 0; i < proc.tactsForDone.size(); i++)
		{
			if (!(proc.tactsForDone[i]))
				continue;
			if (!(--proc.tactsForDone[i])) {
				proc.cores[i] = 0;
				workingCores--;
				proc.freeCores++;
			}
		}	
	}
	for (int i = 0; i < workProcess.size(); i++) {
		if (!(--workProcess[i].tactsForDone)) {
			std::cout << "\nDone task with id " << workProcess[i].id << std::endl;
			workProcess.erase(workProcess.begin() + i);
			++doneTasks;
		}
	}
		while (!queue.empty()) {
			if (validTask(queue.front())) {
				if (this->setTaskOnCluster(queue.front()))
					std::cout << "\nSet up task id " << queue.front().id << std::endl;		
				else
					break;
			}
			else {
				std::cout << "\nInvalid task id " << queue.front().id << std::endl;
				invalidTasks++;
			}
			queue.pop();
		}
		this->getStats();
		std::cout << "----------------------------------------" << std::endl;
}

void Cluster::getStats()
{
	std::cout << "\n\n" << std::endl;
	std::cout << "Working tasks " << workProcess.size() << std::endl;
	std::cout << "Tasks in queue " << queue.size() << std::endl;
	std::cout << "Done tasks " <<doneTasks << std::endl;
	std::cout << "Invalid tasks " << invalidTasks << std::endl;
	std::cout << "Cluster Capasity " << float(workingCores)*100/float(cores) << "%" <<  std::endl;
}

bool Cluster::setTaskOnCluster(Task &task)
{
	auto fakeCluster = cluster;
	for (auto neededCores : task.cores) {
		bool flag = false;
		for (auto &proc : fakeCluster)
			if (proc.freeCores >= neededCores && !proc.used) {
				proc.used = true;
				flag = true;
				int i = 0;
				while (neededCores) {
					if (!proc.cores[i]) {
						proc.cores[i] = 1;
						proc.tactsForDone[i] = task.tacts;
						proc.freeCores--;
						neededCores--;
					}
					i++;
				}
				break;
			}
		if (!flag)
			return false;
	}

	for (auto neededCores : task.cores) {
		for (auto &proc : cluster)
			if (proc.freeCores >= neededCores && !proc.used) {
				proc.used = true;
				int i = 0;
				while (neededCores) {
					if (!proc.cores[i]) {
						proc.cores[i] = 1;
						proc.tactsForDone[i] = task.tacts;
						proc.freeCores--;
						neededCores--;
					}
					i++;
				}
				break;
			}
	}
	for (auto &proc : cluster) {
		proc.used = false;
	}
	for (auto cores : task.cores) {
		workingCores += cores;
	}
	taskInWork newTask;
	newTask.id = task.id;
	newTask.tactsForDone = task.tacts;
	workProcess.push_back(newTask);
	return true;
}
