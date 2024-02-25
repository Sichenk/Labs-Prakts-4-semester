#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Account {
private:
    T balance;

public:
    // Конструктор
    Account(T initialBalance = 0) : balance(initialBalance) {}

    // Метод для пополнения счета
    void deposit(T amount) {
        balance += amount;
        cout << "Пополнено на " << amount << ". Новый баланс: " << balance << endl;
    }

    // Метод для списания со счета
    void withdraw(T amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Списано " << amount << ". Новый баланс: " << balance << endl;
        }
        else {
            cout << "Недостаточно средств для списания." << endl;
        }
    }

    // Метод для получения баланса
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
    // Конструктор
    Object(const string& objectName, const T& initialData) : name(objectName), data(initialData) {}

    // Метод для получения имени объекта
    string getName() const {
        return name;
    }

    // Метод для получения данных объекта
    T getData() const {
        return data;
    }

    // Метод для установки новых данных объекта
    void setData(const T& newData) {
        data = newData;
    }

    // Метод для вывода информации об объекте
    void displayInfo() const {
        cout << "Имя объекта: " << name << endl;
        cout << "Данные объекта: " << data << endl;
    }

    // Метод для увеличения данных на указанное значение
    void increaseData(const T& value) {
        data += value;
        cout << "Данные увеличены на " << value << ". Новые данные: " << data << endl;
    }

    // Метод для проверки, являются ли данные объекта четными
    bool isDataEven() const {
        static_assert(is_integral<T>::value, "T должен быть целочисленного типа");
        return data % 2 == 0;
    }

    // Метод для сброса данных объекта в значение по умолчанию
    void resetData() {
        data = T();
        cout << "Данные сброшены в значение по умолчанию." << endl;
    }

};

class User {
private:
    string username;
    string password;

public:
    // Конструктор
    User(const string& uname, const string& pwd) : username(uname), password(pwd) {}

    // Метод для аутентификации пользователя
    bool authenticate(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    // Метод для изменения пароля пользователя
    void changePassword(const string& newPassword) {
        password = newPassword;
        cout << "Пароль изменен успешно." << endl;
    }

    // Метод для получения логина пользователя
    string getUsername() const {
        return username;
    }

    // Метод для работы с профилем
    void userProfileAction() {
        cout << "Выполняется действие с профилем пользователя: " << username << endl;
    }
};