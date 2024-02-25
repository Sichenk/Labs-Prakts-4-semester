#include "Linked_list.h"

//----------------------------------------------
// ������� ��� �������� ������� ���������� ������
void SinglyLinkedList::SLL_CREATE_EMPTY() {
    head = nullptr;
}
//----------------------------------------------
// ������� ��� ���������� ������ ���� � ������ ���������� ������
void SinglyLinkedList::SLL_ADD_TO_HEAD(string& value) {
    Node* newNode = new Node(value, head);
    head = newNode;
}
//----------------------------------------------
// ������� ��� ���������� ������ ���� � ����� ���������� ������
void SinglyLinkedList::SLL_ADD_TO_TAIL(string& value) {
    Node* newNode = new Node(value, nullptr);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}
//----------------------------------------------
// ������� �������� ������� ���� �� ���������� ������
bool SinglyLinkedList::SLL_REMOVE_FIRST() {
    if (head == nullptr) {
        return false;  // ������ ����
    }

    Node* temp = head;
    head = head->next;
    delete temp;
    return true;
}

// ������� �������� ���� ����� �� ��������� value �� ���������� ������
void SinglyLinkedList::SLL_REMOVE_ALL(string& value) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (prev == nullptr) {
                // ���� ��������� � ������ ������
                Node* temp = current;
                head = current->next;
                current = head;
                delete temp;
            }
            else {
                // ���� ��������� � �������� ��� � ����� ������
                Node* temp = current;
                prev->next = current->next;
                current = current->next;
                delete temp;
            }
        }
        else {
            // ������� � ���������� ����
            prev = current;
            current = current->next;
        }
    }
}
//----------------------------------------------
// ���� ��� �������� ������� � �������� ������� ���� �� ���������� ������
void SinglyLinkedList::testRemoveFirst() {
    SinglyLinkedList list;
    list.SLL_CREATE_EMPTY();
    string value1 = "Node1";
    string value2 = "Node2";
    list.SLL_ADD_TO_HEAD(value1);
    list.SLL_ADD_TO_HEAD(value2);

    assert(list.SLL_REMOVE_FIRST());
    assert(list.SLL_REMOVE_FIRST());
    assert(!list.SLL_REMOVE_FIRST());
}
//----------------------------------------------
// ���� ��� �������� ������� � �������� ���� ����� �� ��������� value �� ���������� ������
void SinglyLinkedList::testRemoveAll() {
    SinglyLinkedList list;
    list.SLL_CREATE_EMPTY();
    string value1 = "Node1";
    string value2 = "Node2";
    list.SLL_ADD_TO_HEAD(value2);
    list.SLL_ADD_TO_TAIL(value2);
    list.SLL_ADD_TO_HEAD(value1);

    list.SLL_REMOVE_ALL(value2);

    assert(list.head != nullptr);
    assert(list.head->data == value1);
    assert(list.head->next == nullptr);
}