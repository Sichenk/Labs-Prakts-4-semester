#pragma once
#include <iostream>
#include <vector>

#define SIZE 901

using namespace std;

class Stack {
private:
    char elements[SIZE];
    int top;

public:
    Stack() : top(-1) {}

    void SPUSH(char& value);
    char SPOP();

    bool isBalanced(string expression);
    char getOpeningBracket(char closingBracket);

    void firstFunction(Stack& callStack);
    void secondFunction(Stack& callStack);

    bool isEmpty() const {
        return top == -1;
    }
};

class UndoRedoStack {
private:
    Stack undoStack;
    Stack redoStack;

public:
    void executeOperation(char& value);
    void undoOperation();
    void redoOperation();
};