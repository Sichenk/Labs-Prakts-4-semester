#include "Queue.h"

//----------------------------------------------
void Queue::QPUSH(string& value) {
	lock_guard<mutex> lock(mtx);
	if (back < SIZE - 1) {
		elements[back] = value;
		back++;
	}
	else {
		cout << "������� ���������." << endl;
	}
}

string Queue::QPOP() {
	lock_guard<mutex> lock(mtx);
	if (front == back) {
		cout << "������� �����." << endl;
		return "";
	}

	string value = elements[front];
	elements[front] = "";
	front++;
	return value;
}

//----------------------------------------------
void RequestSystem::submitRequest(string& request) {
	requestQueue.QPUSH(request);
	cout << "������ ������: " << request << endl;
}

void RequestSystem::processRequests() {
	while (!requestQueue.isEmpty()) {
		string currentRequest = requestQueue.QPOP();
		cout << "��������� ������: " << currentRequest << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}

	cout << "��� ������ ����������." << endl;
}

//----------------------------------------------
void firstTask() {
	vector<int> numbers = {1, 2, 3, 4, 5};
	int sum = 0;
	cout << "������: ";
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << " ";
		sum += numbers[i];
	}
	cout << "��� ����� �����: " << sum << endl;
}

string reverseString(const string& str) {
	string reversed_str = str;
	reverse(reversed_str.begin(), reversed_str.end());
	return reversed_str;
}

void secondTask() {
	string original_str = "Hello";
	string reversed_str = reverseString(original_str);
	cout << "����������� ������: " << reversed_str << endl;
}

bool checkPrime(int number) {
	if (number <= 1) {
		return false;
	}

	for (int i = 2; i <= number / 2; ++i) {
		if (number % i == 0) {
			return false;
		}
	}

	return true;
}

void thirdTask() {
	int number = 17;
	bool isPrime = checkPrime(number);
	cout << number << " �������� ������� ������? " << (isPrime ? "��" : "���") << endl;
}

void TaskScheduler::addTask(string& task) {
	taskQueue.QPUSH(task);
	cout << "������ ���������: " << task << endl;
}

void TaskScheduler::executeTasks() {
	while (!taskQueue.isEmpty()) {
		string currentTask = taskQueue.QPOP();
		cout << "���������� ������: " << currentTask << endl;
		this_thread::sleep_for(chrono::seconds(1));
		if (currentTask == "������ 1") {
			firstTask();
		}
		else if (currentTask == "������ 2") {
			secondTask();
		}
		else if (currentTask == "������ 3") {
			thirdTask();
		}
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "��� ������ ���������." << endl;
}
//----------------------------------------------
void DataBuffer::addToBuffer(string& data) {
	bufferQueue.QPUSH(data);
}

void DataBuffer::processBuffer() {
	// ��������� ���� ��� ���������� ������
	ofstream outputFile("C:\\output.txt", ios::app); 

	while (!bufferQueue.isEmpty()) {
		string currentData = bufferQueue.QPOP();
		outputFile << "��������� ������: " << currentData << endl;
	}

	outputFile.close();
	cout << "����� ��������� � ������ ��������� � �����." << endl;
}
//----------------------------------------------
void EventQueue::addEvent(string& event) {
	eventQueue.QPUSH(event);
}

void EventQueue::processEvents() {
	while (!eventQueue.isEmpty()) {
		string currentEvent = eventQueue.QPOP();
	}

	cout << "��� ������� ����������." << endl;
}
//----------------------------------------------
// ������������ �����
void producer(Queue& q, int id) {
	for (int i = 0; i < 5; ++i) {
		string task = "������ �� ������������� " + to_string(id) + ": " + to_string(i);
		q.QPUSH(task);	
		this_thread::sleep_for(chrono::seconds(2)); 
	}
}
// ���������� �����
void executor(Queue& q, int id) {
	while (true) {
		string task = q.QPOP();
		if (task.empty()) {
			break;
		}

		cout << "����������� " << id << " ��������� ������: " << task << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
}
