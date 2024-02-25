#include "Stack.h"

//----------------------------------------------
void Stack::SPUSH(char& value) {
    if (top < SIZE - 1) {
        top++;
        elements[top] = value;
    }
    else {
        cout << "Стек заполнен" << endl;
    }
}

char Stack::SPOP() {
    if (top == -1) {
        return '\0';
    }

    char value = elements[top];
    elements[top] = '\0';
    top--;
    return value;
}
//----------------------------------------------
bool Stack::isBalanced(string expression) {
    Stack stack;

    for (char& c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            stack.SPUSH(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (stack.SPOP() != getOpeningBracket(c)) {
                return false;
            }
        }
    }

    return true;  // Если стек пуст, то скобки сбалансированы
}

char Stack::getOpeningBracket(char closingBracket) {
    switch (closingBracket) {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return '\0';
    }
}
//----------------------------------------------
void Stack::firstFunction(Stack& callStack) {
    char first_function = '1';
    callStack.SPUSH(first_function);
    cout << "Выполняется первая функция" << endl;
}

void Stack::secondFunction(Stack& callStack) {
    char second_function = '2';
    callStack.SPUSH(second_function);
    cout << "Выполняется вторая функция" << endl;
}
//----------------------------------------------
void UndoRedoStack::executeOperation(char& value) {
    undoStack.SPUSH(value);
}

void UndoRedoStack::undoOperation() {
    if (!undoStack.isEmpty()) {
        char undoneValue = undoStack.SPOP();
        redoStack.SPUSH(undoneValue);
        cout << "Отменена операция: " << undoneValue << endl;
    }
    else {
        cout << "Нечего отменять" << endl;
    }
}

void UndoRedoStack::redoOperation() {
    if (!redoStack.isEmpty()) {
        char redoneValue = redoStack.SPOP();
        undoStack.SPUSH(redoneValue);
        cout << "Повторена операция: " << redoneValue << endl;
    }
    else {
        cout << "Нечего повторять" << endl;
    }
}