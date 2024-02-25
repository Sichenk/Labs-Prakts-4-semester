#include "Linked_list.h"
#include "Stack.h"
#include "Queue.h"
#include "HashTable.h"
#include "Encapsulation.h"
#include "Inheritance.h"
#include "Polymorphism.h"
#include "Typification.h"

using namespace std;

void mainMenu() {
    cout << "<1> ���� linked lists." << endl;
    cout << "<2> ���� stack." << endl;
    cout << "<3> ���� queue." << endl;
    cout << "<4> ���� hash." << endl;
    cout << "<6> ���� ������������." << endl;
    cout << "<7> ���� ������������." << endl;
    cout << "<8> ���� ������������." << endl;
    cout << "<9> ���� ���������." << endl;
    cout << "<0> �����." << endl;
}

void stackMenu() {
    cout << "<1> ���������� �������� �������" << endl;
    cout << "<2> ��������� � ������ ��������" << endl;
    cout << "<3> �������� ������������������ ������" << endl;
}

void queueMenu() {
    cout << "<1> C������ ��������� ������" << endl;
    cout << "<2> ������������ �����" << endl;
    cout << "<3> ����������� ������" << endl;
    cout << "<4> ��������� �������" << endl;
    cout << "<5> ����������� ������ ��������� �������" << endl;
}

void hashTableMenu() {
    cout << "<1> ����� ���������" << endl;
    cout << "<2> ���������� ����������" << endl;
    cout << "<3> �����������" << endl;
    cout << "<4> ������� ������� ���������" << endl;
}

void encapsulationMenu() {
    cout << "<1> �������� ������� ������ `����`" << endl;
    cout << "<2> ���������� ������� ������ `������`" << endl;
    cout << "<3> �������� ������ `������������`" << endl;
}

void inheritanceMenu() {
    cout << "<1> �������� ������ � ��� ���������� �� ������� `������������ ������ � ����������`" << endl;
}

void polymorphismMenu() {
    cout << "<1> ���������� ��������� ������������ ��������� ����� ������ ��� ��������� ������� �������� �� ������� `������������ ������ � ����������`" << endl;
}

void typificationMenu() {
    cout << "<1> ������� ��������� ������ ��� ����������� ����� ������ � �������� �������" << endl;
    cout << "<2> �������, ������� ���������� ���������, ���������� ����� ���������� ������ ��������� ���������� ���" << endl;
}

void sllBlock() {
    SinglyLinkedList list;
    list.testRemoveFirst();
    list.testRemoveAll();
    cout << "��� ����� ��������!" << endl;
}

