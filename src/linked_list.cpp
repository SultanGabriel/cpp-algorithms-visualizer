#include "linked_list.h"

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::InsertAtBeginning(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
}

void LinkedList::InsertAtEnd(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::DeleteValue(int value) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp && temp->value != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp) {
        if (prev) {
            prev->next = temp->next;
        } else {
            head = temp->next;
        }
        delete temp;
    }
}

std::vector<int> LinkedList::GetValues() const {
    std::vector<int> values;
    Node* temp = head;
    while (temp) {
        values.push_back(temp->value);
        temp = temp->next;
    }
    return values;
}

