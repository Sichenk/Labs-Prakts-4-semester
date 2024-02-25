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

    // ����������� ������� ��� ������ ������
    virtual void displayInfo() const {
        cout << "�����: " << address << endl;
        cout << "������: " << floors << endl;
    }

    virtual ~BuildingPol() = default;  // ����������� ����������
};

class ResidentialBuildingPol : public BuildingPol {
private:
    int numApartments;

public:
    ResidentialBuildingPol(const string& addr, int numFloors, int numApts)
        : BuildingPol(addr, numFloors), numApartments(numApts) {}

    // ��������������� ����������� ������� �������� ������
    void displayInfo() const override {
        BuildingPol::displayInfo(); // �������� ����� �������� ������
        cout << "���������� �������: " << numApartments << endl;
    }
};

class OfficeBuildingPol : public BuildingPol {
private:
    int numOffices;

public:
    OfficeBuildingPol(const string& addr, int numFloors, int numOffs)
        : BuildingPol(addr, numFloors), numOffices(numOffs) {}

    // ��������������� ����������� ������� �������� ������
    void displayInfo() const override {
        BuildingPol::displayInfo(); // �������� ����� �������� ������
        cout << "���������� ������: " << numOffices << endl;
    }
};

// �������, ����������� ��������� �� ������� �����
void showBuildingInfo(const BuildingPol* building) {
    building->displayInfo();
}