#include "Queue.h"

//----------------------------------------------
void Queue::QPUSH(string& value) {
	lock_guard<mutex> lock(mtx);
	if (back < SIZE - 1) {
		elements[back] = value;
		back++;
	}
	else {
		cout << "Очередь заполнена." << endl;
	}
}

string Queue::QPOP() {
	lock_guard<mutex> lock(mtx);
	if (front == back) {
		cout << "Очередь пуста." << endl;
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
	cout << "Заявка подана: " << request << endl;
}

void RequestSystem::processRequests() {
	while (!requestQueue.isEmpty()) {
		string currentRequest = requestQueue.QPOP();
		cout << "Обработка заявки: " << currentRequest << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}

	cout << "Все заявки обработаны." << endl;
}

//----------------------------------------------
void firstTask() {
	vector<int> numbers = {1, 2, 3, 4, 5};
	int sum = 0;
	cout << "Вектор: ";
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers[i] << " ";
		sum += numbers[i];
	}
	cout << "Его сумма равна: " << sum << endl;
}

string reverseString(const string& str) {
	string reversed_str = str;
	reverse(reversed_str.begin(), reversed_str.end());
	return reversed_str;
}

void secondTask() {
	string original_str = "Hello";
	string reversed_str = reverseString(original_str);
	cout << "Перевёрнутая строка: " << reversed_str << endl;
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
	cout << number << " является простым числом? " << (isPrime ? "Да" : "Нет") << endl;
}

void TaskScheduler::addTask(string& task) {
	taskQueue.QPUSH(task);
	cout << "Задача добавлена: " << task << endl;
}

void TaskScheduler::executeTasks() {
	while (!taskQueue.isEmpty()) {
		string currentTask = taskQueue.QPOP();
		cout << "Выполнение задачи: " << currentTask << endl;
		this_thread::sleep_for(chrono::seconds(1));
		if (currentTask == "Задача 1") {
			firstTask();
		}
		else if (currentTask == "Задача 2") {
			secondTask();
		}
		else if (currentTask == "Задача 3") {
			thirdTask();
		}
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "Все задачи выполнены." << endl;
}
//----------------------------------------------
void DataBuffer::addToBuffer(string& data) {
	bufferQueue.QPUSH(data);
}

void DataBuffer::processBuffer() {
	// Открываем файл для добавления данных
	ofstream outputFile("C:\\output.txt", ios::app); 

	while (!bufferQueue.isEmpty()) {
		string currentData = bufferQueue.QPOP();
		outputFile << "Обработка данных: " << currentData << endl;
	}

	outputFile.close();
	cout << "Буфер обработан и данные сохранены в файле." << endl;
}
//----------------------------------------------
void EventQueue::addEvent(string& event) {
	eventQueue.QPUSH(event);
}

void EventQueue::processEvents() {
	while (!eventQueue.isEmpty()) {
		string currentEvent = eventQueue.QPOP();
	}

	cout << "Все события обработаны." << endl;
}
//----------------------------------------------
// Производство задач
void producer(Queue& q, int id) {
	for (int i = 0; i < 5; ++i) {
		string task = "Задача от производителя " + to_string(id) + ": " + to_string(i);
		q.QPUSH(task);	
		this_thread::sleep_for(chrono::seconds(2)); 
	}
}
// Выполнение задач
void executor(Queue& q, int id) {
	while (true) {
		string task = q.QPOP();
		if (task.empty()) {
			break;
		}

		cout << "Исполнитель " << id << " выполняет задачу: " << task << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
}
