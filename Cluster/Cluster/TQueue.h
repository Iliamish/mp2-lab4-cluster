#pragma once
#include <vector>
using namespace std;

const int MaxProcessors = 10;
const int MaxCores = 4;

template <class T>
struct List
{
	List *next;
	T data;
};

struct Task
{
	int processors;
	vector<int> cores;
	int priority;
	int tacts;
	int id;
};

template <class T>
class TQueue
{
	List<T> * pFirst;
	int _size = 0;

public:
	TQueue()
	{
		pFirst = nullptr;
	}

	~TQueue()
	{
		while (pFirst != nullptr) {
			List<T> *tmp = pFirst;
			pFirst = tmp->next;
			delete tmp;
		}
	}

	bool empty() {
		return (pFirst == nullptr);
	}

	void push(T object) {
		_size++;
		if (pFirst == nullptr) {
			List<T> *obj = new List<T>;
			obj->data = object;
			obj->next = nullptr;
			pFirst = obj;
			return;
		}
		List<T> *tmp = pFirst;
		List<T> *obj = new List<T>;
		obj->data = object;
		while (tmp->next != nullptr ) {
			tmp = tmp->next;
		}
		tmp->next = obj;
		obj->next = nullptr;
	}

	

	void insert(List<T> *prevElement, List<T> *afterElement, List<T> *obj) {
		obj->next = afterElement;
		prevElement->next = obj;
	}

	void pop() {
		if (pFirst == nullptr)
			throw 0;
		_size--;
		List<T> *tmp = pFirst;
		pFirst = tmp->next;
		delete tmp;
	}

	T& front() {
		return pFirst->data;
	}

	void incPriority() {
		List<T> *tmp = pFirst;
		if (pFirst != nullptr) {
			do  {
				tmp->data.priority++;
				tmp = tmp->next;
			} while (tmp != nullptr);
		}
	}

	int size() {
		return _size;
	}
};

template <>
void TQueue<Task>::push(Task object) {
	_size++;
	if (pFirst == nullptr) {
		List<Task> *obj = new List<Task>;
		obj->data = object;
		obj->next = nullptr;
		pFirst = obj;
		return;
	}
	List<Task> *tmp = pFirst;
	bool ins = false;
	List<Task> *obj = new List<Task>;
	obj->data = object;
	while (tmp->next != nullptr) {
		if (tmp->next->data.priority < object.priority) {
			ins = true;
			if (tmp != pFirst)
				insert(tmp, tmp->next, obj);
			else {
				obj->next = pFirst;
				pFirst = obj;
			}
			break;
		}
		tmp = tmp->next;
	}
	if (!ins) {
		if (pFirst->data.priority < object.priority) {
			obj->next = pFirst;
			pFirst = obj;
		}
		else {
			tmp->next = obj;
			obj->next = nullptr;
		}
	}



}