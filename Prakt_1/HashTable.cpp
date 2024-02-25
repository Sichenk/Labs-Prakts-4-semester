#include "HashTable.h"

int HashTable::hash(string key) {
	int h = 0;
	for (char c : key) {
		h = h * 7 + c;
	}
	return h % SIZE;
}

int HashTable::secondHash(string key) {
	return 7 - (hash(key) % 7);
}

void HashTable::HSET(string& key, string& value) {
	if (count < SIZE) {
		int index = hash(key);
		int step = secondHash(key);
		if (keys[index] == "") {
			keys[index] = key;
			values[index] = value;
			frequencies[index] = 1;
		}
		else if (keys[index] != key) {
			while (keys[index] != "") {
				index = (index + step) % SIZE;
			}
			keys[index] = key;
			values[index] = value;
			frequencies[index] = 1;
		}
		else {
			frequencies[index]++;
			return;
		}
		count++;
	}
	else {
		cout << "Хэш-таблица заполнена." << endl;
	}
}

void HashTable::HDEL(string& key) {
	int index = hash(key);
	if (keys[index] == "" && values[index] == "") {
		cout << "Эта ячейка уже пуста." << endl;
	}
	else {
		keys[index] = "";
		values[index] = "";
		count--;
	}
}

string HashTable::HGET(string& key) {
	int index = hash(key);
	if (keys[index] != "" && values[index] != "") {
		return values[index];
	}
	else {
		return "";
	}
}

int HashTable::HGETFR(string& key) {
	int index = hash(key);
	int step = secondHash(key);

	while (keys[index] != "" && keys[index] != key) {
		index = (index + step) % SIZE;
	}

	if (keys[index] == key) {
		return frequencies[index];
	}
	else {
		return 0;  // Элемент не найден
	}
}

int fibonacci(int n) {
	int result;
	if (n <= 1) {
		result = n;
	}
	else {
		result = fibonacci(n - 1) + fibonacci(n - 2);
	}

	return result;
}