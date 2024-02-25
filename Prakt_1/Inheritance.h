#pragma once
#include <iostream>
#include <string>

using namespace std;

class BuildingInh {
protected:
    string address;
    int floors;

public:
    // �����������
    BuildingInh(const string& addr, int numFloors) : address(addr), floors(numFloors) {}

    // ����� ��� ��������� ������ ������
    string getAddress() const {
        return address;
    }

    // ����� ��� ��������� ���������� ������
    int getFloors() const {
        return floors;
    }

    // ����� ����� ��� ������ ���������� � ������
    void displayInfo() const {
        cout << "�����: " << address << endl;
        cout << "������: " << floors << endl;
    }
};

class ResidentialBuildingInh : public BuildingInh {
private:
    int numApartments;

public:
    // ����������� ���������
    ResidentialBuildingInh(const string& addr, int numFloors, int numApts)
        : BuildingInh(addr, numFloors), numApartments(numApts) {}

    // ����� ��� ��������� ���������� �������
    int getNumApartments() const {
        return numApartments;
    }

    // ������������� ����� ��� ������ ���������� � ����� ������
    void displayResidentialInfo() const {
        displayInfo(); // ���������� ����� ����� �������� ������
        cout << "���������� �������: " << numApartments << endl;
    }
};

class OfficeBuildingInh : public BuildingInh {
private:
    int numOffices;

public:
    // ����������� ���������
    OfficeBuildingInh(const string& addr, int numFloors, int numOffs)
        : BuildingInh(addr, numFloors), numOffices(numOffs) {}

    // ����� ��� ��������� ���������� ������
    int getNumOffices() const {
        return numOffices;
    }

    // ������������� ����� ��� ������ ���������� �� ������� ������
    void displayOfficeInfo() const {
        displayInfo(); // ���������� ����� ����� �������� ������
        cout << "���������� ������: " << numOffices << endl;
    }
};