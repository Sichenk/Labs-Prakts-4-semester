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
    cout << "<1> Блок linked lists." << endl;
    cout << "<2> Блок stack." << endl;
    cout << "<3> Блок queue." << endl;
    cout << "<4> Блок hash." << endl;
    cout << "<6> Блок инкапсуляция." << endl;
    cout << "<7> Блок наследования." << endl;
    cout << "<8> Блок полиморфизма." << endl;
    cout << "<9> Блок типизации." << endl;
    cout << "<0> Выход." << endl;
}

void stackMenu() {
    cout << "<1> Управление вызовами функций" << endl;
    cout << "<2> Обработка и отмена операций" << endl;
    cout << "<3> Проверка сбалансированности скобок" << endl;
}

void queueMenu() {
    cout << "<1> Cистема обработки заявок" << endl;
    cout << "<2> Планирование задач" << endl;
    cout << "<3> Буферизация данных" << endl;
    cout << "<4> Обработка событий" << endl;
    cout << "<5> Координация работы множества потоков" << endl;
}

void hashTableMenu() {
    cout << "<1> Поиск элементов" << endl;
    cout << "<2> Устранение дубликатов" << endl;
    cout << "<3> Кэширование" << endl;
    cout << "<4> Подсчет частоты элементов" << endl;
}

void encapsulationMenu() {
    cout << "<1> Создание шаблона класса `Счет`" << endl;
    cout << "<2> Реализация шаблона класса `Обьект`" << endl;
    cout << "<3> Создание класса `Пользователь`" << endl;
}

void inheritanceMenu() {
    cout << "<1> Создание класса и его подклассов из области `Безопасность зданий и сооружений`" << endl;
}

void polymorphismMenu() {
    cout << "<1> Разработка механизма позволяющего применять общие методы для различных классов объектов из области `Безопасность зданий и сооружений`" << endl;
}

void typificationMenu() {
    cout << "<1> Неявная типизация данных для определения типов ключей и значений словаря" << endl;
    cout << "<2> Функция, которая возвращает результат, полученный путем повторения строки указанное количество раз" << endl;
}

void sllBlock() {
    SinglyLinkedList list;
    list.testRemoveFirst();
    list.testRemoveAll();
    cout << "Все тесты пройдены!" << endl;
}

