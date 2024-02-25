#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <mutex>

using namespace std;

#define SIZE 901

class Queue {
private:
	string elements[SIZE];
	int front;
	int back;
	mutex mtx;
public:
	Queue() : front(0), back(0) {}

	void QPUSH(string& value);
	string QPOP();

	bool isEmpty() const {
		return front == back;
	}
};

class RequestSystem {
private:
    Queue requestQueue;

public:
	void submitRequest(string& request);

	void processRequests();
};

class TaskScheduler {
private:
    Queue taskQueue;

public:
	void addTask(string& task);

	void executeTasks();
};

class DataBuffer {
private:
	Queue bufferQueue;

public:
	void addToBuffer(string& data);

	void processBuffer();
};

class EventQueue {
private:
	Queue eventQueue;

public:
	void addEvent(string& event);

	void processEvents();
};

void producer(Queue& q, int id);
void executor(Queue& q, int id);