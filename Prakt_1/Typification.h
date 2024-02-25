#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void implicitTypification() {
    unordered_map<string, vector<int>> dictionary;

    // Добавляем элементы в словарь
    dictionary["one"] = { 1, 11, 111 };
    dictionary["two"] = { 2, 22, 222 };
    dictionary["three"] = { 3, 33, 333 };

    // Выводим содержимое словаря используя неявную типизацию
    for (const auto& entry : dictionary) {
        cout << "Key: " << entry.first << ", Values: ";
        for (const auto& value : entry.second) {
            cout << value << " ";
        }
        cout << endl;
    }
}

auto repeatString(int count, const string& str) {
    string result;
    for (int i = 0; i < count; ++i) {
        result += str;
    }
    return result;
}