void stackBlock() {
    Stack stack;
    stackMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        Stack callStack;
        
        callStack.firstFunction(callStack);
        callStack.secondFunction(callStack);

        // Выводим вызовы функций из стека
        cout << "Вызовы функций:" << endl;
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

        // Выполняем операции
        undoRedoStack.executeOperation(operation1);
        undoRedoStack.executeOperation(operation2);

        // Отменяем последнюю операцию
        undoRedoStack.undoOperation();

        // Повторяем отмененную операцию
        undoRedoStack.redoOperation();
        break;
    }
    case 3: {
        string expression;
        cout << "Введите строку с выражением: ";
        cin.ignore();
        getline(cin, expression);

        if (stack.isBalanced(expression)) {
            cout << "Скобки сбалансированы." << endl;
        }
        else {
            cout << "Скобки не сбалансированы." << endl;
        }
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void queueBlock() {
    queueMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        RequestSystem requestSystem;

        string request1 = "Заявка на установку датчиков температуры";
        string request2 = "Заявка на установку датчиков шума";

        // Подаем заявки
        requestSystem.submitRequest(request1);
        requestSystem.submitRequest(request2);

        // Обрабатываем заявки
        requestSystem.processRequests();
        break;
    }
    case 2: {
        TaskScheduler taskScheduler;

        string task1 = "Задача 1";
        string task2 = "Задача 2";
        string task3 = "Задача 3";

        // Добавляем задачи в очередь
        taskScheduler.addTask(task1);
        taskScheduler.addTask(task2);
        taskScheduler.addTask(task3);

        // Выполняем все задачи
        taskScheduler.executeTasks();
        break;
    }
    case 3: {
        DataBuffer dataBuffer;

        string data1 = "Данные об установке датчиков температуры";
        string data2 = "Данные об установку датчиков шума";

        // Добавляем данные в буфер
        dataBuffer.addToBuffer(data1);
        dataBuffer.addToBuffer(data2);

        // Обрабатываем данные в буфере
        dataBuffer.processBuffer();
        break;
    }
    case 4: {
        EventQueue eventQueue;

        string event1 = "Событие: установка датчика шума";
        string event2 = "Событие: установка датчика температуры";

        // Добавляем события в очередь
        eventQueue.addEvent(event1);
        eventQueue.addEvent(event2);

        // Обрабатываем события
        eventQueue.processEvents();
        break;
    }
    case 5: {
        Queue taskQueue;
        vector<thread> producers;
        vector<thread> executors;

        // Создаем и запускаем потоки-производители и потоки-потребители
        for (int i = 0; i < 3; ++i) {
            producers.emplace_back(producer, ref(taskQueue), i + 1);
        }

        for (int i = 0; i < 2; ++i) {
            executors.emplace_back(executor, ref(taskQueue), i + 1);
        }

        // Дожидаемся завершения всех потоков
        for (auto& producerThread : producers) {
            producerThread.join();
        }

        // Добавляем в очередь пустые задачи для завершения потоков-исполнителей
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
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void hashTableBlock() {
    hashTableMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        HashTable myTable;

        // Добавление элементов
        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        string value2 = "value2";

        string key3 = "key3";
        string value3 = "value3";

        myTable.HSET(key1, value1);
        myTable.HSET(key2, value2);
        myTable.HSET(key3, value3);

        // Поиск элементов
        cout << "Значение для " << key1 << ": " << myTable.HGET(key1) << endl;
        cout << "Значение для " << key2 << ": " << myTable.HGET(key2) << endl;
        cout << "Значение для " << key3 << ": " << myTable.HGET(key3) << endl;
        cout << "-------------------------" << endl;

        // Удаление элемента
        myTable.HDEL(key2);

        // Повторный поиск элементов
        cout << "Значение для " << key1 << ": " << myTable.HGET(key1) << endl;
        // Должно быть пусто после удаления
        cout << "Значение для " << key2 << ": " << myTable.HGET(key2) << endl;  
        cout << "Значение для " << key3 << ": " << myTable.HGET(key3) << endl;
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
        myTable.HSET(key1, value3);  // Дубликат, будет проигнорирован

        cout << "Value for key1: " << myTable.HGET(key1) << endl;  // Должно быть "value1"
        cout << "Value for key2: " << myTable.HGET(key2) << endl;  // Должно быть "value2"
        break;
    }
    case 3: {
        //0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946
        HashTable myResults;
        string key1 = "fibNumber7";
        string key2 = "fibNumber8";
        string key3 = "fibNumber9";
        // Вычисляем и сохраняем результаты
        string result1 = to_string(fibonacci(7));
        myResults.HSET(key1, result1);

        string result2 = to_string(fibonacci(8));
        myResults.HSET(key2, result2);

        string result3 = to_string(fibonacci(9));
        myResults.HSET(key3, result3);

        // Получаем результаты из хэш-таблицы
        cout << "Результат для ключа 'fibNumber7': " << myResults.HGET(key1) << endl;
        cout << "Результат для ключа 'fibNumber8': " << myResults.HGET(key2) << endl;
        cout << "Результат для ключа 'fibNumber9': " << myResults.HGET(key3) << endl;
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
        myTable.HSET(key1, value1);  // Дубликат, увеличит частоту

        cout << "Частота элемента 'key1': " << myTable.HGETFR(key1) << endl;
        cout << "Частота элемента 'key2': " << myTable.HGETFR(key2) << endl;

        myTable.HDEL(key1);  // Удаление элемента
        cout << "Частота элемента 'key1' после удаления: " << myTable.HGETFR(key1) << endl;
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void encapsulationBlock () {
    encapsulationMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // Пример использования шаблона класса "Счет" с типом данных double
        Account<double> doubleAccount(100.0);
        doubleAccount.deposit(50.5);
        doubleAccount.withdraw(30.2);

        cout << "Текущий баланс: " << doubleAccount.getBalance() << endl;

        // Пример использования шаблона класса "Счет" с типом данных int
        Account<int> intAccount(200);
        intAccount.deposit(50);
        intAccount.withdraw(300);

        cout << "Текущий баланс: " << intAccount.getBalance() << endl;
        break;
    }
    case 2: {
        // Пример использования шаблона класса "Объект" с типом данных double
        Object<double> doubleObject("DoubleObject", 3.14);
        doubleObject.displayInfo();

        // Пример использования шаблона класса "Объект" с типом данных int
        Object<int> intObject("IntObject", 42);
        intObject.displayInfo();

        intObject.increaseData(2);
        cout << "Данные четные: " << (intObject.isDataEven() ? "Да" : "Нет") << endl;
        intObject.resetData();
        intObject.displayInfo();

        // Изменение данных объекта и повторный вывод информации
        intObject.setData(100);
        intObject.displayInfo();
        break;
    }
    case 3: {
        // Пример использования класса "Пользователь"
        User user("NikitaSilchenko", "password123");

        // Попытка аутентификации
        if (user.authenticate("password123")) {
            cout << "Аутентификация успешна для пользователя: " << user.getUsername() << endl;

            // Изменение пароля
            user.changePassword("newPassword456");

            // Доступ к профилю
            user.userProfileAction();
        }
        else {
            cout << "Ошибка аутентификации. Неверный пароль." << endl;
        }
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void inheritanceBlock() {
    inheritanceMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // Пример использования классов
        ResidentialBuildingInh residential("123 Lenina", 5, 20);
        residential.displayResidentialInfo();

        cout << endl;

        OfficeBuildingInh office("456 Titova", 10, 50);
        office.displayOfficeInfo();
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void polymorphismBlock() {
    polymorphismMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        // Пример использования полиморфизма
        ResidentialBuildingPol residential("123 Lenina", 5, 20);
        OfficeBuildingPol office("456 Titova", 10, 50);

        // Полиморфизм: передача объектов различных классов через указатель на базовый класс
        showBuildingInfo(&residential);
        cout << endl;
        showBuildingInfo(&office);
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

void typificationBlock() {
    typificationMenu();
    cout << "Введите номер задания: ";
    int number = 0;
    cin >> number;
    switch (number) {
    case 1: {
        implicitTypification();
        break;
    }
    case 2: {
        auto repeatedString = repeatString(3, "Привет, ");
        cout << repeatedString << endl;
        break;
    }
    default: {
        cout << "Некорректный номер." << endl;
        break;
    }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    mainMenu();
    while (true) {
        int choice = 0;
        cout << "Введите номер блока: ";
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
            cout << "Некорректный номер. Повторите попытку." << endl;
            break;
        }
        }
    }
    return 0;
}
