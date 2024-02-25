#pragma once
#include <iostream>

using namespace std;

#define SIZE 901

class HashTable {
private:
	string keys[SIZE];
	string values[SIZE];
	int count;
	int frequencies[SIZE];
public:
	HashTable() : count(0) {}

	int hash(string key);

	int secondHash(string key);

	void HSET(string& key, string& value);

	void HDEL(string& key);

	string HGET(string& key);

	int HGETFR(string& key);
};

int fibonacci(int n);