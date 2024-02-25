#pragma once
#include <iostream>
#include <string>

using namespace std;

class BuildingInh {
protected:
    string address;
    int floors;

public:
    // Конструктор
    BuildingInh(const string& addr, int numFloors) : address(addr), floors(numFloors) {}

    // Метод для получения адреса здания
    string getAddress() const {
        return address;
    }

    // Метод для получения количества этажей
    int getFloors() const {
        return floors;
    }

    // Общий метод для вывода информации о здании
    void displayInfo() const {
        cout << "Адрес: " << address << endl;
        cout << "Этажей: " << floors << endl;
    }
};

class ResidentialBuildingInh : public BuildingInh {
private:
    int numApartments;

public:
    // Конструктор подкласса
    ResidentialBuildingInh(const string& addr, int numFloors, int numApts)
        : BuildingInh(addr, numFloors), numApartments(numApts) {}

    // Метод для получения количества квартир
    int getNumApartments() const {
        return numApartments;
    }

    // Специфический метод для вывода информации о жилом здании
    void displayResidentialInfo() const {
        displayInfo(); // Используем общий метод базового класса
        cout << "Количество квартир: " << numApartments << endl;
    }
};

class OfficeBuildingInh : public BuildingInh {
private:
    int numOffices;

public:
    // Конструктор подкласса
    OfficeBuildingInh(const string& addr, int numFloors, int numOffs)
        : BuildingInh(addr, numFloors), numOffices(numOffs) {}

    // Метод для получения количества офисов
    int getNumOffices() const {
        return numOffices;
    }

    // Специфический метод для вывода информации об офисном здании
    void displayOfficeInfo() const {
        displayInfo(); // Используем общий метод базового класса
        cout << "Количество офисов: " << numOffices << endl;
    }
};