void stackBlock() {
    Stack stack;
    stackMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        Stack callStack;
        
        callStack.firstFunction(callStack);
        callStack.secondFunction(callStack);

        // ������� ������ ������� �� �����
        cout << "������ �������:" << endl;
        while (true) {
            char functionName = callStack.SPOP();
            if (functionName == NULL) {
                break;
            }
            cout << functionName << endl;
        }
        break;
    }
    case 2: {
        UndoRedoStack undoRedoStack;

        char operation1 = 'A';
        char operation2 = 'B';

        // ��������� ��������
        undoRedoStack.executeOperation(operation1);
        undoRedoStack.executeOperation(operation2);

        // �������� ��������� ��������
        undoRedoStack.undoOperation();

        // ��������� ���������� ��������
        undoRedoStack.redoOperation();
        break;
    }
    case 3: {
        string expression;
        cout << "������� ������ � ����������: ";
        cin.ignore();
        getline(cin, expression);

        if (stack.isBalanced(expression)) {
            cout << "������ ��������������." << endl;
        }
        else {
            cout << "������ �� ��������������." << endl;
        }
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void queueBlock() {
    queueMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        RequestSystem requestSystem;

        string request1 = "������ A";
        string request2 = "������ B";

        // ������ ������
        requestSystem.submitRequest(request1);
        requestSystem.submitRequest(request2);

        // ������������ ������
        requestSystem.processRequests();
        break;
    }
    case 2: {
        TaskScheduler taskScheduler;

        string task1 = "������ 1";
        string task2 = "������ 2";
        string task3 = "������ 3";

        // ��������� ������ � �������
        taskScheduler.addTask(task1);
        taskScheduler.addTask(task2);
        taskScheduler.addTask(task3);

        // ��������� ��� ������
        taskScheduler.executeTasks();
        break;
    }
    case 3: {
        DataBuffer dataBuffer;

        string data1 = "������ A";
        string data2 = "������ B";

        // ��������� ������ � �����
        dataBuffer.addToBuffer(data1);
        dataBuffer.addToBuffer(data2);

        // ������������ ������ � ������
        dataBuffer.processBuffer();
        break;
    }
    case 4: {
        EventQueue eventQueue;

        string event1 = "������� A";
        string event2 = "������� B";

        // ��������� ������� � �������
        eventQueue.addEvent(event1);
        eventQueue.addEvent(event2);

        // ������������ �������
        eventQueue.processEvents();
        break;
    }
    case 5: {
        Queue taskQueue;
        vector<thread> producers;
        vector<thread> executors;

        // ������� � ��������� ������-������������� � ������-�����������
        for (int i = 0; i < 3; ++i) {
            producers.emplace_back(producer, ref(taskQueue), i + 1);
        }

        for (int i = 0; i < 2; ++i) {
            executors.emplace_back(executor, ref(taskQueue), i + 1);
        }

        // ���������� ���������� ���� �������
        for (auto& producerThread : producers) {
            producerThread.join();
        }

        // ��������� � ������� ������ ������ ��� ���������� �������-������������
        for (int i = 0; i < 2; ++i) {
            string empty = "";
            taskQueue.QPUSH(empty);
        }

        for (auto& executorThread : executors) {
            executorThread.join();
        }
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void hashTableBlock() {
    hashTableMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        HashTable myTable;

        // ���������� ���������
        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        string value2 = "value2";

        string key3 = "key3";
        string value3 = "value3";

        myTable.HSET(key1, value1);
        myTable.HSET(key2, value2);
        myTable.HSET(key3, value3);

        // ����� ���������
        cout << "�������� ��� " << key1 << ": " << myTable.HGET(key1) << endl;
        cout << "�������� ��� " << key2 << ": " << myTable.HGET(key2) << endl;
        cout << "�������� ��� " << key3 << ": " << myTable.HGET(key3) << endl;
        cout << "-------------------------" << endl;

        // �������� ��������
        myTable.HDEL(key2);

        // ��������� ����� ���������
        cout << "�������� ��� " << key1 << ": " << myTable.HGET(key1) << endl;
        // ������ ���� ����� ����� ��������
        cout << "�������� ��� " << key2 << ": " << myTable.HGET(key2) << endl;  
        cout << "�������� ��� " << key3 << ": " << myTable.HGET(key3) << endl;
        break;
    }
    case 2: {
        HashTable myTable;

        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        string value2 = "value2";

        string key3 = "key3";
        string value3 = "value3";

        myTable.HSET(key1, value1);
        myTable.HSET(key2, value2);
        myTable.HSET(key1, value3);  // ��������, ����� ��������������

        cout << "Value for key1: " << myTable.HGET(key1) << endl;  // ������ ���� "value1"
        cout << "Value for key2: " << myTable.HGET(key2) << endl;  // ������ ���� "value2"
        break;
    }
    case 3: {
        //0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946
        HashTable myResults;
        string key1 = "fibNumber7";
        string key2 = "fibNumber8";
        string key3 = "fibNumber9";
        // ��������� � ��������� ����������
        string result1 = to_string(fibonacci(7));
        myResults.HSET(key1, result1);

        string result2 = to_string(fibonacci(8));
        myResults.HSET(key2, result2);

        string result3 = to_string(fibonacci(9));
        myResults.HSET(key3, result3);

        // �������� ���������� �� ���-�������
        cout << "��������� ��� ����� 'fibNumber7': " << myResults.HGET(key1) << endl;
        cout << "��������� ��� ����� 'fibNumber8': " << myResults.HGET(key2) << endl;
        cout << "��������� ��� ����� 'fibNumber9': " << myResults.HGET(key3) << endl;
        break;
    }
    case 4: {
        HashTable myTable;

        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        string value2 = "value2";

        myTable.HSET(key1, value1);
        myTable.HSET(key2, value2);
        myTable.HSET(key1, value1);  // ��������, �������� �������

        cout << "������� �������� 'key1': " << myTable.HGETFR(key1) << endl;
        cout << "������� �������� 'key2': " << myTable.HGETFR(key2) << endl;

        myTable.HDEL(key1);  // �������� ��������
        cout << "������� �������� 'key1' ����� ��������: " << myTable.HGETFR(key1) << endl;
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void encapsulationBlock () {
    encapsulationMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // ������ ������������� ������� ������ "����" � ����� ������ double
        Account<double> doubleAccount(100.0);
        doubleAccount.deposit(50.5);
        doubleAccount.withdraw(30.2);

        cout << "������� ������: " << doubleAccount.getBalance() << endl;

        // ������ ������������� ������� ������ "����" � ����� ������ int
        Account<int> intAccount(200);
        intAccount.deposit(50);
        intAccount.withdraw(300);

        cout << "������� ������: " << intAccount.getBalance() << endl;
        break;
    }
    case 2: {
        // ������ ������������� ������� ������ "������" � ����� ������ double
        Object<double> doubleObject("DoubleObject", 3.14);
        doubleObject.displayInfo();

        // ������ ������������� ������� ������ "������" � ����� ������ int
        Object<int> intObject("IntObject", 42);
        intObject.displayInfo();

        intObject.increaseData(2);
        cout << "������ ������: " << (intObject.isDataEven() ? "��" : "���") << endl;
        intObject.resetData();
        intObject.displayInfo();

        // ��������� ������ ������� � ��������� ����� ����������
        intObject.setData(100);
        intObject.displayInfo();
        break;
    }
    case 3: {
        // ������ ������������� ������ "������������"
        User user("NikitaSilchenko", "password123");

        // ������� ��������������
        if (user.authenticate("password123")) {
            cout << "�������������� ������� ��� ������������: " << user.getUsername() << endl;

            // ��������� ������
            user.changePassword("newPassword456");

            // ������ � �������
            user.userProfileAction();
        }
        else {
            cout << "������ ��������������. �������� ������." << endl;
        }
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void inheritanceBlock() {
    inheritanceMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // ������ ������������� �������
        ResidentialBuildingInh residential("123 Lenina", 5, 20);
        residential.displayResidentialInfo();

        cout << endl;

        OfficeBuildingInh office("456 Titova", 10, 50);
        office.displayOfficeInfo();
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void polymorphismBlock() {
    polymorphismMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // ������ ������������� ������������
        ResidentialBuildingPol residential("123 Lenina", 5, 20);
        OfficeBuildingPol office("456 Titova", 10, 50);

        // �����������: �������� �������� ��������� ������� ����� ��������� �� ������� �����
        showBuildingInfo(&residential);
        cout << endl;
        showBuildingInfo(&office);
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

void typificationBlock() {
    typificationMenu();
    cout << "������� ����� �������: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        implicitTypification();
        break;
    }
    case 2: {
        auto repeatedString = repeatString(3, "������, ");
        cout << repeatedString << endl;
        break;
    }
    default: {
        cout << "������������ �����." << endl;
        break;
    }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    mainMenu();
    while (true) {
        int choice = 0;
        cout << "������� ����� �����: ";
        cin >> choice;
        switch (choice) {
        case 1: {     
            sllBlock();
            break;
        }
        case 2: {
            stackBlock();
            break;
        }
        case 3: {
            queueBlock();
            break;
        }
        case 4: {
            hashTableBlock();
            break;
        }
        case 6: {
            encapsulationBlock();
            break;
        }
        case 7: {
            inheritanceBlock();
            break;
        }
        case 8: {
            polymorphismBlock();
            break;
        }
        case 9: {
            typificationBlock();
            break;
        }
        case 0: {
            return 1;
        }
        default: {
            cout << "������������ �����. ��������� �������." << endl;
            break;
        }
        }
    }
    return 0;
}