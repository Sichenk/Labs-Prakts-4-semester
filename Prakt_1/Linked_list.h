#pragma once
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

class Node {
public:
    string data;
    class Node* next;
    Node(string value, Node* head) : data(value), next(head) {}
};

class SinglyLinkedList {
private:
    Node* head;
public:
    SinglyLinkedList() : head(nullptr) {}

    void SLL_CREATE_EMPTY();
    void SLL_ADD_TO_HEAD(string& value);
    void SLL_ADD_TO_TAIL(string& value);
    bool SLL_REMOVE_FIRST();
    void SLL_REMOVE_ALL(string& value);

    void testRemoveFirst();
    void testRemoveAll();
};