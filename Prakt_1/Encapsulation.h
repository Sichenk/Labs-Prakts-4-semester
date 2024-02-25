#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Account {
private:
    T balance;

public:
    // �����������
    Account(T initialBalance = 0) : balance(initialBalance) {}

    // ����� ��� ���������� �����
    void deposit(T amount) {
        balance += amount;
        cout << "��������� �� " << amount << ". ����� ������: " << balance << endl;
    }

    // ����� ��� �������� �� �����
    void withdraw(T amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "������� " << amount << ". ����� ������: " << balance << endl;
        }
        else {
            cout << "������������ ������� ��� ��������." << endl;
        }
    }

    // ����� ��� ��������� �������
    T getBalance() const {
        return balance;
    }
};

template <typename T>
class Object {
private:
    T data;
    string name;

public:
    // �����������
    Object(const string& objectName, const T& initialData) : name(objectName), data(initialData) {}

    // ����� ��� ��������� ����� �������
    string getName() const {
        return name;
    }

    // ����� ��� ��������� ������ �������
    T getData() const {
        return data;
    }

    // ����� ��� ��������� ����� ������ �������
    void setData(const T& newData) {
        data = newData;
    }

    // ����� ��� ������ ���������� �� �������
    void displayInfo() const {
        cout << "��� �������: " << name << endl;
        cout << "������ �������: " << data << endl;
    }

    // ����� ��� ���������� ������ �� ��������� ��������
    void increaseData(const T& value) {
        data += value;
        cout << "������ ��������� �� " << value << ". ����� ������: " << data << endl;
    }

    // ����� ��� ��������, �������� �� ������ ������� �������
    bool isDataEven() const {
        static_assert(is_integral<T>::value, "T ������ ���� �������������� ����");
        return data % 2 == 0;
    }

    // ����� ��� ������ ������ ������� � �������� �� ���������
    void resetData() {
        data = T();
        cout << "������ �������� � �������� �� ���������." << endl;
    }

};

class User {
private:
    string username;
    string password;

public:
    // �����������
    User(const string& uname, const string& pwd) : username(uname), password(pwd) {}

    // ����� ��� �������������� ������������
    bool authenticate(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    // ����� ��� ��������� ������ ������������
    void changePassword(const string& newPassword) {
        password = newPassword;
        cout << "������ ������� �������." << endl;
    }

    // ����� ��� ��������� ������ ������������
    string getUsername() const {
        return username;
    }

    // ����� ��� ������ � ��������
    void userProfileAction() {
        cout << "����������� �������� � �������� ������������: " << username << endl;
    }
};