#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>
#include <string>

struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void InsertAtBeginning(int value);
    void InsertAtEnd(int value);
    void DeleteValue(int value);
    std::vector<int> GetValues() const;

private:
    Node* head;
};

#endif // LINKED_LIST_H

