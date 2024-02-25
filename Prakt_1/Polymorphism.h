#pragma once
#include <iostream>
#include <string>

using namespace std;

class BuildingPol {
protected:
    string address;
    int floors;

public:
    BuildingPol(const string& addr, int numFloors) : address(addr), floors(numFloors) {}

    // Виртуальная функция для общего метода
    virtual void displayInfo() const {
        cout << "Адрес: " << address << endl;
        cout << "Этажей: " << floors << endl;
    }

    virtual ~BuildingPol() = default;  // Виртуальный деструктор
};

class ResidentialBuildingPol : public BuildingPol {
private:
    int numApartments;

public:
    ResidentialBuildingPol(const string& addr, int numFloors, int numApts)
        : BuildingPol(addr, numFloors), numApartments(numApts) {}

    // Переопределение виртуальной функции базового класса
    void displayInfo() const override {
        BuildingPol::displayInfo(); // Вызываем метод базового класса
        cout << "Количество квартир: " << numApartments << endl;
    }
};

class OfficeBuildingPol : public BuildingPol {
private:
    int numOffices;

public:
    OfficeBuildingPol(const string& addr, int numFloors, int numOffs)
        : BuildingPol(addr, numFloors), numOffices(numOffs) {}

    // Переопределение виртуальной функции базового класса
    void displayInfo() const override {
        BuildingPol::displayInfo(); // Вызываем метод базового класса
        cout << "Количество офисов: " << numOffices << endl;
    }
};

// Функция, принимающая указатель на базовый класс
void showBuildingInfo(const BuildingPol* building) {
    building->displayInfo();
}